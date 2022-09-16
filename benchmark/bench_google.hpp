#pragma once

#ifndef __BENCH__HYPEROUTE__GOOGLE__H__
#define __BENCH__HYPEROUTE__GOOGLE__H__

// https://github.com/julienschmidt/go-http-routing-benchmark/blob/master/gplus_test.go

static void hyperoute_empty(const hyperoute::route_context&)
{

}

template<typename Backend>
class Google_HyperouteBenchmark : public ::benchmark::Fixture
{
protected:
    std::optional<hyperoute::router> r;

    void SetUp(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        auto backend = std::make_shared<Backend>();
        hyperoute::builder builder(backend);

        // People
        std::error_condition ec;
        builder.add_route("/people/{userId}"                            , ec, hyperoute_empty).methods({"GET"});
        builder.add_route("/people"                                     , ec, hyperoute_empty).methods({"GET"});
        builder.add_route("/activities/{activityId}/people/{collection}", ec, hyperoute_empty).methods({"GET"});
        builder.add_route("/people/{userId}/people/{collection}"        , ec, hyperoute_empty).methods({"GET"});
        builder.add_route("/people/{userId}/openIdConnect"              , ec, hyperoute_empty).methods({"GET"});

        // Activities
        builder.add_route("/people/{userId}/activities/{collection}"    , ec, hyperoute_empty).methods({"GET"});
        builder.add_route("/activities/{activityId}"                    , ec, hyperoute_empty).methods({"GET"});
        builder.add_route("/activities"                                 , ec, hyperoute_empty).methods({"GET"});

        // Comments
        builder.add_route("/activities/{activityId}/comments"           , ec, hyperoute_empty).methods({"GET"});
        builder.add_route("/comments/{commentId}"                       , ec, hyperoute_empty).methods({"GET"});

        // Moments
        builder.add_route("/people/{userId}/moments/{collection}"       , ec, hyperoute_empty).methods({"POST"});
        builder.add_route("/people/{userId}/moments/{collection}"       , ec, hyperoute_empty).methods({"GET"});
        builder.add_route("/moments/{id}"                               , ec, hyperoute_empty).methods({"DELETE"});

        r = builder.build(ec);
    }

    void TearDown(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        r = std::nullopt;
    }

    void Execute(::benchmark::State& state)
    {

        CALLGRIND_START_INSTRUMENTATION;
        for (auto _ : state)
        {
            Execute();
        }
        CALLGRIND_STOP_INSTRUMENTATION;
    }

    void Execute()
    {
        CALLGRIND_TOGGLE_COLLECT;
        r->call("GET", "/people");
        r->call("GET", "/people/118051310819094153327");
        r->call("GET", "/activities/84351354022154364354684/people/8412168431358451351");
        r->call("GET", "/people");
        r->call("POST", "/people/118051310819094153327/moments/8412168431358451351");
        r->call("GET", "/people");
        r->call("DELETE", "/moments/81546314631645295626595");
        r->call("GET", "/people");
        r->call("GET", "/activities/841516194169416161915126/comments");
        r->call("GET", "/not_found");

        r->call("GET", "/people");
        r->call("DELETE", "/moments/81546314631645295626595");
        r->call("GET", "/people");
        r->call("GET", "/people/118051310819094153327/moments/81546314631645295626595");
        r->call("GET", "/not_found");
        r->call("GET", "/people/118051310819094153327/people/81546314631645295626595");
        r->call("GET", "/people");
        r->call("GET", "/people/118051310819094153327/openIdConnect");
        r->call("GET", "/people/118051310819094153327");
        r->call("GET", "/people");
        CALLGRIND_TOGGLE_COLLECT;
    }
};

BENCHMARK_TEMPLATE_F(Google_HyperouteBenchmark, Hyperouter_Hyperscan, hyperoute::backend::hyperscan_router)(benchmark::State& st)
{
    Execute(st);
}

BENCHMARK_TEMPLATE_F(Google_HyperouteBenchmark, Hyperouter_Boost, hyperoute::backend::boost_router)(benchmark::State& st)
{
    Execute(st);
}

#ifdef WITH_R3

class Google_R3Benchmark : public ::benchmark::Fixture
{
protected:
    node *n = nullptr;

