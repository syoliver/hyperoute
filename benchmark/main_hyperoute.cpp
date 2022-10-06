#include "benchmark/benchmark.h"

#include <hyperoute/backend/hyperscan.hpp>
#include <hyperoute/backend/boost.hpp>
#include <hyperoute/backend/simple.hpp>
#include <hyperoute/route_context.hpp>
#include <hyperoute/builder.hpp>
#include <hyperoute/router.hpp>

#ifdef VALGRIND_BENCHMARK
#	include <valgrind/callgrind.h>
#else
#	define CALLGRIND_START_INSTRUMENTATION
#	define CALLGRIND_STOP_INSTRUMENTATION
#	define CALLGRIND_TOGGLE_COLLECT
#	define CALLGRIND_TOGGLE_COLLECT
#endif

#ifdef WITH_R3
#   include <r3.h>
#endif

#ifdef WITH_HTTP_ROUTER
#   include <HttpRouter.hpp>
#endif

#include <optional>

#include <iostream>

#include "bench_google.hpp"
#include "bench_github.hpp"

BENCHMARK_MAIN();
