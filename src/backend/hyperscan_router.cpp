#include <backend/hyperscan_router.hpp>
#include <backend/hyperscan_matcher.hpp>
#include <hyperoute/error.hpp>
#include <hs/ch.h>
#include <numeric>
#include <iostream>

namespace hyperoute::backend
{

/* virtual */ hyperscan_router::~hyperscan_router() = default;


static std::vector<unsigned int> generate_ids(const std::size_t count)
{
    std::vector<unsigned int> ids(count, 0);
    std::iota(std::begin(ids), std::end(ids), 0);

    return ids;
}


static std::vector<route_context> transform_context(const std::vector<regex_line_t>& regexes, std::error_condition& ec)
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

static std::vector<const char*> transform_routes(const std::vector<regex_line_t>& regexes)
{
    std::vector<const char*> routes;
    routes.reserve(regexes.size());

    std::transform(
        std::begin(regexes),
        std::end(regexes),
        std::back_inserter(routes),
        [](const auto& regex_line){
            return regex_line.regex.c_str();
    });


    return routes;
}

/* virtual */ void hyperscan_router::init_router(const std::vector<regex_line_t>& route_regexes, std::error_condition& ec)
{
    const auto& routes = transform_routes(route_regexes);
    
    const auto& ids = generate_ids(route_regexes.size());
    contexts_ = transform_context(route_regexes, ec);
    if(ec)
    {
        return;
    }

    ch_compile_error_t *err = nullptr;
    ch_database_t *db = nullptr;
    
    const auto status = ch_compile_multi(routes.data(), nullptr, ids.data(), routes.size(), CH_MODE_GROUPS, nullptr, &db, &err);
 

    if(status == CH_SUCCESS)
    {
        db_.reset(db, ch_free_database);
    }
    else
    {
        ec = make_error_condition(error::regex_syntax);
    }

    ch_free_compile_error(err);
}

/* virtual */ std::unique_ptr<matcher_backend> hyperscan_router::matcher()
{
    if(db_)
    {
        return std::make_unique<hyperscan_matcher>(db_, contexts_);
    }
    return nullptr;
}

}
