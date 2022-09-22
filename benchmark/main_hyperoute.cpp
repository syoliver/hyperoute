#include "benchmark/benchmark.h"

#include <hyperoute/backend/hyperscan.hpp>
#include <hyperoute/backend/boost.hpp>
#include <hyperoute/backend/simple.hpp>
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
#include "bench_github.hpp"

BENCHMARK_MAIN();
