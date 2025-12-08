/**
 *
 *  JWT.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class JWT : public HttpFilter<JWT>
{
  public:
    JWT() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

