#define BOOST_TEST_MODULE TestHyperRoute
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <turtle/mock.hpp>

#include <hyperoute/backend/hyperscan.hpp>
#include <hyperoute/backend/boost.hpp>
#include <hyperoute/backend/simple.hpp>
#include <hyperoute/route_context.hpp>
#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>
#include <hyperoute/error.hpp>

const auto regex_test_backends = []() {
    return boost::unit_test::data::make({ "hyperscan"                         , "boost" })
        ^ boost::unit_test::data::make({ hyperoute::backend::make_hyperscan(), hyperoute::backend::make_boost() });
};

const auto all_test_backends = []() {
    return boost::unit_test::data::make({ "simple"                         , "hyperscan"                         , "boost" })
         ^ boost::unit_test::data::make({ hyperoute::backend::make_simple(), hyperoute::backend::make_hyperscan(), hyperoute::backend::make_boost() });
};

BOOST_DATA_TEST_CASE( route, all_test_backends(), kind, backend)
{
    MOCK_FUNCTOR(first_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(second_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(third_ctx, void(const hyperoute::route_context&));

    hyperoute::builder builder(backend);
    
    std::error_condition ec;
    builder.add_route("/vehicle", ec, first_ctx);
    BOOST_TEST(!ec);

    builder.add_route("/vehicle/{id}", ec, third_ctx);
    BOOST_TEST(!ec);

    const auto router = builder.build(ec);
    BOOST_TEST(!ec);

    {
        MOCK_EXPECT(third_ctx).once().with([](const hyperoute::route_context& ctx){
            return ctx.params.find("id")->second == "012345.";
        });
        router->call("GET", "/vehicle/012345.");
    }
}


BOOST_DATA_TEST_CASE( route_regex, regex_test_backends(), kind, backend )
{
    MOCK_FUNCTOR(first_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(second_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(third_ctx, void(const hyperoute::route_context&));

    hyperoute::builder builder(backend);
    
    std::error_condition ec;
    builder.add_route("/vehicle", ec, first_ctx);
    BOOST_TEST(!ec);

    builder.add_route("/vehicle/{id:\\w+}.{type:\\w{3}}", ec, second_ctx);
    BOOST_TEST(!ec);

    builder.add_route("/vehicle/{id}", ec, third_ctx);
    BOOST_TEST(!ec);

    const auto router = builder.build(ec);
    BOOST_TEST(!ec);

    {
        MOCK_EXPECT(second_ctx).once().with([](const hyperoute::route_context& ctx){
            return ctx.params.find("id")->second == "012345" && ctx.params.find("type")->second == "csv";
        });
        router->call("GET", "/vehicle/012345.csv");
        mock::verify();
    }

    {
        MOCK_EXPECT(third_ctx).once().with([](const hyperoute::route_context& ctx){
            return ctx.params.find("id")->second == "012345.";
        });
        router->call("GET", "/vehicle/012345.");
    }
}

BOOST_DATA_TEST_CASE( route_prefix, all_test_backends(), kind, backend )
{
    MOCK_FUNCTOR(first_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(second_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(third_ctx, void(const hyperoute::route_context&));

    hyperoute::builder builder(backend);

    std::error_condition ec;

    builder.add_route_prefix("/static_1/{id}", ec, first_ctx);
    BOOST_TEST(!ec);

    builder.add_route_prefix("/static_2/{id}", ec, second_ctx);
    BOOST_TEST(!ec);

    builder.add_route_prefix("/static_3/{id}", ec, third_ctx);
    BOOST_TEST(!ec);

    const auto router = builder.build(ec);
    BOOST_TEST(!ec);

    {
        MOCK_EXPECT(second_ctx).once().with([](const hyperoute::route_context& ctx){
            return ctx.matched_path == "/static_2/a" && ctx.remaining_path == "/file/path" && ctx.params.find("id")->second == "a";
        });
        router->call("GET", "/static_2/a/file/path");
        mock::verify();
    }
}

BOOST_DATA_TEST_CASE( route_not_found, all_test_backends(), kind, backend )
{
    hyperoute::builder builder(backend);

    std::error_condition ec;

    const auto router = builder.build(ec);
    BOOST_TEST(!ec);

    router->call("GET", "/a/file/path");

    new int(3);
}


BOOST_DATA_TEST_CASE( route_empty_prefix, all_test_backends(), kind, backend )
{
    MOCK_FUNCTOR(mock_ctx, void(const hyperoute::route_context&));

    hyperoute::builder builder(backend);

    std::error_condition ec;

    builder.add_route_prefix("", ec, mock_ctx);
    BOOST_TEST(!ec);

    const auto router = builder.build(ec);
    BOOST_TEST(!ec);

    {
        MOCK_EXPECT(mock_ctx).once().with([](const hyperoute::route_context& ctx){
            return ctx.matched_path.empty() && ctx.remaining_path == "/a/file/path" && ctx.params.empty();
        });
        router->call("GET", "/a/file/path");
    }
}


BOOST_DATA_TEST_CASE( route_verb, all_test_backends(), kind, backend )
{
    MOCK_FUNCTOR(first_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(second_ctx, void(const hyperoute::route_context&));

    hyperoute::builder builder(backend);

    std::error_condition ec;

    builder.add_route("/test", ec, first_ctx).methods({"GET", "POST"});
    BOOST_TEST(!ec);

    builder.add_route_prefix("/", ec, second_ctx);
    BOOST_TEST(!ec);

    const auto router = builder.build(ec);
    BOOST_TEST(!ec);

    {
        mock::sequence s;

        MOCK_EXPECT(first_ctx).once().with([](const hyperoute::route_context& ctx){
            return ctx.matched_path == "/test";
        }).in(s);

        MOCK_EXPECT(second_ctx).once().with([](const hyperoute::route_context& ctx){
            return ctx.matched_path == "/";
        }).in(s);

        router->call("GET", "/test");
        router->call("LIST", "/test");
    }
}


BOOST_DATA_TEST_CASE( add_route_failure_same_param_name, all_test_backends(), kind, backend )
{
    MOCK_FUNCTOR(first_ctx, void(const hyperoute::route_context&));
    hyperoute::builder builder(backend);

    std::error_condition ec;
    builder.add_route("/test/{name}/{name}", ec, first_ctx).methods({"GET"});
    BOOST_TEST(!ec);

    const auto router = builder.build(ec);
    BOOST_TEST((ec == hyperoute::error::duplicate_parameter), "check ec == hyperoute::error::duplicate_parameter has failed [ec == " << ec.message() << "]");
    BOOST_TEST(router.has_value() == false);
}


BOOST_DATA_TEST_CASE( add_route_failure_regex_syntax, regex_test_backends(), kind, backend )
{
    MOCK_FUNCTOR(first_ctx, void(const hyperoute::route_context&));
    hyperoute::builder builder(backend);

    std::error_condition ec;
    builder.add_route("/test/{name:)(*)}", ec, first_ctx).methods({"GET"});
    BOOST_TEST(!ec);

    const auto router = builder.build(ec);
    BOOST_TEST((ec == hyperoute::error::regex_syntax), "check ec == hyperoute::error::regex_syntax has failed [ec == " << ec.message() << "]");
    BOOST_TEST(router.has_value() == false);
}

