#include <backend/simple_matcher.hpp>

namespace hyperoute::backend
{
    simple_matcher::simple_matcher(std::shared_ptr<route_trie> db, route_trie::search_context search_context, std::vector<route_context> contexts)
        : db_(std::move(db))
        , search_context_(std::move(search_context))
        , contexts_(std::move(contexts))
    {

    }

    /* virtual */ simple_matcher::~simple_matcher() = default;
    
    /* virtual */ std::optional<matched> simple_matcher::match(std::string_view path, const std::vector<route_line_t>& route_lines)
    {
        const auto& match = db_->search(path, search_context_);
        if(match.has_value())
        {
            const auto context_index = *match - 1;

            auto& context = contexts_[context_index];
            
            auto iter = std::begin(context.params);
            for(const auto& capture: search_context_.captures)
            {
                iter->second = capture;
                ++iter;
            }

            
            return matched{
                .context = contexts_[context_index],
                .func = route_lines[context_index].func
            };
        }

        return std::nullopt;
    }

    route_context& simple_matcher::context(std::size_t index)
    {
        return contexts_[index];
    }
}
