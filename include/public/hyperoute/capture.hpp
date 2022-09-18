#pragma once

#ifndef __HYPEROUTE__CAPTURE_H__
#define __HYPEROUTE__CAPTURE_H__

#include <string>

namespace hyperoute
{
    struct capture_t
    {
        std::string name;
        bool        has_regex;
        std::size_t group;
    };

}

#endif