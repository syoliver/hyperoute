#pragma once

#ifndef __HYPEROUTE__ROUTER_H__
#define __HYPEROUTE__ROUTER_H__


#include <hyperoute/capture.hpp>
#include <hyperoute/route_function.hpp>
#include <hyperoute/route_line.hpp>
#include <hyperoute/route_scratch.hpp>
#include <hyperoute/ch_forward.hpp>
#include <vector>
#include <memory>

namespace hyperoute
{
    class builder;
    
    class router
    {
    private:

    private:
        friend class builder;
        router(std::shared_ptr<ch_database_t>&& db, std::vector<route_line_t>&& route_lines);

    public:
        void call(std::string_view url) const;

    private:
        std::shared_ptr<ch_database_t> db_;
        std::vector<route_line_t> route_lines_;

        route_scratch scratch_;

    };

}

#endif