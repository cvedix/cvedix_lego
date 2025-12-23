cmake_minimum_required(VERSION 3.5)
project(cvedix_backend CXX)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)

if(NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
# Do nothing
elseif(HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif(HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else()
    set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cc)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon
# add_subdirectory(drogon)
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
find_package(jwt-cpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE jwt-cpp::jwt-cpp)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
find_package(OpenCV REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
find_package(PkgConfig REQUIRED)
find_package(cvedix REQUIRED)
target_link_directories(${PROJECT_NAME}
    PRIVATE ${CVEDIX_LIBRARY_DIRS}
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CVEDIX_INCLUDE_DIRS} /opt/cvedix/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CVEDIX_LIBRARIES} /opt/cvedix/lib/libcvedix_instance_sdk.so)
pkg_check_modules(GST REQUIRED gstreamer-1.0 gstreamer-video-1.0)
target_include_directories(${PROJECT_NAME} PRIVATE ${GST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GST_LIBRARIES})

# Optional: enable Kafka broker support (requires librdkafka pkg-config)
option(ENABLE_CVEDIX_KAFKA "Enable Kafka broker support (requires librdkafka)" OFF)

if(ENABLE_CVEDIX_KAFKA)
    message(STATUS "Kafka support enabled: searching for librdkafka via pkg-config")
    pkg_check_modules(RDKAFKA REQUIRED rdkafka)
    target_include_directories(${PROJECT_NAME} PRIVATE ${RDKAFKA_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${RDKAFKA_LIBRARIES})
    target_compile_definitions(${PROJECT_NAME} PRIVATE CVEDIX_WITH_KAFKA)
endif()

# ##############################################################################
if(CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "c++17 or higher is required")
elseif(CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else()
    message(STATUS "use c++20")
endif()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(controllers/MakeNode MAKE_NODE_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
    ${CMAKE_CURRENT_BINARY_DIR})

# use the following line to create views with namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
# ${CMAKE_CURRENT_BINARY_DIR} TRUE)
# use the following line to create views with namespace CHANGE_ME prefixed
# and path namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
# ${CMAKE_CURRENT_BINARY_DIR} TRUE CHANGE_ME)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers/MakeNode
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CVEDIX_INCLUDE_DIRS}
)
target_sources(${PROJECT_NAME}
    PRIVATE
    ${SRC_DIR}
    ${CTL_SRC}
    ${MAKE_NODE_SRC}
    ${FILTER_SRC}
    ${PLUGIN_SRC}
    ${MODEL_SRC})
target_compile_definitions(cvedix_backend
    PRIVATE CVEDIX_WITH_GSTREAMER
)

# ##############################################################################
# uncomment the following line for dynamically loading views
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

# ##############################################################################
message(STATUS "CVEDIX INCLUDE DIRS = ${CVEDIX_INCLUDE_DIRS}")
add_subdirectory(test)

# ================= DEBUG CONFIG =================
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build type: DEBUG")

    target_compile_options(${PROJECT_NAME} PRIVATE
        -g
        -O0
        -Wall
        -Wextra
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
else()
    message(STATUS "Build type: RELEASE")

    target_compile_options(${PROJECT_NAME} PRIVATE
        -O3
    )
endif()
# ================================================