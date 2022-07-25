#pragma once

#ifndef __HYPEROUTE__ROUTE_FUNCTION_H__
#define __HYPEROUTE__ROUTE_FUNCTION_H__

#include <hyperoute/context.hpp>
#include <functional>

namespace hyperoute
{
    using route_function_t = std::function<void(const context_t&)>;

}

#endif

