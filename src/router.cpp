#include <hyperoute/router.hpp>
#include <hyperoute/backend/matcher_backend.hpp>
#include <iostream>

namespace hyperoute
{

router::router(router&&) = default;

router::router(std::unique_ptr<backend::matcher_backend> backend, std::vector<route_line_t> route_lines)
    : backend_(std::move(backend))
    , route_lines_(std::move(route_lines))
{
}


router::~router() = default;

void router::call(std::string_view url) const
{
    auto matched = backend_->match(url, route_lines_);
    if(matched.has_value())
    {
        matched->func(matched->context);
    }
}

}