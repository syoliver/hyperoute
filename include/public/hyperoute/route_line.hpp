#pragma once

#ifndef __HYPEROUTE__ROUTE_LINE_H__
#define __HYPEROUTE__ROUTE_LINE_H__

#include <hyperoute/capture.hpp>
#include <hyperoute/route_function.hpp>
#include <vector>

namespace hyperoute
{
    struct route_line_t
    {
        std::vector<capture_t> captures;
        route_function_t func;
    };
}

#endif
