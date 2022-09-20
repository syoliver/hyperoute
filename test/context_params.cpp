#define BOOST_TEST_MODULE TestHyperRoute_Params
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <hyperoute/context_params.hpp>

BOOST_AUTO_TEST_SUITE(context_params)
    BOOST_AUTO_TEST_CASE(empty_context)
    {
        hyperoute::context_params params;

        BOOST_TEST(params.empty());
        BOOST_TEST(params.size() == 0);
    }

    BOOST_AUTO_TEST_CASE(find_not_found)
    {
        hyperoute::context_params params;

        BOOST_TEST(params.empty());

        bool success = false;
        std::tie(std::ignore, success) = params.emplace("index", std::string_view());
        BOOST_TEST(success);
        BOOST_TEST(params.empty() == false);
        BOOST_TEST(params.size() == 1);
        std::vector<std::string> values{"123456789"};
        
        auto iter_value = std::begin(values);
        auto iter_param = std::begin(params);
        for( ; iter_value != std::end(values) ; ++iter_value, ++iter_param)
        {
            iter_param->second = *iter_value;
        }

        BOOST_TEST((params.find("index") != std::end(params)));
        BOOST_TEST((params.find("collection") == std::end(params)));
    }

    BOOST_AUTO_TEST_CASE(analphabetic_insertion)
    {
        hyperoute::context_params params;

        bool success = false;
        std::tie(std::ignore, success) = params.emplace("userId", std::string_view());
        BOOST_TEST(success);

        std::tie(std::ignore, success) = params.emplace("collection", std::string_view());
        BOOST_TEST(success);
        BOOST_TEST(params.size() == 2);

        std::vector<std::string> values{"123456789", "987654321"};
        
        auto iter_value = std::begin(values);
        auto iter_param = std::begin(params);
        for( ; iter_value != std::end(values) ; ++iter_value, ++iter_param)
        {
            iter_param->second = *iter_value;
        }

        BOOST_TEST(params.find("userId")->second == "123456789");
        BOOST_TEST(params.find("collection")->second == "987654321");
    }

    BOOST_AUTO_TEST_CASE(alphabetic_insertion)
    {
        hyperoute::context_params params;
        bool success = false;
        std::tie(std::ignore, success) = params.emplace("collection", std::string_view());
        BOOST_TEST(success);

        std::tie(std::ignore, success) = params.emplace("userId", std::string_view());
        BOOST_TEST(success);

        BOOST_TEST(params.size() == 2);

        std::vector<std::string> values{"123456789", "987654321"};
        
        auto iter_value = std::begin(values);
        auto iter_param = std::begin(params);
        for( ; iter_value != std::end(values) ; ++iter_value, ++iter_param)
        {
            iter_param->second = *iter_value;
        }

        BOOST_TEST(params.find("userId")->second == "987654321");
        BOOST_TEST(params.find("collection")->second == "123456789");
    }

BOOST_AUTO_TEST_SUITE_END()