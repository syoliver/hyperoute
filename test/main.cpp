#define BOOST_TEST_MODULE TestHyperRoute
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <turtle/mock.hpp>

#include <hyperoute/backend/hyperscan.hpp>
#include <hyperoute/route_context.hpp>
#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>
#include <translate.hpp>

BOOST_DATA_TEST_CASE( translation_unamed, boost::unit_test::data::make({ true, false }), prefix_mode)
{
    const auto result = hyperoute::translate_route("/vehicle/{id}", prefix_mode);
    if(prefix_mode)
    {
        BOOST_TEST(result.first == "^\\/vehicle\\/([^\\/]+)");
    }
    else
    {
        BOOST_TEST(result.first == "^\\/vehicle\\/([^\\/]+)$");
    }
    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}

BOOST_DATA_TEST_CASE( translation_named, boost::unit_test::data::make({ true, false }), prefix_mode)
{
    const auto result = hyperoute::translate_route("/vehicle/{id:\\w+}/name", prefix_mode);
    if(prefix_mode)
    {
        BOOST_TEST(result.first == "^\\/vehicle\\/(\\w+)\\/name");
    }
    else
    {
        BOOST_TEST(result.first == "^\\/vehicle\\/(\\w+)\\/name$");
    }
    
    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}

BOOST_DATA_TEST_CASE( translation_inner_group, boost::unit_test::data::make({ true, false }), prefix_mode)
{
    const auto result = hyperoute::translate_route("/vehicle/{id:(abc)|(def)}/{name}", prefix_mode);
    if(prefix_mode)
    {
        BOOST_TEST(result.first == "^\\/vehicle\\/((abc)|(def))\\/([^\\/]+)");
    }
    else
    {
        BOOST_TEST(result.first == "^\\/vehicle\\/((abc)|(def))\\/([^\\/]+)$");
    }

    BOOST_TEST(result.second.size() == 2);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
    BOOST_TEST(result.second[1].name == "name");
    BOOST_TEST(result.second[1].group == 4);
}

BOOST_DATA_TEST_CASE( translation_inner_brace, boost::unit_test::data::make({ true, false }), prefix_mode)
{
    const auto result = hyperoute::translate_route("/vehicle/{id:\\w{3}}", prefix_mode);
    if(prefix_mode)
    {
        BOOST_TEST(result.first == "^\\/vehicle\\/(\\w{3})");
    }
    else
    {
        BOOST_TEST(result.first == "^\\/vehicle\\/(\\w{3})$");
    }

    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}


BOOST_DATA_TEST_CASE( translation_dot_brace, boost::unit_test::data::make({ true, false }), prefix_mode)
{
    const auto result = hyperoute::translate_route("/vehicle.().{id:\\w{3}", prefix_mode);
    if(prefix_mode)
    {
        BOOST_TEST(result.first == "^\\/vehicle\\.\\(\\)\\.\\w{3}");
    }
    else
    {
        BOOST_TEST(result.first == "^\\/vehicle\\.\\(\\)\\.\\w{3}$");
    }

    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}



BOOST_AUTO_TEST_CASE( route )
{
    MOCK_FUNCTOR(first_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(second_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(third_ctx, void(const hyperoute::route_context&));

    hyperoute::builder builder(hyperoute::backend::make_hyperscan());

    builder.add_route("/vehicle", first_ctx);
    builder.add_route("/vehicle/{id:\\w+}.{type:\\w{3}}", second_ctx);
    builder.add_route("/vehicle/{id}", third_ctx);

    const auto router = builder.build();

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

BOOST_AUTO_TEST_CASE( route_prefix )
{
    MOCK_FUNCTOR(first_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(second_ctx, void(const hyperoute::route_context&));
    MOCK_FUNCTOR(third_ctx, void(const hyperoute::route_context&));

    hyperoute::builder builder(hyperoute::backend::make_hyperscan());

    builder.add_route_prefix("/static_1/{id}", first_ctx);
    builder.add_route_prefix("/static_2/{id}", second_ctx);
    builder.add_route_prefix("/static_3/{id}", third_ctx);
    const auto router = builder.build();

    {
        MOCK_EXPECT(second_ctx).once().with([](const hyperoute::route_context& ctx){
            return ctx.matched_path == "/static_2/a" && ctx.remaining_path == "/file/path" && ctx.params.find("id")->second == "a";
        });
        router->call("GET", "/static_2/a/file/path");
        mock::verify();
    }
}