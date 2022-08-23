#pragma once

#ifndef __HYPEROUTE__BUILDER_H__
#define __HYPEROUTE__BUILDER_H__

#include <hyperoute/router.hpp>
#include <hyperoute/capture.hpp>
#include <hyperoute/route_function.hpp>
#include <hyperoute/regex_line.hpp>
#include <boost/unordered_map.hpp>
#include <functional>
#include <string_view>
#include <vector>
#include <optional>
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
        builder& add_route(std::string_view route, const route_function_t& callback);
        builder& add_route_prefix(std::string_view route, const route_function_t& callback);
        std::optional<router> build();

    private:
        using router_backend_ptr = std::unique_ptr<backend::router_backend>;

        router_backend_ptr backend_;

        std::map<std::string, std::vector<regex_line_t>> regexes_;
    };

}

#endif