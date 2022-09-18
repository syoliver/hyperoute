#include <hyperoute/backend/simple_router.hpp>
#include <hyperoute/backend/simple_matcher.hpp>
#include <hyperoute/error.hpp>
#include <numeric>
#include <sstream>
#include <iostream>

namespace hyperoute::backend
{

/* virtual */ simple_router::~simple_router() = default;


/* virtual */ void simple_router::init_router(const std::vector<regex_line_t>& route_regexes, std::error_condition& ec)
{
    for(const auto& route_regex: route_regexes)
    {
        route_trie_.insert(route_regex);
    }
}

/* virtual */ std::unique_ptr<matcher_backend> simple_router::matcher()
{
    return std::make_unique<simple_matcher>(route_trie_, contexts_);
}

}
