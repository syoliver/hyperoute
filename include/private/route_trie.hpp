#pragma once

#ifndef __HYPEROUTE__ROUTE_TRIE_H__
#define __HYPEROUTE__ROUTE_TRIE_H__

#include <hyperoute/builder.hpp>
#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace hyperoute
{
    namespace details
    {

        struct trie_data;

        struct trie_node
        {
            
            std::vector<std::pair<std::string, trie_data>> statics;
            std::vector<trie_data> matches;
        };

        struct trie_data
        {
            std::size_t route_index = 0;
            trie_node node;
        };

        struct backtracking_info;
    }

    class route_trie
    {
    public:
        struct search_context final
        {
        public:
            search_context();
            search_context(const search_context& other);
            search_context(search_context&& other);

            ~search_context();

            std::vector<std::string_view> captures;

            std::size_t backtracking_depth() const;

        private:
            friend class route_trie;

            std::vector<details::backtracking_info> backtracking_stack;
            std::vector<std::string_view> pending_captures;
        };

    public:
        bool insert(std::string_view route, std::size_t route_index);

        std::optional<std::size_t> search(std::string_view value, search_context& context) const;
        
        search_context create_search_context() const;

        void print_trie() const;

    private:
        details::trie_data root_;
    };
}

namespace std
{
    inline void swap(hyperoute::details::trie_node& lhs, hyperoute::details::trie_node& rhs) noexcept
    {
        std::swap(lhs.statics   , rhs.statics   );
        std::swap(lhs.matches   , rhs.matches   );
    }
}

#endif