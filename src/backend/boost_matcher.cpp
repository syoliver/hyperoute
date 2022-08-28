#include <hyperoute/backend/boost_matcher.hpp>

namespace hyperoute::backend
{
    boost_matcher::boost_matcher(std::shared_ptr<boost::regex> db, std::vector<route_context> contexts, std::shared_ptr<std::vector<std::size_t>> capture_indexes)
        : db_(std::move(db))
        , capture_indexes_(std::move(capture_indexes))
        , contexts_(std::move(contexts))
    {

    }

    /* virtual */ boost_matcher::~boost_matcher() = default;
    
    /* virtual */ std::optional<matched> boost_matcher::match(std::string_view path, const std::vector<route_line_t>& route_lines)
    {
        boost::match_results<std::string_view::const_iterator> matcher;
        const auto matched_route = boost::regex_search(std::begin(path), std::end(path), matcher, *db_);
        if(matched_route)
        {
            const auto iter = std::find_if(std::begin(*capture_indexes_), std::end(*capture_indexes_), [&matcher](const auto index){
                return matcher[index+1].matched;
            });
        
            const auto context_index = iter - std::begin(*capture_indexes_);

            if(iter != std::end(*capture_indexes_))
            {
                const auto& line = route_lines[context_index];
                auto& matched_context = contexts_[context_index];
                auto iter_params = std::begin(matched_context.params);

                for(std::size_t match_index = *iter+1 ; match_index < *iter+line.captures.size()+1 ; ++match_index, ++iter_params)
                {
                    const auto capture_index = match_index-*iter-1;

                    const auto match_subindex = match_index+1;

                    auto& params = matched_context.params;
                    if(matcher[match_subindex].matched)
                    {
                        const auto count = matcher[match_subindex].second - matcher[match_subindex].first;
                        iter_params->second = std::string_view(matcher[match_subindex].first, count);

                    }
                    else
                    {
                        iter_params->second = std::string_view();
                    }
                }

                const auto prefix_count = matcher[*iter+1].second - matcher[*iter+1].first;
                matched_context.matched_path = std::string_view(matcher[*iter+1].first, prefix_count);
                matched_context.remaining_path = std::string_view(matcher[*iter+1].second, path.size()-prefix_count);


                return matched{
                    .context = contexts_[context_index],
                    .func = route_lines[context_index].func
                };
            }
        }
        return std::nullopt;
    }

    route_context& boost_matcher::context(std::size_t index)
    {
        return contexts_[index];
    }
}
