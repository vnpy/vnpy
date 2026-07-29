#include "matching_engine/matching_engine.hpp"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace vm = vnpy::matching;

namespace {

using Clock = std::chrono::steady_clock;

struct Options {
    std::size_t operations{200'000};
    std::uint64_t seed{42};
};

Options parse_options(int argc, char **argv) {
    Options options;
    for (int i = 1; i < argc; ++i) {
        const std::string argument = argv[i];
        if (argument == "--operations" && i + 1 < argc) {
            options.operations = std::stoull(argv[++i]);
        } else if (argument == "--seed" && i + 1 < argc) {
            options.seed = std::stoull(argv[++i]);
        } else if (argument == "--help" || argument == "-h") {
            std::cout << "Usage: matching_engine_bench [--operations N] [--seed N]\n";
            std::exit(0);
        } else {
            throw std::runtime_error("unknown argument: " + argument);
        }
    }
    if (options.operations == 0) {
        throw std::runtime_error("operations must be greater than zero");
    }
    return options;
}

std::uint64_t percentile(const std::vector<std::uint64_t> &sorted, double quantile) {
    const double raw_index = quantile * static_cast<double>(sorted.size() - 1);
    const auto index = static_cast<std::size_t>(raw_index);
    return sorted[index];
}

void print_distribution(std::string_view name, std::vector<std::uint64_t> &latencies) {
    if (latencies.empty()) {
        std::cout << name << "_operations=0\n";
        return;
    }

    std::sort(latencies.begin(), latencies.end());
    std::cout << name << "_operations=" << latencies.size() << '\n'
              << name << "_latency_p50_ns=" << percentile(latencies, 0.50) << '\n'
              << name << "_latency_p99_ns=" << percentile(latencies, 0.99) << '\n'
              << name << "_latency_p999_ns=" << percentile(latencies, 0.999) << '\n'
              << name << "_latency_max_ns=" << latencies.back() << '\n';
}

} // namespace

int main(int argc, char **argv) {
    try {
        const Options options = parse_options(argc, argv);
        vm::MatchingEngine engine;
        vm::EventBuffer events;
        events.reserve(32);

        std::mt19937_64 rng(options.seed);
        vm::OrderId next_id = 1;
        std::vector<vm::OrderId> cancel_candidates;
        cancel_candidates.reserve(options.operations + 10'000);

        // Warm the allocator and create a realistic multi-level book.
        for (std::size_t i = 0; i < 10'000; ++i) {
            const vm::Side side = (i & 1U) == 0 ? vm::Side::Buy : vm::Side::Sell;
            const vm::Price price = side == vm::Side::Buy
                                        ? 9'900 - static_cast<vm::Price>(i % 100)
                                        : 10'100 + static_cast<vm::Price>(i % 100);
            const vm::OrderId id = next_id++;
            engine.submit({id, side, vm::OrderType::Limit, price, 1 + i % 20}, events);
            cancel_candidates.push_back(id);
        }

        const std::size_t active_orders_initial = engine.active_order_count();
        std::vector<std::uint64_t> limit_latencies_ns;
        std::vector<std::uint64_t> cancel_latencies_ns;
        std::vector<std::uint64_t> market_latencies_ns;
        limit_latencies_ns.reserve(options.operations * 55 / 100 + 1);
        cancel_latencies_ns.reserve(options.operations * 35 / 100 + 1);
        market_latencies_ns.reserve(options.operations * 10 / 100 + 1);
        std::size_t events_generated = 0;
        std::size_t cancel_rejects = 0;

        const auto benchmark_start = Clock::now();
        for (std::size_t i = 0; i < options.operations; ++i) {
            const std::uint64_t choice = rng() % 100;

            if (choice < 55) {
                const vm::Side side = (rng() & 1U) == 0 ? vm::Side::Buy : vm::Side::Sell;
                const vm::Price price = side == vm::Side::Buy
                                            ? 9'900 - static_cast<vm::Price>(rng() % 100)
                                            : 10'100 + static_cast<vm::Price>(rng() % 100);
                const vm::OrderId id = next_id++;
                const vm::NewOrder request{id, side, vm::OrderType::Limit, price, 1 + rng() % 20};

                const auto start = Clock::now();
                engine.submit(request, events);
                const auto end = Clock::now();
                limit_latencies_ns.push_back(static_cast<std::uint64_t>(
                    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()));
                events_generated += events.size();
                cancel_candidates.push_back(id);
            } else if (choice < 90) {
                vm::OrderId id = 0;
                while (!cancel_candidates.empty()) {
                    const vm::OrderId candidate = cancel_candidates.back();
                    cancel_candidates.pop_back();
                    if (engine.contains(candidate)) {
                        id = candidate;
                        break;
                    }
                }

                const auto start = Clock::now();
                engine.cancel(id, events);
                const auto end = Clock::now();
                cancel_latencies_ns.push_back(static_cast<std::uint64_t>(
                    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()));
                events_generated += events.size();
                if (id == 0) {
                    ++cancel_rejects;
                }
            } else {
                const vm::Side side = (rng() & 1U) == 0 ? vm::Side::Buy : vm::Side::Sell;
                const vm::NewOrder request{next_id++, side, vm::OrderType::Market, 0,
                                           1 + rng() % 25};

                const auto start = Clock::now();
                engine.submit(request, events);
                const auto end = Clock::now();
                market_latencies_ns.push_back(static_cast<std::uint64_t>(
                    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()));
                events_generated += events.size();
            }
        }
        const auto benchmark_end = Clock::now();

        std::string invariant_error;
        if (!engine.check_invariants(&invariant_error)) {
            std::cerr << "invariant check failed: " << invariant_error << '\n';
            return 1;
        }

        const double wall_seconds =
            std::chrono::duration<double>(benchmark_end - benchmark_start).count();
        const double throughput = static_cast<double>(options.operations) / wall_seconds;

        std::cout << "benchmark=mixed_single_instrument\n"
                  << "operations=" << options.operations << '\n'
                  << "seed=" << options.seed << '\n'
                  << "workload=55%_resting_limit,35%_cancel,10%_market\n"
                  << std::fixed << std::setprecision(0)
                  << "throughput_ops_per_second=" << throughput << '\n'
                  << "events_generated=" << events_generated << '\n'
                  << "cancel_rejects=" << cancel_rejects << '\n'
                  << "active_orders_initial=" << active_orders_initial << '\n'
                  << "active_orders_final=" << engine.active_order_count() << '\n'
                  << "trades_final=" << engine.last_trade_id() << '\n';
        print_distribution("limit", limit_latencies_ns);
        print_distribution("cancel", cancel_latencies_ns);
        print_distribution("market", market_latencies_ns);
    } catch (const std::exception &exception) {
        std::cerr << "benchmark error: " << exception.what() << '\n';
        return 1;
    }

    return 0;
}
