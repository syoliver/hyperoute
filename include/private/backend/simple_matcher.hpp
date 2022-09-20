#pragma once

#ifndef __HYPEROUTE__BACKEND__SIMPLE_MATCHER_H__
#define __HYPEROUTE__BACKEND__SIMPLE_MATCHER_H__

#include <hyperoute/backend/matcher_backend.hpp>
#include <hyperoute/route_context.hpp>
#include <route_trie.hpp>
#include <string_view>
#include <memory>
#include <vector>
#include <optional>

namespace hyperoute::backend
{
    class simple_matcher : public matcher_backend
    {
    public:
        simple_matcher(std::shared_ptr<hyperoute::route_trie> db, hyperoute::route_trie::search_context search_context, std::vector<route_context> contexts);
        virtual ~simple_matcher();
        virtual std::optional<matched> match(std::string_view url, const std::vector<route_line_t>& route_lines) override;

        route_context& context(std::size_t index);
    private:
        std::shared_ptr<hyperoute::route_trie> db_;
        hyperoute::route_trie::search_context search_context_;
        std::vector<route_context> contexts_;
    };

}

#endif