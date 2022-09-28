#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>
#include <translate.hpp>
#include <hyperoute/backend/router_backend.hpp>
#include <hyperoute/backend/matcher_backend.hpp>
#include <hyperoute/builder_route_modifier.hpp>
#include <numeric>
#include <iostream>
#include <algorithm>

namespace hyperoute
{
    builder::builder(std::shared_ptr<backend::router_backend> backend)
        : backend_(std::move(backend))
    {

    }

    builder_route_modifier builder::add_route(std::string_view route, std::error_condition& ec, const route_function_t& callback)
    {
        auto[regex, captures] = translate_route(route, false, ec);

        lines_.emplace_back(
            regex_line_t{
                .regex      = std::move(regex)      ,
                .captures   = std::move(captures)   ,
                .func       = callback
            },
            true
        );

        return builder_route_modifier(*this, lines_.size()-1);
    }


    builder_route_modifier builder::add_route_prefix(std::string_view route, std::error_condition& ec, const route_function_t& callback)
    {
        const auto&[regex, captures] = translate_route(route, true, ec);

        lines_.emplace_back(
            regex_line_t{
                .regex      = std::move(regex)      ,
                .captures   = std::move(captures)   ,
                .func       = callback
            },
            true
        );

        return builder_route_modifier(*this, lines_.size()-1);
    }

    static std::vector<route_line_t> transform_route_line(const std::vector<regex_line_t>& regexes)
    {
        std::vector<route_line_t> lines;
        lines.reserve(regexes.size());
        
        std::transform(
            std::begin(regexes),
            std::end(regexes),
            std::back_inserter(lines),
            [](const auto& regex_line){
                return route_line_t{
                    .captures = regex_line.captures,
                    .func     = regex_line.func
                };
        });


        return std::move(lines);
    }

    std::optional<router> builder::build(std::error_condition& ec)
    {
        std::vector<router::verb_route_lines_context_t> route_lines;

        std::vector<regex_line_t> regexes;
        regexes.reserve(lines_.size());
        for(const auto& [verb, regexes_index] : regexes_)
        {
            regexes.clear();

            std::transform(
                std::begin(regexes_index),
                std::end(regexes_index),
                std::back_inserter(regexes),
                [this](const auto& index){
                    return lines_[index].first;
            });

            backend_->init_router(regexes, ec);
            
            if(ec)
            {
                return std::nullopt;
            }

            route_lines.push_back({verb, backend_->matcher(), transform_route_line(regexes)});
        }

        {
            regexes.clear();
            for(const auto& [regex, has_star]: lines_)
            {
                if(has_star)
                {
                    regexes.push_back(regex);
                }
            }


            if(regexes.empty() == false)
            {
                backend_->init_router(regexes, ec);

                if(ec)
                {
                    return std::nullopt;
                }

                route_lines.push_back({"*", backend_->matcher(), transform_route_line(regexes)});
            }
        }
        
        return router(std::move(route_lines));
    }
}
