
#include <route_trie.hpp>
#include <string_view>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <limits>

namespace hyperoute
{

using iterator = std::string_view::const_iterator;

namespace details
{
    struct backtracking_info
    {
        const details::trie_data* node;
        std::size_t captures_size;
        bool matched;
        std::string_view::const_iterator iterator;
    };
}

route_trie::search_context::~search_context() = default;

route_trie::search_context::search_context()
    : match_end(0)
{
}

route_trie::search_context::search_context(const search_context& other) = default;
route_trie::search_context::search_context(search_context&& other) = default;

std::size_t route_trie::search_context::backtracking_depth() const
{
    return backtracking_stack.capacity();
}

static void do_print_trie(const details::trie_node* node, std::size_t ident = 0)
{
    for(const auto& node: node->statics)
    {
        for(std::size_t i = 0 ; i < ident ; ++i) std::cout << "-";
        std::cout << "[" << (node.second.is_route_prefix ? "*":"") << node.second.route_index <<  "]: " << node.first << std::endl;
        do_print_trie(&node.second.node, ident+1);
    }

    if(node->matches != nullptr)
    {
        for(std::size_t i = 0 ; i < ident ; ++i) std::cout << "-";
        std::cout << "[" << (node->matches->is_route_prefix ? "*":"") << node->matches->route_index << "]: <MATCH>"  << std::endl;
        do_print_trie(&node->matches->node, ident+1);
    }
}

static std::pair<iterator, iterator> next_match(bool valid_match_preceding, iterator iter, iterator end)
{
    iterator begin_match = end;
    iterator end_match = end;
    bool skip = false;
    bool begin_found = false;
    bool end_found = false;
    for(; iter != end ; ++iter)
    {
        bool want_match_preceding = false;
        if(!skip)
        {
            if(*iter == '\'')
            {
                skip = true;
            }
            else if(*iter == '/')
            {
                want_match_preceding = true;
            }
            else if(*iter == '(')
            {
                if(valid_match_preceding == false)
                {
                    std::cout << "FAILURE FOR VALID MATCH PRECEDING" << std::endl;
                    // TODO: FAILURE...
                }
                begin_match = iter;
                begin_found = true;
            }
            else if(*iter == ')')
            {
                if(begin_found == false)
                {
                    std::cout << "FAILURE FOR VALID MATCH BEGIN IS MISSING" << std::endl;
                    // TODO: FAILURE...
                }
                else
                {
                    end_match = iter+1;
                    if((end_match != end) && (*end_match != '/'))
                    {
                        std::cout << "FAILURE FOR VALID MATCH ENDING" << std::endl;
                        // TODO: FAILURE...
                    }
                    end_found = true;
                    break;
                }
            }
        }
        else
        {
            skip = false;
        }
        valid_match_preceding = want_match_preceding;
    }
    if(begin_found && end_found == false)
    {
        // TODO: FAILURE...
    }
    return std::pair(begin_match, end_match);
}

namespace
{
    struct binary_search_comparator
    {
        bool operator()(const std::pair<std::string, details::trie_data>& lhs, const char value) const
        {
            if(lhs.first.empty())
            {
                return true;
            }
            return lhs.first[0] < value;
        }

