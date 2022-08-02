#pragma once

#ifndef __HYPEROUTE__BACKEND__HYPERSCAN_ROUTER_H__
#define __HYPEROUTE__BACKEND__HYPERSCAN_ROUTER_H__

#include <hyperoute/backend/router_backend.hpp>
#include <hyperoute/ch_forward.hpp>
#include <hyperoute/context.hpp>
#include <hyperoute/regex_line.hpp>

namespace hyperoute::backend
{
    class hyperscan_router : public router_backend
    {
    public:
        virtual ~hyperscan_router();
        virtual void init_router(const std::vector<regex_line_t>& route_regexes) override;
        virtual std::unique_ptr<matcher_backend> matcher() override;

    private:
        std::shared_ptr<ch_database_t> db_;
        std::vector<context_t> contexts_;
    };

}

#endif