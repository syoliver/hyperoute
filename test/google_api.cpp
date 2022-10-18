#define BOOST_TEST_MODULE TestHyperRoute_GoogleApi
#include <hyperoute/backend/boost.hpp>
#include <hyperoute/backend/hyperscan.hpp>
#include <hyperoute/backend/simple.hpp>
#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>

#include <turtle/mock.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/included/unit_test.hpp>

struct GoogleApi_Fixture
{
    GoogleApi_Fixture() {}

    ~GoogleApi_Fixture() {}

    template<typename Backend>
    std::optional<hyperoute::router> create_router(Backend backend)
    {
        hyperoute::builder builder(backend);

        // clang-format off
        std::error_condition ec;
        builder.add_route("/people/{userId}"                            , ec, ctx_1).methods({"GET"});
        builder.add_route("/people"                                     , ec, ctx_2).methods({"GET"});
        builder.add_route("/activities/{activityId}/people/{collection}", ec, ctx_3).methods({"GET"});
        builder.add_route("/people/{userId}/people/{collection}"        , ec, ctx_4).methods({"GET"});
        builder.add_route("/people/{userId}/openIdConnect"              , ec, ctx_5).methods({"GET"});

        // Activities
        builder.add_route("/people/{userId}/activities/{collection}"    , ec, ctx_6).methods({"GET"});
        builder.add_route("/activities/{activityId}"                    , ec, ctx_7).methods({"GET"});
        builder.add_route("/activities"                                 , ec, ctx_8).methods({"GET"});

        // Comments
        builder.add_route("/activities/{activityId}/comments"           , ec, ctx_9).methods({"GET"});
        builder.add_route("/comments/{commentId}"                       , ec, ctx_10).methods({"GET"});

        // Moments
        builder.add_route("/people/{userId}/moments/{collection}"       , ec, ctx_11).methods({"POST"});
        builder.add_route("/people/{userId}/moments/{collection}"       , ec, ctx_12).methods({"GET"});
        builder.add_route("/moments/{id}"                               , ec, ctx_13).methods({"DELETE"});
        // clang-format on

        return builder.build(ec);
    }

    MOCK_FUNCTOR(ctx_1, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_2, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_3, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_4, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_5, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_6, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_7, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_8, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_9, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_10, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_11, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_12, void(const hyperoute::route_context &));
    MOCK_FUNCTOR(ctx_13, void(const hyperoute::route_context &));
};

BOOST_AUTO_TEST_SUITE(GoogleApi)
    // clang-format off
    const auto test_backends = []() {
        return boost::unit_test::data::make({ "simple"                         , "hyperscan"                         , "boost" })
             ^ boost::unit_test::data::make({ hyperoute::backend::make_simple(), hyperoute::backend::make_hyperscan(), hyperoute::backend::make_boost() });
    };
    // clang-format on

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_1, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_1).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("userId")->second == "jzepdzdzm";
        });

        router->call("GET", "/people/jzepdzdzm");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_2, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_2).once().with([](const hyperoute::route_context &ctx) { return true; });

        router->call("GET", "/people");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_3, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_3).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("activityId")->second == "dzdzdzfezfzedz"
                && ctx.params.find("collection")->second == "brhgdssdgrhgdvfdc";
        });

        router->call("GET", "/activities/dzdzdzfezfzedz/people/brhgdssdgrhgdvfdc");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_4, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_4).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("userId")->second == "89616351684"
                && ctx.params.find("collection")->second == "1565135454";
        });
        router->call("GET", "/people/89616351684/people/1565135454");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_5, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_5).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("userId")->second == "6541321351";
        });
        router->call("GET", "/people/6541321351/openIdConnect");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_6, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_6).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("userId")->second == "846543544"
                && ctx.params.find("collection")->second == "684354684351";
        });
        router->call("GET", "/people/846543544/activities/684354684351");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_7, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_7).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("activityId")->second == "965435464654";
        });
        router->call("GET", "/activities/965435464654");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_8, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_8).once().with([](const hyperoute::route_context &ctx) { return ctx.params.empty(); }
        );
        router->call("GET", "/activities");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_9, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_9).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("activityId")->second == "841354684";
        });
        router->call("GET", "/activities/841354684/comments");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_10, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_10).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("commentId")->second == "643516546513546";
        });
        router->call("GET", "/comments/643516546513546");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_11, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_11).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("userId")->second == "165435498461"
                && ctx.params.find("collection")->second == "65454465454";
        });
        router->call("POST", "/people/165435498461/moments/65454465454");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_12, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_12).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("userId")->second == "165435498461"
                && ctx.params.find("collection")->second == "65454465454";
        });
        router->call("GET", "/people/165435498461/moments/65454465454");
    }

    BOOST_DATA_TEST_CASE_F(GoogleApi_Fixture, route_13, test_backends(), kind, backend)
    {
        const auto router = create_router(backend);

        MOCK_EXPECT(ctx_13).once().with([](const hyperoute::route_context &ctx) {
            return ctx.params.find("id")->second == "165454166584";
        });
        router->call("DELETE", "/moments/165454166584");
    }

BOOST_AUTO_TEST_SUITE_END()