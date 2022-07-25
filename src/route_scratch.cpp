#include <hyperoute/route_scratch.hpp>
#include <hs/ch.h>

namespace hyperoute
{
    route_scratch::route_scratch(const ch_database_t* db, const std::vector<route_line_t>& route_lines)
    {
        ch_scratch_t* scratch = nullptr;
        
        auto error = ch_alloc_scratch(db, &scratch);

        scratch_.reset(scratch, ch_free_scratch);

        std::transform(
            std::begin(route_lines),
            std::end(route_lines),
            std::back_inserter(contexts_),
            [](const auto& line){
                context_t ctx;
                std::transform(
                    std::begin(line.captures),
                    std::end(line.captures),
                    std::inserter(ctx, std::end(ctx)),
                    [](const auto& capture){
                        return std::pair(capture.name, std::string_view());
                });
                
                return ctx;
        });
    }


    ch_scratch_t* route_scratch::scratch() const
    {
        return scratch_.get();
    }

    context_t& route_scratch::context(std::size_t index) const
    {
        return contexts_[index];
    }
}
