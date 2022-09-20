#pragma once

#ifndef __HYPEROUTE__BACKEND__SIMPLE_H__
#define __HYPEROUTE__BACKEND__SIMPLE_H__

#include <hyperoute/hyperoute_export.hpp>
#include <hyperoute/backend/router_backend.hpp>
#include <memory>

namespace hyperoute::backend
{
    HYPEROUTE_EXPORT std::shared_ptr<router_backend> make_simple();
}

#endif
