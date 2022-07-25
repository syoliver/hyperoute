#include <hyperoute/router.hpp>
#include <hs/ch.h>
#include <iostream>

namespace hyperoute
{

router::router(std::shared_ptr<ch_database_t>&& db, std::vector<route_line_t>&& route_lines)
    : db_(std::move(db))
    , route_lines_(std::move(route_lines))
    , scratch_(db_.get(), route_lines_)
{
}


struct scan_ctx
{
    const router* self;
    std::string_view url;
    const std::vector<route_line_t>& route_lines;
    const route_scratch& scratch;
    
};

static ch_callback_t on_event(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, unsigned int size, const ch_capture_t *captured, void *void_ctx)
{
    const scan_ctx* ctx = reinterpret_cast<scan_ctx*>(void_ctx);
    
    auto& context = ctx->scratch.context(id);
    const auto& line = ctx->route_lines[id];

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

    line.func(context);
    return CH_CALLBACK_TERMINATE;
}

void router::call(std::string_view url) const
{
    ch_error_t* err = nullptr;
    scan_ctx ctx{
        .self = this,
        .url = url,
        .route_lines = route_lines_,
        .scratch = scratch_
    };

    ch_scan(
        db_.get(),
        url.data(),
        url.size(),
        0,
        scratch_.scratch(),
        &on_event,
        nullptr,
        &ctx
    );
}

}