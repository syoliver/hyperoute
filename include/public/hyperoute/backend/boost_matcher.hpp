#pragma once

#ifndef __HYPEROUTE__BACKEND__BOOST_MATCHER_H__
#define __HYPEROUTE__BACKEND__BOOST_MATCHER_H__

#include <hyperoute/backend/matcher_backend.hpp>
#include <hyperoute/route_context.hpp>
#include <boost/regex.hpp>
#include <string_view>
#include <memory>
#include <vector>
#include <optional>

namespace hyperoute::backend
{
    class boost_matcher : public matcher_backend
    {
    public:
        boost_matcher(std::shared_ptr<boost::regex> db, std::vector<route_context> contexts, std::shared_ptr<std::vector<std::size_t>> capture_indexes);
        virtual ~boost_matcher();
        virtual std::optional<matched> match(std::string_view url, const std::vector<route_line_t>& route_lines) override;

        route_context& context(std::size_t index);
    private:
        std::shared_ptr<boost::regex> db_;
        std::shared_ptr<std::vector<std::size_t>> capture_indexes_;
        std::vector<route_context> contexts_;
    };

}

#endif