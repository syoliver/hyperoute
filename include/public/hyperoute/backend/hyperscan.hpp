#pragma once

#ifndef __HYPEROUTE__BACKEND__HYPERSCAN_H__
#define __HYPEROUTE__BACKEND__HYPERSCAN_H__

#include <hyperoute/backend/router_backend.hpp>
#include <memory>

namespace hyperoute::backend
{
    std::shared_ptr<router_backend> make_hyperscan();
}

#endif
