#pragma once

#ifndef __HYPEROUTE__BUILDER_H__
#define __HYPEROUTE__BUILDER_H__

#include <hyperoute/router.hpp>
#include <hyperoute/capture.hpp>
#include <hyperoute/route_function.hpp>
#include <functional>
#include <string_view>
#include <vector>
#include <optional>

namespace hyperoute
{


    class builder
    {
    public:

        struct regex_line_t
        {
            std::string regex;
            std::vector<capture_t> captures;
            route_function_t func;
        };

    public:
        builder& add_route(std::string_view route, const route_function_t& callback);
        std::optional<router> build();

    private:
        std::vector<regex_line_t> regexes_;
    };

}

#endif