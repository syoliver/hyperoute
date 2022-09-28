#pragma once

#ifndef __HYPEROUTE__BACKEND__ROUTE_BACKEND_H__
#define __HYPEROUTE__BACKEND__ROUTE_BACKEND_H__

#include <hyperoute/route_function.hpp>
#include <hyperoute/route_line.hpp>
#include <hyperoute/route_context.hpp>
#include <optional>
#include <string_view>
#include <vector>

namespace hyperoute::backend
{
    struct matched
    {
        const route_context& context;
        const route_function_t& func;
    };

    class matcher_backend
    {
    public:
        virtual ~matcher_backend();
        virtual std::optional<matched> match(std::string_view url, const std::vector<route_line_t>& route_lines) = 0;
    };

}

#endif