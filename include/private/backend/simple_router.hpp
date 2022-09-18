#pragma once

#ifndef __HYPEROUTE__BACKEND__SIMPLE_ROUTER_H__
#define __HYPEROUTE__BACKEND__SIMPLE_ROUTER_H__

#include <hyperoute/backend/router_backend.hpp>
#include <hyperoute/route_context.hpp>
#include <hyperoute/regex_line.hpp>

namespace hyperoute::backend
{
    class simple_router : public router_backend
    {
    public:
        virtual ~simple_router();
        virtual void init_router(const std::vector<regex_line_t>& route_regexes, std::error_condition& ec) override;
        virtual std::unique_ptr<matcher_backend> matcher() override;

    private:
        std::vector<route_context> contexts_;
    };

}

#endif