#pragma once

#ifndef __HYPEROUTE__ROUTER_H__
#define __HYPEROUTE__ROUTER_H__


#include <hyperoute/capture.hpp>
#include <hyperoute/route_function.hpp>
#include <hyperoute/route_line.hpp>
#include <vector>
#include <memory>

namespace hyperoute
{
    class builder;
    
    namespace backend
    {
        class matcher_backend;
    }

    class router
    {
    public:
        router(router&&);
        ~router();

    private:
        friend class builder;
        router(std::unique_ptr<backend::matcher_backend> backend, std::vector<route_line_t> route_lines);

    public:
        void call(std::string_view url) const;

    private:
        std::unique_ptr<backend::matcher_backend> backend_;
        std::vector<route_line_t> route_lines_;
    };

}

#endif