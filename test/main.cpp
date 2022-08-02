#define BOOST_TEST_MODULE TestHyperRoute
#include <boost/test/included/unit_test.hpp>
#include <turtle/mock.hpp>

#include <hyperoute/backend/hyperscan.hpp>
#include <hyperoute/context.hpp>
#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>
#include <translate.hpp>

BOOST_AUTO_TEST_CASE( translation_unamed )
{
    const auto result = hyperoute::translate_route("/vehicle/{id}");
    BOOST_TEST(result.first == "^\\/vehicle\\/([^\\/]+)$");
    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}

BOOST_AUTO_TEST_CASE( translation_named )
{
    const auto result = hyperoute::translate_route("/vehicle/{id:\\w+}/name");
    BOOST_TEST(result.first == "^\\/vehicle\\/(\\w+)\\/name$");
    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}

BOOST_AUTO_TEST_CASE( translation_inner_group )
{
    const auto result = hyperoute::translate_route("/vehicle/{id:(abc)|(def)}/{name}");
    BOOST_TEST(result.first == "^\\/vehicle\\/((abc)|(def))\\/([^\\/]+)$");
    BOOST_TEST(result.second.size() == 2);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
    BOOST_TEST(result.second[1].name == "name");
    BOOST_TEST(result.second[1].group == 4);
}

BOOST_AUTO_TEST_CASE( translation_inner_brace )
{
    const auto result = hyperoute::translate_route("/vehicle/{id:\\w{3}");
    BOOST_TEST(result.first == "^\\/vehicle\\/\\w{3}$");
    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}


BOOST_AUTO_TEST_CASE( translation_dot_brace )
{
    const auto result = hyperoute::translate_route("/vehicle.().{id:\\w{3}");
    BOOST_TEST(result.first == "^\\/vehicle\\.\\(\\)\\.\\w{3}$");
    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}

BOOST_AUTO_TEST_CASE( route )
{
    MOCK_FUNCTOR(first_ctx, void(const hyperoute::context_t&));
    MOCK_FUNCTOR(second_ctx, void(const hyperoute::context_t&));
    MOCK_FUNCTOR(third_ctx, void(const hyperoute::context_t&));

    hyperoute::builder builder(hyperoute::backend::make_hyperscan());

    const auto router = builder.add_route("/vehicle", first_ctx)
                               .add_route("/vehicle/{id:\\w+}.{type:\\w{3}}", second_ctx)
                               .add_route("/vehicle/{id}", third_ctx)
                               .build();

    {
        MOCK_EXPECT(second_ctx).once().with([](const hyperoute::context_t& ctx){
            return ctx.find("id")->second == "012345" && ctx.find("type")->second == "csv";
        });
        router->call("/vehicle/012345.csv");
        mock::verify();
    }

    {
        MOCK_EXPECT(third_ctx).once().with([](const hyperoute::context_t& ctx){
            return ctx.find("id")->second == "012345.";
        });
        router->call("/vehicle/012345.");
    }

}
