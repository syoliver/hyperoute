#pragma once

#ifndef __HYPEROUTE__BUILDER_H__
#define __HYPEROUTE__BUILDER_H__

#include <hyperoute/router.hpp>
#include <hyperoute/capture.hpp>
#include <hyperoute/route_function.hpp>
#include <hyperoute/regex_line.hpp>
#include <hyperoute/builder_route_modifier.hpp>
#include <functional>
#include <string_view>
#include <vector>
#include <optional>
#include <set>
#include <map>

namespace hyperoute
{
    namespace backend
    {
        class router_backend;
    }

    class builder
    {
    public:
        builder(std::unique_ptr<backend::router_backend> backend);
        builder_route_modifier add_route(std::string_view route, const route_function_t& callback);
        builder_route_modifier add_route_prefix(std::string_view route, const route_function_t& callback);
        std::optional<router> build();

    private:
        friend class builder_route_modifier;

        using router_backend_ptr = std::unique_ptr<backend::router_backend>;

        router_backend_ptr backend_;


        std::vector<std::pair<regex_line_t, bool>> lines_;
        std::map<std::string, std::set<std::size_t>> regexes_;
    };

}

#endif