#pragma once

#ifndef __HYPEROUTE__BACKEND__ROUTER_BACKEND_H__
#define __HYPEROUTE__BACKEND__ROUTER_BACKEND_H__

#include <hyperoute/regex_line.hpp>
#include <memory>
#include <vector>

namespace hyperoute::backend
{
    class matcher_backend;

    class router_backend
    {
    public:
        virtual void init_router(const std::vector<regex_line_t>& route_regexes) = 0;
        virtual std::unique_ptr<matcher_backend> matcher() = 0;
    };

}

#endif