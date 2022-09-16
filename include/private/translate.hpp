#pragma once

#ifndef __HYPEROUTE__TRANSLATER_H__
#define __HYPEROUTE__TRANSLATER_H__

#include <hyperoute/builder.hpp>
#include <system_error>
#include <string>
#include <string_view>
#include <vector>

namespace hyperoute
{

    std::pair<std::string, std::vector<capture_t>> translate_route(std::string_view route, bool prefix_mode, std::error_condition& ec);

}

#endif