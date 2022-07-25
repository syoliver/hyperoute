#pragma once

#ifndef __HYPEROUTE__CAPTURE_H__
#define __HYPEROUTE__CAPTURE_H__

#include <string>

namespace hyperoute
{
    struct capture_t
    {
        std::string name;
        std::size_t group;
    };

}

#endif