#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <thread>
#include <filesystem>
#include <unordered_map>
#include <functional>

#include "All_Node.h"

using json = nlohmann::json;

class NodeFactory {
    public:
        using CreateSrcNode = std::function<std::shared_ptr<cvedix_nodes::cvedix_src_node>(const json&)>;
        using CreateDesNode = std::function<std::shared_ptr<cvedix_nodes::cvedix_des_node>(const json&)>;

        static NodeFactory& Instance()
        {
            static NodeFactory ins;
            return ins;
        }

        void registerSrcNode(const std::string& type, CreateSrcNode creator)
        {
            srcNodeCreators[type] = creator;
        }

        std::shared_ptr<cvedix_nodes::cvedix_src_node> CreateNode(const std::string& type, const json& config)
        {
            if(srcNodeCreators.find(type) != srcNodeCreators.end())
            {
                return srcNodeCreators[type](config);
            }
            return nullptr;
        }

    private:
        std::unordered_map<std::string, CreateSrcNode> srcNodeCreators;
        std::unordered_map<std::string, CreateDesNode> desNodeCreators;

        
        NodeFactory() = default;
        ~NodeFactory() = default;
        NodeFactory(const NodeFactory&) = delete;
        NodeFactory& operator=(const NodeFactory&) = delete;
};


class NodeRegister {
public:
    NodeRegister(const std::string& type, NodeFactory::CreateSrcNode creator) {
        NodeFactory::Instance().registerSrcNode(type, creator);
    }
};