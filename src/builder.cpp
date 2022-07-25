#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>
#include <translate.hpp>
#include <hs/ch.h>
#include <numeric>

namespace hyperoute
{
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

    static std::vector<const char*> transform_routes(const std::vector<builder::regex_line_t>& regexes)
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


        return std::move(routes);
    }

    static std::vector<route_line_t> transform_route_line(const std::vector<builder::regex_line_t>& regexes)
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

    static std::vector<unsigned int> generate_ids(const std::vector<builder::regex_line_t>& regexes)
    {
        std::vector<unsigned int> ids(regexes.size(), 0);
        std::iota(std::begin(ids), std::end(ids), 0);

        return std::move(ids);
    }

    std::optional<router> builder::build()
    {
        ch_compile_error_t *err = nullptr;
        ch_database_t *db = nullptr;


        const auto& routes = transform_routes(regexes_);
        const auto& ids = generate_ids(regexes_);

        ch_compile_multi(routes.data(), nullptr, ids.data(), routes.size(), CH_MODE_GROUPS, nullptr, &db, &err);


        std::shared_ptr<ch_database_t> pdb(db, ch_free_database);

        auto route_lines = transform_route_line(regexes_);

        return router(std::move(pdb), std::move(route_lines));
    }
}
