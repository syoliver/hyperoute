#include <hyperoute/backend/hyperscan_router.hpp>
#include <hyperoute/backend/hyperscan_matcher.hpp>
#include <hs/ch.h>
#include <numeric>

namespace hyperoute::backend
{

/* virtual */ hyperscan_router::~hyperscan_router() = default;


static std::vector<unsigned int> generate_ids(const std::size_t count)
{
    std::vector<unsigned int> ids(count, 0);
    std::iota(std::begin(ids), std::end(ids), 0);

    return ids;
}


static std::vector<route_context> transform_context(const std::vector<regex_line_t>& regexes)
{
    std::vector<route_context> contexts;
    contexts.reserve(regexes.size());
    
    std::transform(
        std::begin(regexes),
        std::end(regexes),
        std::back_inserter(contexts),
        [](const auto& regex_line){
            route_context context;
            std::transform(
                std::begin(regex_line.captures),
                std::end(regex_line.captures),
                std::inserter(context.params, std::end(context.params)),
                [](const auto& capture){
                    return std::pair(capture.name, std::string_view());
            });
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

/* virtual */ void hyperscan_router::init_router(const std::vector<regex_line_t>& route_regexes)
{
    const auto& routes = transform_routes(route_regexes);
    
    const auto& ids = generate_ids(route_regexes.size());
    contexts_ = transform_context(route_regexes);

    ch_compile_error_t *err = nullptr;
    ch_database_t *db = nullptr;
    

    ch_compile_multi(routes.data(), nullptr, ids.data(), routes.size(), CH_MODE_GROUPS, nullptr, &db, &err);
    db_.reset(db, ch_free_database);
}

/* virtual */ std::unique_ptr<matcher_backend> hyperscan_router::matcher()
{
    return std::make_unique<hyperscan_matcher>(db_, contexts_);
}

}
