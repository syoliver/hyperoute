#include "error_category.hpp"

namespace hyperoute
{
/* virtual */ error_category::~error_category() = default;

/* virtual */ const char* error_category::name() const noexcept
{
    return "hyperoute";
}

/* virtual */ std::string error_category::message(const int condition) const
{
    switch(static_cast<error>(condition))
    {
    case error::unbalanced_brace:
        return "Unbalanced brace in route";
    case error::duplicate_parameter:
        return "Duplicate matched parameter in route";
    }
    return "success";
}

}