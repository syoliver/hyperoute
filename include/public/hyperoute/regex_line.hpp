#pragma once

#ifndef __HYPEROUTE__REGEX_LINE_H__
#define __HYPEROUTE__REGEX_LINE_H__

#include <hyperoute/capture.hpp>
#include <hyperoute/route_function.hpp>
#include <string>

namespace hyperoute
{
    struct regex_line_t
    {
        std::string regex;
        std::vector<capture_t> captures;
        route_function_t func;
    };
}

#endif