#include <hyperoute/router.hpp>
#include <hyperoute/backend/matcher_backend.hpp>
#include <boost/container_hash/hash.hpp>

namespace hyperoute
{

router::router(router&&) = default;


router::router(std::vector<verb_route_lines_context_t> route_lines)
    : route_lines_(std::move(route_lines))
{
    index_.reserve(route_lines_.size());

    boost::hash<std::string> hasher;
    std::transform(
        std::begin(route_lines_),
        std::end(route_lines_),
        std::back_inserter(index_),
        [&hasher](const auto& route_lines){
            return std::uint8_t(hasher(route_lines.verb));
    });
}


router::~router() = default;

router& router::operator=(router&& other)
{
    std::swap(route_lines_, other.route_lines_);
    std::swap(index_, other.index_);
}

void router::call(const std::string_view verb, const std::string_view url) const
{
    static const boost::hash<std::string_view> hasher;

    const auto verb_hash = std::uint8_t(hasher(verb));
    static const auto star_hash = std::uint8_t(hasher("*"));

    auto iter_index = std::find(std::begin(index_), std::end(index_), verb_hash);

    const verb_route_lines_context_t* lines = nullptr;
    if(iter_index != std::end(index_))
    {
        const auto expected_verb_index = iter_index-std::begin(index_);

        if(route_lines_[expected_verb_index].verb == verb)
        {
            lines = &route_lines_[expected_verb_index];
        }
    }

    if(lines == nullptr && verb_hash != star_hash)
    {
        iter_index = std::find(std::begin(index_), std::end(index_), star_hash);

        if(iter_index != std::end(index_))
        {
            const auto expected_star_index = iter_index-std::begin(index_);

            if(route_lines_[expected_star_index].verb == "*")
            {
                lines = &route_lines_[expected_star_index];
            }
        }
        
    }

    if(lines != nullptr)
    {
        const auto& backend = lines->backend;

        auto matched = backend->match(url, lines->lines);
        if(matched.has_value())
        {
            matched->func(matched->context);
        }
    }
}

}