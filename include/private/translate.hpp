#pragma once

#ifndef __HYPEROUTE__TRANSLATER_H__
#define __HYPEROUTE__TRANSLATER_H__

#include <string>
#include <string_view>
#include <vector>

struct capture_t
{
    std::string name;
    std::size_t group;
};

std::pair<std::string, std::vector<capture_t>> translate_route(std::string_view route);

#endif