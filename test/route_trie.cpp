#define BOOST_TEST_MODULE TestHyperRoute::RouteTrie
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <route_trie.hpp>

BOOST_AUTO_TEST_SUITE(route_prefix)

    BOOST_AUTO_TEST_CASE(insert_static_routes)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/a\\/path", 1));
        BOOST_TEST(trie.insert("^\\/another\\/path", 2));

        trie.print_trie();

        auto context = trie.create_search_context();

        {
            const auto opt_value = trie.search("/a/path/with/a/suffix", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);
            BOOST_TEST(context.match_end == std::strlen("/a/path"));
        }
        
        {
            const auto opt_value = trie.search("/another/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 2);
            BOOST_TEST(context.match_end == std::strlen("/another/path"));
        }

        {
            const auto opt_value = trie.search("/not/a/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value() == false);
        }
    }


    BOOST_AUTO_TEST_CASE(insert_static_before_prefix)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/a\\/path", 1));
        BOOST_TEST(trie.insert("^\\/a\\/path\\//with\\/a\\/suffix$", 2));

        trie.print_trie();

        auto context = trie.create_search_context();

        {
            const auto opt_value = trie.search("/a/path/with/a/suffix", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);
            BOOST_TEST(context.match_end == std::strlen("/a/path"));
        }
        
        {
            const auto opt_value = trie.search("/a/path/with/another/suffix", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);
            BOOST_TEST(context.match_end == std::strlen("/a/path"));
        }

        {
            const auto opt_value = trie.search("/not/a/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value() == false);
        }
    }

    BOOST_AUTO_TEST_CASE(insert_prefix_before_static)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/a\\/path\\/with\\/a\\/suffix$", 1));
        BOOST_TEST(trie.insert("^\\/a\\/path", 2));

        trie.print_trie();

        auto context = trie.create_search_context();

        {
            const auto opt_value = trie.search("/a/path/with/a/suffix", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);
            BOOST_TEST(context.match_end == std::strlen("/a/path/with/a/suffix"));
        }
        
        {
            const auto opt_value = trie.search("/a/path/with/another/suffix", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 2);
            BOOST_TEST(context.match_end == std::strlen("/a/path"));
        }

        {
            const auto opt_value = trie.search("/not/a/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value() == false);
        }
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(static_routes)

    BOOST_AUTO_TEST_CASE(insert_static_routes)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/a\\/path$", 1));
        BOOST_TEST(trie.insert("^\\/another\\/path$", 2));

        trie.print_trie();

        auto context = trie.create_search_context();

        {
            const auto opt_value = trie.search("/a/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);
        }
        
        {
            const auto opt_value = trie.search("/another/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 2);
        }

        {
            const auto opt_value = trie.search("/not/a/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value() == false);
        }
    }

    BOOST_AUTO_TEST_CASE(insert_dependent_static_routes)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/a$", 1));    
        BOOST_TEST(trie.insert("^\\/a\\/path$", 2));

        auto context = trie.create_search_context();

        {
            const auto opt_value = trie.search("/a", context);
            BOOST_TEST(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);
        }
        
        {
            const auto opt_value = trie.search("/a/path", context);
            BOOST_TEST(opt_value.has_value());
            BOOST_TEST(*opt_value == 2);
        }

        {
            const auto opt_value = trie.search("/a/path/that/doesn't/exit", context);
            BOOST_TEST(opt_value.has_value() == false);
        }
    }


    BOOST_AUTO_TEST_CASE(insert_twice_static_routes)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/a$", 1));
        BOOST_TEST(trie.insert("^\\/a$", 2) == false);
    }

    BOOST_AUTO_TEST_CASE(insert_complex_static_routes)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/a\\/path$", 1));
        BOOST_TEST(trie.insert("^\\/another\\/path$", 2));
        BOOST_TEST(trie.insert("^\\/second\\/path$", 3));
        BOOST_TEST(trie.insert("^\\/a\\/strange\\/path$", 4));
        BOOST_TEST(trie.insert("^\\/a\\/path\\/not\\/so\\/strange$", 5));
        BOOST_TEST(trie.insert("^\\/another\\/strange\\/path$", 6));
        BOOST_TEST(trie.insert("^\\/_\\/path$", 7));
        BOOST_TEST(trie.insert("^\\/an\\/imaginary\\/path$", 8));

        auto context = trie.create_search_context();

        BOOST_TEST(context.backtracking_depth() == 0);

        {
            const auto opt_value = trie.search("/a/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);
        }
        
        {
            const auto opt_value = trie.search("/another/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 2);
        }

        {
            const auto opt_value = trie.search("/second/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 3);
        }

        {
            const auto opt_value = trie.search("/_/path", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 7);
        }
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(matched_routes)
    BOOST_AUTO_TEST_CASE(insert_matched_routes)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/people\\/([^\\/]+)\\/moments\\/([^\\/]+)$", 1));
        BOOST_TEST(trie.insert("^\\/people\\/([^\\/]+)$", 2));
        BOOST_TEST(trie.insert("^\\/people$", 3));
        BOOST_TEST(trie.insert("^\\/people\\/([^\\/]+)/people/([^\\/]+)$", 4));
        BOOST_TEST(trie.insert("^\\/people\\/([^\\/]+)/openIdConnect$", 5));

        trie.print_trie();
        
        auto context = trie.create_search_context();

        BOOST_TEST(context.captures.capacity() == 2);
        BOOST_TEST(context.backtracking_depth() == 2);

        {
            const auto opt_value = trie.search("/people/454346561/moments/8496513", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);

            BOOST_TEST_REQUIRE(context.captures.size() == 2);
            BOOST_TEST(context.captures[0] == "454346561");
            BOOST_TEST(context.captures[1] == "8496513");
        }

        {
            const auto opt_value = trie.search("/people/65431514", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 2);

            BOOST_TEST_REQUIRE(context.captures.size() == 1);
            BOOST_TEST(context.captures[0] == "65431514");
        }

        {
            const auto opt_value = trie.search("/people", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 3);
        }
        
        {
            const auto opt_value = trie.search("/people/8653513251/people/854635145841", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 4);

            BOOST_TEST_REQUIRE(context.captures.size() == 2);
            BOOST_TEST(context.captures[0] == "8653513251");
            BOOST_TEST(context.captures[1] == "854635145841");
        }

        {
            const auto opt_value = trie.search("/people/8456313514/openIdConnect", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 5);

            BOOST_TEST_REQUIRE(context.captures.size() == 1);
            BOOST_TEST(context.captures[0] == "8456313514");
        }
    }

    BOOST_AUTO_TEST_CASE(insert_conflicted_routes)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/people\\/([^\\/]+)\\/a_collection$", 1));
        BOOST_TEST(trie.insert("^\\/people\\/an_user\\/([^\\/]+)$", 2));

        auto context = trie.create_search_context();

        BOOST_TEST(context.captures.capacity() == 1);
        BOOST_TEST(context.backtracking_depth() == 2);

        {
            const auto opt_value = trie.search("/people/an_user/a_collection", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);
            
            BOOST_TEST_REQUIRE(context.captures.size() == 1);
            BOOST_TEST(context.captures[0] == "an_user");
        }

        {
            const auto opt_value = trie.search("/people/135413251/a_collection", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 1);
            
            BOOST_TEST_REQUIRE(context.captures.size() == 1);
            BOOST_TEST(context.captures[0] == "135413251");
        }

        {
            const auto opt_value = trie.search("/people/an_user/6543213", context);
            BOOST_TEST_REQUIRE(opt_value.has_value());
            BOOST_TEST(*opt_value == 2);
            
            BOOST_TEST_REQUIRE(context.captures.size() == 1);
            BOOST_TEST(context.captures[0] == "6543213");
        }
    }
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(parsing_error)
    BOOST_AUTO_TEST_CASE(insert_invalid_route)
    {
        hyperoute::route_trie trie;
        BOOST_TEST(trie.insert("^\\/people\\/)\\/a_collection$", 1) == false);

        BOOST_TEST(trie.insert("^\\/aaa(name)$", 2) == false);

        BOOST_TEST(trie.insert("^\\/people\\/(name)aaa$", 3) == false);

        BOOST_TEST(trie.insert("^(name)$", 4) == false);
    }
BOOST_AUTO_TEST_SUITE_END()
