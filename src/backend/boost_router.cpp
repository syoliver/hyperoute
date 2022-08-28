#include <hyperoute/backend/boost_router.hpp>
#include <hyperoute/backend/boost_matcher.hpp>
#include <numeric>
#include <sstream>
#include <iostream>

namespace hyperoute::backend
{

/* virtual */ boost_router::~boost_router() = default;


static auto generate_capture_indexes(const std::vector<regex_line_t>& route_regexes)
{
    auto indexes = std::make_shared<std::vector<std::size_t>>();
    indexes->reserve(route_regexes.size());

    std::transform(
        std::begin(route_regexes),
        std::end(route_regexes),
        std::back_inserter(*indexes),
        [index = std::size_t(0)](const auto& line) mutable {
            const auto previous = index;
            index += 1+line.captures.size();
            return previous;
    });

    return indexes;
}


static auto transform_context(const std::vector<regex_line_t>& regexes)
{
    std::vector<route_context> contexts;
    contexts.reserve(regexes.size());
    
    std::transform(
        std::begin(regexes),
        std::end(regexes),
        std::back_inserter(contexts),
        [](const auto& regex_line){
            route_context context;
            context.params.reserve(regex_line.captures.size());
            
            for(const auto& capture: regex_line.captures)
            {
                // TODO: Check if insertion was successful
                context.params.emplace(capture.name, std::string_view());
            }
            return context;
    });


    return contexts;
}

static auto generate_whole_regex(const std::vector<regex_line_t>& regexes)
{
    bool first = true;
    std::ostringstream oss;
    for(const auto& regex : regexes)
    {
        if (first == false)
        {
            oss << '|';
        }

        oss << '(' << regex.regex << ')';
        first = false;
    }
    return oss.str();
}

/* virtual */ void boost_router::init_router(const std::vector<regex_line_t>& route_regexes)
{
    capture_indexes_ = generate_capture_indexes(route_regexes);

    const auto whole_regex = generate_whole_regex(route_regexes);

    contexts_ = transform_context(route_regexes);

    db_ = std::make_shared<boost::regex>(std::move(whole_regex));
}

/* virtual */ std::unique_ptr<matcher_backend> boost_router::matcher()
{
    return std::make_unique<boost_matcher>(db_, contexts_, capture_indexes_);
}

}
