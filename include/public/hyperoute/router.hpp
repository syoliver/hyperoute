#pragma once

#ifndef __HYPEROUTE__ROUTER_H__
#define __HYPEROUTE__ROUTER_H__


#include <hyperoute/capture.hpp>
#include <hyperoute/route_function.hpp>
#include <hyperoute/route_line.hpp>
#include <vector>
#include <memory>
#include <string_view>

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
        using backend_ptr = std::unique_ptr<backend::matcher_backend>;


        struct verb_route_lines_context_t
        {
            std::string                 verb;
            backend_ptr                 backend;
            std::vector<route_line_t>   lines;
        };

        friend class builder;
        router(std::vector<verb_route_lines_context_t> route_lines);

    public:
        void call(std::string_view verb, std::string_view url) const;

    private:
        std::vector<std::uint8_t> index_;
        std::vector<verb_route_lines_context_t> route_lines_;
    };

}

#endif