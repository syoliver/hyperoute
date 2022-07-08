#define BOOST_TEST_MODULE TestHyperRoute
#include <boost/test/included/unit_test.hpp>
#include <translate.hpp>

BOOST_AUTO_TEST_CASE( translation_unamed )
{
    const auto result = translate_route("/vehicle/{id}");
    BOOST_TEST(result.first == "^\\/vehicle\\/([^\\/]+)$");
    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}

BOOST_AUTO_TEST_CASE( translation_named )
{
    const auto result = translate_route("/vehicle/{id:\\w+}/name");
    BOOST_TEST(result.first == "^\\/vehicle\\/(\\w+)\\/name$");
    BOOST_TEST(result.second.size() == 1);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
}

BOOST_AUTO_TEST_CASE( translation_inner_group )
{
    const auto result = translate_route("/vehicle/{id:(abc)|(def)}/{name}");
    BOOST_TEST(result.first == "^\\/vehicle\\/((abc)|(def))\\/([^\\/]+)$");
    BOOST_TEST(result.second.size() == 2);
    BOOST_TEST(result.second[0].name == "id");
    BOOST_TEST(result.second[0].group == 1);
    BOOST_TEST(result.second[1].name == "name");
    BOOST_TEST(result.second[1].group == 4);
}
