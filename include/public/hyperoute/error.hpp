#pragma once

#ifndef __HYPEROUTE__ERROR_H__
#define __HYPEROUTE__ERROR_H__

#include <hyperoute/hyperoute_export.hpp>
#include <system_error>

namespace hyperoute
{
    const std::error_category& category();

    enum class error
    {
        success = 0,
        unbalanced_brace,
        regex_syntax,
        duplicate_parameter
    };

    HYPEROUTE_EXPORT std::error_condition make_error_condition(::hyperoute::error err) noexcept;
}

namespace std
{
    template <>
    struct is_error_condition_enum<::hyperoute::error> : public true_type {};

}

#endif
