#pragma once

#ifndef __HYPEROUTE__ERROR_CATEGORY_H__
#define __HYPEROUTE__ERROR_CATEGORY_H__

#include <hyperoute/error.hpp>
#include <system_error>

namespace hyperoute
{

    class error_category : public std::error_category
    {
    public:
        virtual ~error_category();
        virtual const char* name() const noexcept override;
        virtual std::string message( int condition ) const override;
    };
}

#endif