    int route_data[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    Google_R3Benchmark()
    {
    }

    void SetUp(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        n = r3_tree_create(10);

       // People
        r3_tree_insert_routel(n, METHOD_GET, "/people/{userId}", sizeof("/people/{userId}") - 1, &route_data[0]);
        r3_tree_insert_routel(n, METHOD_GET, "/people", sizeof("/people") - 1, &route_data[1]);
        r3_tree_insert_routel(n, METHOD_GET, "/activities/{activityId}/people/{collection}", sizeof("/activities/{activityId}/people/{collection}") - 1, &route_data[2]);
        r3_tree_insert_routel(n, METHOD_GET, "/people/{userId}/people/{collection}", sizeof("/people/{userId}/people/{collection}") - 1, &route_data[3]);
        r3_tree_insert_routel(n, METHOD_GET, "/people/{userId}/openIdConnect", sizeof("/people/{userId}/openIdConnect") - 1, &route_data[4]);

        // Activities
        r3_tree_insert_routel(n, METHOD_GET, "/people/{userId}/activities/{collection}", sizeof("/people/{userId}/activities/{collection}") - 1, &route_data[5]);
        r3_tree_insert_routel(n, METHOD_GET, "/activities/{activityId}", sizeof("/activities/{activityId}") - 1, &route_data[6]);
        r3_tree_insert_routel(n, METHOD_GET, "/activities", sizeof("/activities") - 1, &route_data[7]);

        // Comments
        r3_tree_insert_routel(n, METHOD_GET, "/activities/{activityId}/comments", sizeof("/activities/{activityId}/comments") - 1, &route_data[8]);
        r3_tree_insert_routel(n, METHOD_GET, "/comments/{commentId}", sizeof("/comments/{commentId}") - 1, &route_data[9]);

        // Moments
        r3_tree_insert_routel(n, METHOD_POST, "/people/{userId}/moments/{collection}", sizeof("/people/{userId}/moments/{collection}") - 1, &route_data[10]);
        r3_tree_insert_routel(n, METHOD_GET, "/people/{userId}/moments/{collection}", sizeof("/people/{userId}/moments/{collection}") - 1, &route_data[11]);
        r3_tree_insert_routel(n, METHOD_DELETE, "/moments/{id}", sizeof("/moments/{id}") - 1, &route_data[12]);


        char *errstr = NULL;
        int err = r3_tree_compile(n, &errstr);
        if(errstr != nullptr)
        {
            std::cout << "err = " << errstr;
        }
    }

    void TearDown(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        r3_tree_free(n);
        n = nullptr;
    }

    void Execute(::benchmark::State& state)
    {
        for (auto _ : state)
        {
            Execute();
        }
    }

    void CallRoute(int method, const char* path)
    {
        match_entry * entry = match_entry_create(path);
        entry->request_method = method;

        auto* matched_R3Route = r3_tree_match_route(n, entry);
        match_entry_free(entry);


    }

    void Execute()
    {
        CallRoute(METHOD_GET, "/people");
        CallRoute(METHOD_GET, "/people/118051310819094153327");
        CallRoute(METHOD_GET, "/activities/84351354022154364354684/people/8412168431358451351");
        CallRoute(METHOD_GET, "/people");
        CallRoute(METHOD_POST, "/people/118051310819094153327/moments/8412168431358451351");
        CallRoute(METHOD_GET, "/people");
        CallRoute(METHOD_DELETE, "/moments/81546314631645295626595");
        CallRoute(METHOD_GET, "/people");
        CallRoute(METHOD_GET, "/activities/841516194169416161915126/comments");
        CallRoute(METHOD_GET, "/not_found");

        CallRoute(METHOD_GET, "/people");
        CallRoute(METHOD_DELETE, "/moments/81546314631645295626595");
        CallRoute(METHOD_GET, "/people");
        CallRoute(METHOD_GET, "/people/118051310819094153327/moments/81546314631645295626595");
        CallRoute(METHOD_GET, "/not_found");
        CallRoute(METHOD_GET, "/people/118051310819094153327/people/81546314631645295626595");
        CallRoute(METHOD_GET, "/people");
        CallRoute(METHOD_GET, "/people/118051310819094153327/openIdConnect");
        CallRoute(METHOD_GET, "/people/118051310819094153327");
        CallRoute(METHOD_GET, "/people");

    }
};

BENCHMARK_F(Google_R3Benchmark, R3)(benchmark::State& st)
{
    Execute(st);
}

#endif

#endif