        bool operator()(const char value, const std::pair<std::string, details::trie_data>& rhs) const
        {
            if(rhs.first.empty())
            {
                return true;
            }
            return value < rhs.first[0];
        }
    };
}

static std::tuple<details::trie_data*, iterator> find_prefix_in_node(details::trie_node* node, iterator iter_begin, iterator iter_end)
{
    std::size_t index = 0;
    auto iter = iter_begin;

    auto iter_statics = std::lower_bound(
        std::begin(node->statics),
        std::end(node->statics),
        *iter_begin,
        binary_search_comparator{}
    );

    if(iter_statics != std::end(node->statics) && (iter_statics->first[0] == *iter_begin))
    {
        while(index < iter_statics->first.size() && (iter != iter_end) && iter_statics->first[index] == *iter)
        {
            ++index;
            ++iter;
        }

        if(index == iter_statics->first.size())
        {
            return std::pair(&iter_statics->second, iter_begin+index);
        }
        else if(iter == iter_end)
        {
            details::trie_data new_node_data;
            std::swap(new_node_data, iter_statics->second);
            details::trie_node& parent_node = iter_statics->second.node;

            const std::string_view new_node_prefix =
                (iter == iter_begin) ? std::string_view{}:std::string_view(&*iter_begin, (iter - iter_begin));

            const std::string_view new_node_suffix =
                (iter == iter_end) ? std::string_view{}: std::string_view(&*iter, (iter_end - iter));
            
            parent_node.statics.emplace_back(iter_statics->first.substr(index), std::move(new_node_data));
            iter_statics->first = new_node_prefix;


            return std::pair(&iter_statics->second, iter_end);
        }

        // Create new node and split previous one
        details::trie_data new_node_data;
        std::swap(new_node_data, iter_statics->second);

        details::trie_node& parent_node = iter_statics->second.node;

        const std::string_view new_node_prefix(&*iter_begin, (iter - iter_begin));
        const std::string_view new_node_suffix(&*iter, (iter_end - iter));

        parent_node.statics.emplace_back(iter_statics->first.substr(index), std::move(new_node_data));

        iter_statics->first = new_node_prefix;


        auto iter_where = std::upper_bound(
            std::begin(parent_node.statics),
            std::end(parent_node.statics),
            new_node_suffix,
            [](const auto prefix, const auto& rhs) {
                return prefix < rhs.first;
        });

        auto iter_inserted = parent_node.statics.emplace(iter_where, new_node_suffix, details::trie_data{});

        return std::pair(&iter_inserted->second, iter_end);
    }

    const std::string_view new_node_prefix(&*iter_begin, (iter_end-iter_begin));
    
    auto iter_where = std::upper_bound(
        std::begin(node->statics),
        std::end(node->statics),
        new_node_prefix,
        [](const auto prefix, const auto& rhs) {
            return prefix < rhs.first;
    });

    auto iter_inserted = node->statics.emplace(iter_where, new_node_prefix, details::trie_data{});

    return std::pair(&iter_inserted->second, iter_end);
}

static std::pair<details::trie_data*, iterator> insert_in_node_static(details::trie_node* node, iterator iter_route, iterator iter_match_begin, iterator iter_match_end)
{
    details::trie_data* node_data = nullptr;
    while(iter_route != iter_match_begin)
    {
        std::tie(node_data, iter_route) = find_prefix_in_node(node, iter_route, iter_match_begin);
        node = &node_data->node;
    }
    return std::pair(node_data, iter_route);
}

static details::trie_data* insert_in_node_match(details::trie_node* node, iterator match_begin, iterator match_end)
{
    if(node->matches == nullptr)
    {
        node->matches = std::make_unique<details::trie_data>();
    }
    return &*node->matches;
}


static std::optional<std::string> sanitize_route(std::string_view route, bool& matching_route_prefix)
{
    std::ostringstream oss;

    std::string_view::const_iterator iter_begin = std::begin(route);
    std::string_view::const_iterator iter_end = std::end(route);

    bool valid_match_preceding = false;
    bool in_match = false;
    bool skip = false;

    matching_route_prefix = true;

    if(iter_begin == iter_end || *iter_begin != '^') return std::nullopt;
    ++iter_begin;

    auto iter_validation = iter_begin;
    std::string_view::const_iterator iter_begin_capture;

    while(iter_validation != iter_end)
    {
        if(skip == false)
        {
            switch(*iter_validation)
            {
                case '(':
                {
                    if(valid_match_preceding == false) return std::nullopt;
                    if(in_match) return std::nullopt;
                    in_match = true;
                    iter_begin_capture = iter_validation;
                    oss << '(';
                    break;
                }
                case ')':
                {
                    if(in_match == false) return std::nullopt;
                    if((std::next(iter_validation)==iter_end))
                    {
                        oss << ')';
                        return oss.str();
                    }
                    
                    if(*std::next(iter_validation) == '$' && std::next(std::next(iter_validation)) == iter_end)
                    {
                        matching_route_prefix = false;
                        oss << ')';
                        return oss.str();
                    }
                     
                    if(*std::next(iter_validation) != '/')
                    {

                        if(*std::next(iter_validation) == '\\' && std::next(std::next(iter_validation)) != iter_end && *std::next(std::next(iter_validation)) == '/')
                        {
                            // OK continue....
                        }
                        else
                        {
                            return std::nullopt;
                        }
                    }

                    if(std::string_view(&*iter_begin_capture, (iter_validation-iter_begin_capture)) != "([^\\/]+") return std::nullopt;
                    in_match = false;
                    oss << ')';
                    break;
                }
                case '/':
                {
                    if(in_match == false)
                    {
                        valid_match_preceding = true;
                        oss << '/';
                    }
                    break;
                }
                case '$':
                    if(in_match) return std::nullopt;
                    if(skip == false && (std::next(iter_validation) != iter_end)) return std::nullopt;
                    matching_route_prefix = false;
                    break;
                case '\\':
                {
                    skip = true;
                    break;
                }
                default:
                {
                    valid_match_preceding = false;
                    skip = false;
                    if(in_match == false)
                    {
                        oss << *iter_validation;
                    }
                }
            }
        }
        else
        {
            if(in_match == false)
            {
                if(*iter_validation == '/')
                {
                    valid_match_preceding = true;
                }

                oss << *iter_validation;
            }
            skip = false;
        }
        ++iter_validation;
    }
    return oss.str();
}

bool route_trie::insert(const std::string_view route, const std::size_t route_index)
{
    details::trie_node* node = &root_.node;
    details::trie_data* node_data = nullptr;
    
    bool matching_route_prefix = false;
    const auto sanitized_route = sanitize_route(route, matching_route_prefix);

    if(sanitized_route.has_value() == false)
    {
        return false;
    }

    std::string_view sanitized_route_view(*sanitized_route);
    auto iter_route = std::begin(sanitized_route_view);
    auto iter_end = std::end(sanitized_route_view);

    auto iter_match = iter_route;
    
    bool valid_match_preceding = false;
    while(true)
    {
        auto [match_begin, match_end] = next_match(valid_match_preceding, iter_route, iter_end);

        std::tie(node_data, iter_match) = insert_in_node_static(node, iter_route, match_begin, match_end);

        if(iter_match != match_end)
        {
            node_data = insert_in_node_match(&node_data->node, match_begin, match_end);
        }
        node = &node_data->node;
        
        if(match_end == iter_end)
        {
            break;
        }

        if(iter_route != match_end)
        {
            if(*std::prev(match_end) == '/')
            {
                valid_match_preceding = true;
            }
        }

        iter_route = match_end;
    }

    if(node_data != nullptr && node_data->route_index == 0)
    {
        node_data->route_index = route_index;
        node_data->is_route_prefix = matching_route_prefix;
        return true;
    }

    return false;
}

template<typename BackTracking>
static std::tuple<const details::trie_data*, bool, iterator> search_in_node(const details::trie_data* node_data, bool backtracking_mode, iterator iter, iterator iter_end, std::vector<std::string_view>& captures, std::vector<BackTracking>& backtracking_stack)
{
    if(backtracking_mode)
    {
        while(backtracking_stack.empty() == false && ((backtracking_stack.back().node->node.matches == nullptr) || (backtracking_stack.back().matched)))
        {
            backtracking_stack.pop_back();
        }

        if(backtracking_stack.empty())
        {
            return std::tuple(nullptr, true, iter_end);
        }

        auto& backtracking = backtracking_stack.back();
        captures.resize(backtracking.captures_size);

        {
            const auto iter_begin = backtracking.iterator;
            while((backtracking.iterator != iter_end) && (*backtracking.iterator != '/')) ++backtracking.iterator;
        
            captures.emplace_back(&*iter_begin, (backtracking.iterator - iter_begin));
            ++backtracking.captures_size;
            backtracking.matched = true;
        }

        return std::tuple(backtracking.node->node.matches.get(), false, backtracking.iterator);
    }

    auto iter_begin = iter;
    std::size_t index = 0;
    
    auto iter_statics = std::lower_bound(
        std::begin(node_data->node.statics),
        std::end(node_data->node.statics),
        *iter_begin,
        binary_search_comparator{}
    );


    const auto current_capture_size = (backtracking_stack.empty()?0:backtracking_stack.back().captures_size);

    if(iter_statics != std::end(node_data->node.statics) && (iter_statics->first[0] == *iter_begin))
    {
        while(index < iter_statics->first.size() && (iter != iter_end) && iter_statics->first[index] == *iter)
        {
            ++index;
            ++iter;
        }
        
        if(index == iter_statics->first.size())
        {
            if(node_data->node.matches != nullptr)
            {
                backtracking_stack.push_back({.node = node_data, .captures_size = current_capture_size, .matched = false, .iterator = iter_begin});
            }
            return std::tuple(&iter_statics->second, false, iter);
        }
    }
    
    iter = iter_begin;

    if(node_data->node.matches != nullptr)
    {
        while((iter != iter_end) && (*iter != '/'))
        {
            ++iter;
        }

        captures.emplace_back(&*iter_begin, (iter - iter_begin));
        backtracking_stack.push_back({.node = node_data, .captures_size = current_capture_size + 1, .matched = true, .iterator = iter});
        return std::tuple(node_data->node.matches.get(), false, iter);
    }


    // Begin backtracking...
    if(backtracking_stack.empty() == false)
    {
        if((backtracking_stack.back().node->node.matches == nullptr) || (backtracking_stack.back().matched))
        {
            backtracking_stack.pop_back();
        }
        
        if(backtracking_stack.empty() == false)
        {
            const auto& backtracking = backtracking_stack.back();

            return std::tuple(backtracking.node, true, backtracking.iterator);
        }
    }


    return std::tuple(nullptr, false, iter_end);
}



std::optional<std::size_t> route_trie::search(const std::string_view value, search_context& context) const
{
    context.captures.clear();
    context.pending_captures.clear();
    context.backtracking_stack.clear();

    auto iter_begin = std::begin(value);
    auto iter = iter_begin;
    auto iter_end = std::end(value);

    const auto* node_data = &root_;
    bool backtracking_mode = false;

    std::size_t current_route_index = std::numeric_limits<std::size_t>::max();
    
    do
    {
        std::tie(node_data, backtracking_mode, iter) = search_in_node(node_data, backtracking_mode, iter, iter_end, context.pending_captures, context.backtracking_stack);

        if((node_data != nullptr) && node_data->route_index < current_route_index)
        {
            if((iter == iter_end) && (node_data->is_route_prefix == false) || (node_data->is_route_prefix))
            {
                if(node_data->route_index > 0)
                {
                    current_route_index = node_data->route_index;
                    context.captures = context.pending_captures;
                    context.match_end = (iter - iter_begin);
                }
            }

            if(iter == iter_end)
            {
                backtracking_mode = true;
            }
        }

    } while((node_data != nullptr) && (context.backtracking_stack.empty() == false || backtracking_mode == false));

    if(current_route_index != std::numeric_limits<std::size_t>::max())
    {
        return current_route_index;
    }
    return std::nullopt;
}

void route_trie::print_trie() const
{
    std::cout << "-------------------------------" << std::endl;
    do_print_trie(&root_.node);
    std::cout << "-------------------------------" << std::endl;
}


static std::size_t max_captures(const details::trie_node* node)
{
    struct stack_node
    {
        const details::trie_node* node;
        std::size_t index;
        std::size_t depth;
    };

    std::size_t depth = 0;
    
    std::vector<stack_node> stack;
    stack.push_back({.node = node, .index = 0, .depth = 0});

    while(stack.empty() == false)
    {
        auto& stack_node = stack.back();
        if(stack_node.index < stack_node.node->statics.size())
        {
            stack.push_back({.node = &stack_node.node->statics[stack_node.index].second.node, .index = 0, .depth = stack_node.depth});
        }
        else if((stack_node.index == stack_node.node->statics.size()) && stack_node.node->matches != nullptr)
        {
            stack.push_back({.node = &stack_node.node->matches->node, .index = 0, .depth = stack_node.depth+1});
        }
        else
        {
            depth = std::max(stack_node.depth, depth);
            stack.pop_back();
            if(stack.empty() == false)
            {
                ++stack.back().index;
            }
        }
    }

    return depth;
}

static std::size_t max_backtracking(const details::trie_node* node)
{
    struct stack_node
    {
        const details::trie_node* node;
        std::size_t index;
        std::size_t depth;
    };

    std::size_t depth = 0;
    
    std::vector<stack_node> stack;
    stack.push_back({.node = node, .index = 0, .depth = 0});

    while(stack.empty() == false)
    {
        auto& stack_node = stack.back();
        if(stack_node.index < stack_node.node->statics.size())
        {
            const auto has_matches = (stack_node.node->matches != nullptr);

            stack.push_back({.node = &stack_node.node->statics[stack_node.index].second.node, .index = 0, .depth = stack_node.depth + (has_matches?1:0)});

        }
        else if((stack_node.index == stack_node.node->statics.size()) && stack_node.node->matches != nullptr)
        {
            stack.push_back({.node = &stack_node.node->matches->node, .index = 0, .depth = stack_node.depth+1});
        }
        else
        {
            depth = std::max(stack_node.depth, depth);
            stack.pop_back();
            if(stack.empty() == false)
            {
                ++stack.back().index;
            }
        }
    }

    return depth;
}

route_trie::search_context route_trie::create_search_context() const
{
    search_context ctx;

    ctx.captures.reserve(max_captures(&root_.node));
    ctx.backtracking_stack.reserve(max_backtracking(&root_.node));
    ctx.pending_captures.reserve(ctx.captures.capacity());

    return ctx;
}

}

