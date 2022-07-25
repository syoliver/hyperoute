#pragma once

#ifndef __HYPEROUTE__ROUTE_SCRATCH_H__
#define __HYPEROUTE__ROUTE_SCRATCH_H__

#include <hyperoute/ch_forward.hpp>
#include <hyperoute/route_line.hpp>
#include <vector>
#include <memory>

namespace hyperoute
{
    class route_scratch
    {

    public:
        route_scratch(const ch_database_t* db, const std::vector<route_line_t>& route_lines);

        ch_scratch_t* scratch() const;

        context_t& context(std::size_t index) const;

    private:
        std::shared_ptr<ch_scratch_t> scratch_;
        mutable std::vector<context_t> contexts_;
    };
}

#endif