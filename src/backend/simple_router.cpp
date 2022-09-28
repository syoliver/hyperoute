#include <backend/simple_router.hpp>
#include <backend/simple_matcher.hpp>
#include <route_trie.hpp>
#include <hyperoute/error.hpp>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace hyperoute::backend
{

/* virtual */ simple_router::~simple_router() = default;



static auto transform_context(const std::vector<regex_line_t>& regexes, std::error_condition& ec)
{
    std::vector<route_context> contexts;
    contexts.reserve(regexes.size());
    
    std::transform(
        std::begin(regexes),
        std::end(regexes),
        std::back_inserter(contexts),
        [&ec](const auto& regex_line){
            route_context context;
            context.params.reserve(regex_line.captures.size());
            
            for(const auto& capture: regex_line.captures)
            {
                const auto [_, inserted] = context.params.emplace(capture.name, std::string_view());
                if(inserted == false)
                {
                    ec = make_error_condition(error::duplicate_parameter);
                }
            }
            return context;
    });


    return contexts;
}

/* virtual */ void simple_router::init_router(const std::vector<regex_line_t>& route_regexes, std::error_condition& ec)
{
    db_ = std::make_shared<hyperoute::route_trie>();

    contexts_ = transform_context(route_regexes, ec);

    std::size_t context_index = 0;
    for(const auto& route_regex: route_regexes)
    {
        // TODO:
        //  1) Tester le retour..
        db_->insert(route_regex.regex, ++context_index);
    }
}

/* virtual */ std::unique_ptr<matcher_backend> simple_router::matcher()
{
    return std::make_unique<simple_matcher>(db_, db_->create_search_context(), contexts_);
}

}
