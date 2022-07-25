#pragma once

#ifndef __HYPEROUTE__TRANSLATER_H__
#define __HYPEROUTE__TRANSLATER_H__

#include <hyperoute/builder.hpp>
#include <hyperoute/context.hpp>
#include <string>
#include <string_view>
#include <vector>

namespace hyperoute
{

    std::pair<std::string, std::vector<capture_t>> translate_route(std::string_view route);

}

#endif