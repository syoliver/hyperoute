#pragma once

#ifndef __HYPEROUTE__CONTEXT_H__
#define __HYPEROUTE__CONTEXT_H__

#include <string>
#include <string_view>
#include <unordered_map>

namespace hyperoute
{
    using context_t = std::unordered_map<std::string, std::string_view>;
}

#endif