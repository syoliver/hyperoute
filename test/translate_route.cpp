#define BOOST_TEST_MODULE TestHyperRoute::TranslateRoute
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <translate.hpp>
#include <hyperoute/error.hpp>

BOOST_DATA_TEST_CASE( translation_unamed, boost::unit_test::data::make({ true, false }), prefix_mode)
{
    std::error_condition ec;
    const auto result = hyperoute::translate_route("/vehicle/{id}", prefix_mode, ec);
    BOOST_TEST(!ec);

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
    std::error_condition ec;
    const auto result = hyperoute::translate_route("/vehicle/{id:\\w+}/name", prefix_mode, ec);
    BOOST_TEST(!ec);

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
    std::error_condition ec;
    const auto result = hyperoute::translate_route("/vehicle/{id:(abc)|(def)}/{name}", prefix_mode, ec);
    BOOST_TEST(!ec);
    
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
    std::error_condition ec;
    const auto result = hyperoute::translate_route("/vehicle/{id:\\w{3}}", prefix_mode, ec);
    BOOST_TEST(!ec);

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
    std::error_condition ec;
    const auto result = hyperoute::translate_route("/vehicle.().{id:\\w{3}", prefix_mode, ec);
    BOOST_TEST(!ec);

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

BOOST_DATA_TEST_CASE( translation_failure_brace_not_balanced, boost::unit_test::data::make({ true, false }), prefix_mode)
{

    {
        std::error_condition ec;
        const auto result = hyperoute::translate_route("/vehicle/{id:{", prefix_mode, ec);
        BOOST_TEST((ec == hyperoute::error::unbalanced_brace), "check ec == hyperoute::error::unbalanced_brace has failed [ec == " << ec.message() << "]");
    }

    {
        std::error_condition ec;
        const auto result = hyperoute::translate_route("/vehicle}", prefix_mode, ec);
        BOOST_TEST((ec == hyperoute::error::unbalanced_brace), "check ec == hyperoute::error::unbalanced_brace has failed [ec == " << ec.message() << "]");
    }

    {
        std::error_condition ec;
        const auto result = hyperoute::translate_route("/vehicle\\}", prefix_mode, ec);
        BOOST_TEST(!ec);
        BOOST_TEST(result.first == std::string("^\\/vehicle\\}") + (prefix_mode?"":"$"));
        BOOST_TEST(result.second.empty());
    }


    {
        std::error_condition ec;
        const auto result = hyperoute::translate_route("/vehicle\\{", prefix_mode, ec);
        BOOST_TEST(!ec);
        BOOST_TEST(result.first == std::string("^\\/vehicle\\{") + (prefix_mode?"":"$"));
        BOOST_TEST(result.second.empty());
    }

    {
        std::error_condition ec;
        const auto result = hyperoute::translate_route("/vehicle\\{\\}/two", prefix_mode, ec);
        BOOST_TEST(!ec);
        BOOST_TEST(result.first == std::string("^\\/vehicle\\{\\}\\/two") + (prefix_mode?"":"$"));
        BOOST_TEST(result.second.empty());
    }


    {
        std::error_condition ec;
        const auto result = hyperoute::translate_route("/vehicle/{id:[0-9]{3}}", prefix_mode, ec);
        BOOST_TEST(!ec);
        BOOST_TEST(result.first == std::string("^\\/vehicle\\/([0-9]{3})") + (prefix_mode?"":"$"));
        BOOST_TEST(result.second.size() == 1);
        BOOST_TEST(result.second[0].name == "id");
        BOOST_TEST(result.second[0].group == 1);
    }
}


