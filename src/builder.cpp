#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>
#include <translate.hpp>
#include <hyperoute/backend/router_backend.hpp>
#include <hyperoute/backend/matcher_backend.hpp>
#include <numeric>

namespace hyperoute
{
    builder::builder(std::unique_ptr<backend::router_backend> backend)
        : backend_(std::move(backend))
    {

    }
    builder& builder::add_route(std::string_view route, const route_function_t& callback)
    {
        const auto&[regex, captures] = translate_route(route);

        regexes_.push_back({
            .regex      = std::move(regex)      ,
            .captures   = std::move(captures)   ,
            .func       = callback
        });

        return *this;
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

    std::optional<router> builder::build()
    {
        backend_->init_router(regexes_);

        auto route_lines = transform_route_line(regexes_);

        return router(backend_->matcher(), std::move(route_lines));
    }
}
