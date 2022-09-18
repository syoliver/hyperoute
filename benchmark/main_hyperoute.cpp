#include "benchmark/benchmark.h"

#include <backend/hyperscan_router.hpp>
#include <backend/boost_router.hpp>
#include <hyperoute/route_context.hpp>
#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>
#include <valgrind/callgrind.h>
#ifdef WITH_R3
#   include <r3.h>
#endif

#include <optional>

#include <iostream>

#include "bench_google.hpp"

BENCHMARK_MAIN();
