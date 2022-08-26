#include <hyperoute/builder_route_modifier.hpp>
#include <hyperoute/builder.hpp>

namespace hyperoute
{

builder_route_modifier::builder_route_modifier(builder& build, std::size_t regex_index)
    : builder_(build)
    , regex_index_(regex_index)
{

}


builder_route_modifier& builder_route_modifier::methods(std::initializer_list<const char*> verbs) &&
{
    for(const char* verb: verbs)
    {
        builder_.regexes_[verb].insert(regex_index_);
        builder_.lines_[regex_index_].second = false;
    }
    
    return *this;
}

}
