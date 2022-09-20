#pragma once

#ifndef __HYPEROUTE__BUILDER_ROUTE_MODIFIER_H__
#define __HYPEROUTE__BUILDER_ROUTE_MODIFIER_H__

#include <hyperoute/hyperoute_export.hpp>
#include <string>

namespace hyperoute
{
    class builder;

    class HYPEROUTE_EXPORT builder_route_modifier
    {
    private:
        friend class builder;
        builder_route_modifier(builder& build, std::size_t regex_index);

    public:
        builder_route_modifier() = delete;
        builder_route_modifier(const builder_route_modifier&) = delete;
        builder_route_modifier(builder_route_modifier&&) = delete;

        builder_route_modifier& operator=(const builder_route_modifier&) = delete;
        builder_route_modifier& operator=(builder_route_modifier&&) = delete;

        builder_route_modifier& methods(std::initializer_list<const char*>) &&;

    private:
        builder& builder_;
        std::size_t regex_index_;
    };
}

#endif
