#pragma once

#ifndef __HYPEROUTE__BACKEND__ROUTER_BACKEND_H__
#define __HYPEROUTE__BACKEND__ROUTER_BACKEND_H__

#include <hyperoute/regex_line.hpp>
#include <memory>
#include <vector>
#include <system_error>

namespace hyperoute::backend
{
    class matcher_backend;

    class router_backend
    {
    public:
        virtual ~router_backend();
        virtual void init_router(const std::vector<regex_line_t>& route_regexes, std::error_condition& ec) = 0;
        virtual std::unique_ptr<matcher_backend> matcher() = 0;
    };

}

#endif