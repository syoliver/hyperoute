
#include <hyperoute/context_params.hpp>
#include <boost/container_hash/hash.hpp>

namespace hyperoute
{
    static char* duplicate(const char* const in, std::size_t length)
    {
        char* out = new char[length+1];
        std::strcpy(out, in);
        out[length] = '\0';
        return out;
    }

    context_params::context_params() = default;
    context_params::context_params(context_params&& other) = default;
    context_params& context_params::operator=(context_params&&) = default;


    context_params::context_params(const context_params& other) = default;
    
    context_params::~context_params() = default;

    void context_params::reserve(std::size_t size)
    {
        hashs_.reserve(size);
        nodes_.reserve(size);
    }
    
    std::pair<context_params::iterator, bool> context_params::insert( const_iterator hint, const value_type& value )
    {
        static const boost::hash<std::string_view> hasher;
        std::uint64_t hash = hasher(value.first);
        auto iter = inner_find(value.first, hash);
        bool inserted = false;
        if(iter == end())
        {
            iter = inner_insert(value, hash);
            inserted = true;
        }

        return std::pair(iter, inserted);
    }

    std::pair<context_params::iterator, bool> context_params::insert( const_iterator hint, value_type&& value )
    {
        static const boost::hash<std::string_view> hasher;
        std::uint64_t hash = hasher(value.first);
        auto iter = inner_find(value.first, hash);
        bool inserted = false;
        if(iter == end())
        {
            iter = inner_insert(std::move(value), hash);
            inserted = true;
        }

        return std::pair(iter, inserted);
    }

    std::pair<context_params::iterator, bool> context_params::emplace(const std::string_view key, std::string_view value)
    {
        static const boost::hash<std::string_view> hasher;
        std::uint64_t hash = hasher(key);
        auto iter = inner_find(key, hash);
        bool inserted = false;
        if(iter == end())
        {
            iter = inner_emplace(key, value, hash);
            inserted = true;
        }

        return std::pair(iter, inserted);
    }

    context_params::iterator context_params::find(const std::string_view key)
    {
        static const boost::hash<std::string_view> hasher;

        const std::uint16_t search_hash = hasher(key);

        return inner_find(key, search_hash);
    }

    context_params::const_iterator context_params::find(const std::string_view key) const
    {
        return const_cast<context_params*>(this)->find(key);
    }

    context_params::iterator context_params::begin()
    {
        return std::begin(nodes_);
    }
    context_params::const_iterator context_params::begin() const
    {
        return std::begin(nodes_);
    }

    context_params::iterator context_params::end()
    {
        return std::end(nodes_);
    }
    context_params::const_iterator context_params::end() const
    {
        return std::end(nodes_);
    }


    context_params::iterator context_params::inner_find(const std::string_view key, const std::uint16_t search_hash)
    {
        const auto node_count = nodes_.size();
        for(std::size_t node_index = 0 ; node_index < node_count ; ++node_index)
        {
            if(hashs_[node_index] == search_hash && nodes_[node_index].first == key)
            {
                return std::begin(nodes_) + node_index;
            }
        }
        return std::end(nodes_);
    }
    
    context_params::iterator context_params::inner_emplace(const std::string_view key, std::string_view value, const std::uint16_t hash)
    {
        hashs_.push_back(hash);
        nodes_.emplace_back(key, value);

        return std::rend(nodes_).base();
    }
    
    context_params::iterator context_params::inner_insert(std::pair<std::string, std::string_view> node, const std::uint16_t hash)
    {
        hashs_.push_back(hash);
        nodes_.push_back(std::move(node));

        return std::rend(nodes_).base();
    }
}

