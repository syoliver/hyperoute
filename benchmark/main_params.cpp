
#include "benchmark/benchmark.h"
#include <hyperoute/context_params.hpp>
#include <valgrind/callgrind.h>

template<typename Params>
class Hyperoute_params : public ::benchmark::Fixture
{
protected:

    Params params;
    void SetUp(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        params.emplace("cbhjscdslk", std::string_view());
        params.emplace("cbhj", std::string_view());
        params.emplace("vfevrzfzd", std::string_view());
        params.emplace("vfev", std::string_view());
        params.emplace("czdefesf", std::string_view());
        params.emplace("czde", std::string_view());
        params.emplace("nrntzgzefrfqcds", std::string_view());
        params.emplace("nrnt", std::string_view());
        params.emplace("erferffcsczc", std::string_view());
        params.emplace("erfe", std::string_view());
        params.emplace("cfezfezfzecd", std::string_view());
        params.emplace("cfez", std::string_view());
        params.emplace("efefesfdscsdfze", std::string_view());
        params.emplace("efef", std::string_view());
        params.emplace("rehrezedezdezd", std::string_view());
        params.emplace("rehr", std::string_view());
        params.emplace("vregrfezd", std::string_view());
        params.emplace("vreg", std::string_view());
        params.emplace("rgrehrjhrddez", std::string_view());
        params.emplace("rgre", std::string_view());
    }

    void TearDown(const ::benchmark::State& state) BENCHMARK_OVERRIDE
    {
        params.clear();
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
        benchmark::DoNotOptimize(params.find("viocndscksjos"));
        benchmark::DoNotOptimize(params.find("cbhj"));
        benchmark::DoNotOptimize(params.find("vfev"));
        benchmark::DoNotOptimize(params.find("czde"));
        benchmark::DoNotOptimize(params.find("nrnt"));
        benchmark::DoNotOptimize(params.find("erfe"));
        benchmark::DoNotOptimize(params.find("rehr"));
        benchmark::DoNotOptimize(params.find("vreg"));
        benchmark::DoNotOptimize(params.find("rgre"));
        CALLGRIND_TOGGLE_COLLECT;
    }
};

BENCHMARK_TEMPLATE_F(Hyperoute_params, basic_params, hyperoute::context_params)(benchmark::State& st)
{
    Execute(st);
}




BENCHMARK_MAIN();

