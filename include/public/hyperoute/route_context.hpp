#pragma once

#ifndef __HYPEROUTE__ROUTE_CONTEXT_H__
#define __HYPEROUTE__ROUTE_CONTEXT_H__

#include <string>
#include <string_view>
#include <unordered_map>

namespace hyperoute
{
    struct route_context
    {
        using params_t = std::unordered_map<std::string, std::string_view>;

        std::string_view matched_path;
        std::string_view remaining_path;

        params_t params;
    };


}

#endif