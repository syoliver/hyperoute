#pragma once

#ifndef __HYPEROUTE__BACKEND__BOOST_ROUTER_H__
#define __HYPEROUTE__BACKEND__BOOST_ROUTER_H__

#include <hyperoute/backend/router_backend.hpp>
#include <boost/regex.hpp>
#include <hyperoute/route_context.hpp>
#include <hyperoute/regex_line.hpp>

namespace hyperoute::backend
{
    class boost_router : public router_backend
    {
    public:
        virtual ~boost_router();
        virtual void init_router(const std::vector<regex_line_t>& route_regexes) override;
        virtual std::unique_ptr<matcher_backend> matcher() override;

    private:
        std::shared_ptr<boost::regex> db_;
        std::shared_ptr<std::vector<std::size_t>> capture_indexes_;
        std::vector<route_context> contexts_;
    };

}

#endif