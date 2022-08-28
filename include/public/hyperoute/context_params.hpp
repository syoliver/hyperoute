#pragma once

#ifndef __HYPEROUTE__CONTEXT_PARAMS_H__
#define __HYPEROUTE__CONTEXT_PARAMS_H__

#include <vector>
#include <string_view>

namespace hyperoute
{
    class context_params final
    {
    private:
        using node = std::pair<const std::string, std::string_view>;
    public:
        using iterator = std::vector<node>::iterator;
        using const_iterator = std::vector<node>::const_iterator;
        using value_type = node;
        using key_type = const char *;
        using mapped_type = std::string_view;

        using size_type = std::vector<node>::size_type;
        using difference_type = std::vector<node>::difference_type;
        using reference = std::vector<node>::reference;
        using const_reference = std::vector<node>::const_reference;
        using pointer = std::vector<node>::pointer;
        using const_pointer = std::vector<node>::const_pointer;


        context_params();
        context_params(const context_params&);
        context_params(context_params&&);
        ~context_params();

        void reserve(std::size_t size);
        std::pair<iterator, bool> insert( const_iterator hint, const value_type& value );
        std::pair<iterator, bool> insert( const_iterator hint, value_type&& value );
        std::pair<iterator, bool> emplace(const std::string_view key, std::string_view value);
        iterator find(const std::string_view key);
        const_iterator find(const std::string_view key) const;
        
        iterator begin();
        const_iterator begin() const;

        iterator end();
        const_iterator end() const;


        context_params& operator=(const context_params&) = delete;
        context_params& operator=(context_params&&);

    private:
        iterator inner_find(const std::string_view key, std::uint16_t hash);
        
        iterator inner_emplace(const std::string_view key, std::string_view value, std::uint16_t hash);
        iterator inner_insert(std::pair<std::string, std::string_view> node, std::uint16_t hash);

    private:
        std::vector<std::uint16_t> hashs_;
        std::vector<node> nodes_;
    };
}


#endif
