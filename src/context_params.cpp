
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
    
    void context_params::clear()
    {
        hashs_.clear();
        nodes_.clear();
    }
    
    std::pair<context_params::iterator, bool> context_params::insert( const_iterator hint, const value_type& value )
    {
        static const boost::hash<std::string_view> hasher;
        const auto hash = hasher(value.first);
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
        const auto hash = hasher(value.first);
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
        const auto hash = hasher(key);
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

        const auto search_hash = hasher(key);

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


    context_params::iterator context_params::inner_find(const std::string_view key, const std::size_t search_hash)
    {
        const auto iter_end = std::end(hashs_);
        auto iter = std::lower_bound(
            std::begin(hashs_),
            iter_end,
            std::pair<std::size_t, std::size_t>(search_hash, 0),
            [](const auto& lhs, const auto& rhs){
                return lhs.first < rhs.first;
        });

        while(iter != iter_end && iter->first == search_hash)
        {
            if(nodes_[iter->second].first == key)
            {
                return std::begin(nodes_) + (iter - std::begin(hashs_));
            }
            ++iter;
        }
        return std::end(nodes_);
    }
    
    context_params::iterator context_params::inner_emplace(const std::string_view key, std::string_view value, const std::size_t hash)
    {
        hashs_.push_back(std::pair(hash, nodes_.size()));
        nodes_.emplace_back(key, value);

        std::sort(std::begin(hashs_), std::end(hashs_), [](const auto& lhs, const auto& rhs){
            return lhs.first < rhs.first;
        });

        return std::rend(nodes_).base();
    }
    
    context_params::iterator context_params::inner_insert(std::pair<std::string, std::string_view> node, const std::size_t hash)
    {
        hashs_.push_back(std::pair(hash, nodes_.size()));
        nodes_.push_back(std::move(node));

        std::sort(std::begin(hashs_), std::end(hashs_), [](const auto& lhs, const auto& rhs){
            return lhs.first < rhs.first;
        });

        return std::rend(nodes_).base();
    }
}

