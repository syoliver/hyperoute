#include <hyperoute/backend/hyperscan_matcher.hpp>
#include <hs/ch.h>

namespace hyperoute::backend
{

hyperscan_matcher::hyperscan_matcher(std::shared_ptr<ch_database_t> db, std::vector<context_t> contexts)
    : db_(std::move(db))
    , contexts_(std::move(contexts))
{
    ch_scratch_t* scratch = nullptr;
    
    auto error = ch_alloc_scratch(db_.get(), &scratch);

    scratch_.reset(scratch, ch_free_scratch);
}
/* virtual */ hyperscan_matcher::~hyperscan_matcher() = default;

struct scan_ctx
{
    hyperscan_matcher* self;
    std::string_view url;
    const std::vector<route_line_t>& route_lines;
    std::optional<unsigned int> index;
};

static ch_callback_t on_event(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, unsigned int size, const ch_capture_t *captured, void *void_ctx)
{
    scan_ctx* ctx = reinterpret_cast<scan_ctx*>(void_ctx);
    
    auto& context = ctx->self->context(id);
    const auto& line = ctx->route_lines[id];
    ctx->index = id;
    for(std::size_t index = 1 ; index < size ; ++index)
    {
        if(captured[index].flags == CH_CAPTURE_FLAG_ACTIVE)
        {
            const auto match = ctx->url.substr(
                captured[index].from,
                captured[index].to - captured[index].from
            );
            
            context.insert_or_assign(line.captures[index-1].name, match);
        }
    }

    return CH_CALLBACK_TERMINATE;
}

context_t& hyperscan_matcher::context(const std::size_t index)
{
    return contexts_[index];
}

/* virtual */ std::optional<matched> hyperscan_matcher::match(const std::string_view url, const std::vector<route_line_t>& route_lines)
{
    ch_error_t* err = nullptr;
    scan_ctx ctx{
        .self = this,
        .url = url,
        .route_lines = route_lines,
        .index = std::nullopt
    };

    ch_scan(
        db_.get(),
        url.data(),
        url.size(),
        0,
        scratch_.get(),
        &on_event,
        nullptr,
        &ctx
    );

    if(ctx.index.has_value())
    {
        return matched{
            .context = contexts_[*ctx.index],
            .func = route_lines[*ctx.index].func
        };
    }
    return std::nullopt;
}

}
