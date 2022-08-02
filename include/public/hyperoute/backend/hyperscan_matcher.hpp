#pragma once

#ifndef __HYPEROUTE__BACKEND__HYPERSCAN_MATCHER_H__
#define __HYPEROUTE__BACKEND__HYPERSCAN_MATCHER_H__

#include <hyperoute/backend/matcher_backend.hpp>
#include <hyperoute/context.hpp>
#include <hyperoute/ch_forward.hpp>
#include <string_view>
#include <memory>
#include <vector>
#include <optional>

namespace hyperoute::backend
{
    class hyperscan_matcher : public matcher_backend
    {
    public:
        hyperscan_matcher(std::shared_ptr<ch_database_t> db, std::vector<context_t> contexts);
        virtual ~hyperscan_matcher();
        virtual std::optional<matched> match(std::string_view url, const std::vector<route_line_t>& route_lines) override;

        context_t& context(std::size_t index);
    private:
        std::shared_ptr<ch_scratch_t> scratch_;
        std::shared_ptr<ch_database_t> db_;
        std::vector<context_t> contexts_;
    };

}

#endif