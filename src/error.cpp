#include "error_category.hpp"

#include <hyperoute/error.hpp>

namespace hyperoute
{

const std::error_category &category()
{
    static error_category instance;
    return instance;
}

std::error_condition make_error_condition(::hyperoute::error err) noexcept
{
    return std::error_condition(static_cast<int>(err), ::hyperoute::category());
}

}  // namespace hyperoute
