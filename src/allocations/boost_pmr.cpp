#include <benchmark/benchmark.h>

#include <boost/container/pmr/monotonic_buffer_resource.hpp>
#include <boost/container/pmr/unsynchronized_pool_resource.hpp>
#include <boost/container/pmr/vector.hpp>

constexpr size_t vector_elements_1{1024};
constexpr size_t vector_elements_2{1024 * 1024};

static void allocations_boost_pmr_pure_vector_pb(benchmark::State& state) {
  const auto vector_elements{state.range(0)};
  for (auto _ : state) {
    std::vector<size_t> v;
    for (size_t i{0}; i < vector_elements; ++i) {
      v.push_back(i);
    }
    state.SetItemsProcessed(vector_elements);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(allocations_boost_pmr_pure_vector_pb)
    ->Arg(vector_elements_1)
    ->Arg(vector_elements_2);

static void allocations_boost_pmr_pure_vector_eb(benchmark::State& state) {
  const auto vector_elements{state.range(0)};
  for (auto _ : state) {
    std::vector<size_t> v;
    for (size_t i{0}; i < vector_elements; ++i) {
      v.emplace_back(i);
    }
    state.SetItemsProcessed(vector_elements);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(allocations_boost_pmr_pure_vector_eb)
    ->Arg(vector_elements_1)
    ->Arg(vector_elements_2);

static void allocations_boost_pmr_reserve_vector_pb(benchmark::State& state) {
  const auto vector_elements{state.range(0)};
  for (auto _ : state) {
    std::vector<size_t> v;
    v.reserve(vector_elements);
    for (size_t i{0}; i < vector_elements; ++i) {
      v.push_back(i);
    }
    state.SetItemsProcessed(vector_elements);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(allocations_boost_pmr_reserve_vector_pb)
    ->Arg(vector_elements_1)
    ->Arg(vector_elements_2);

static void allocations_boost_pmr_reserve_vector_eb(benchmark::State& state) {
  const auto vector_elements{state.range(0)};
  for (auto _ : state) {
    std::vector<size_t> v;
    v.reserve(vector_elements);
    for (size_t i{0}; i < vector_elements; ++i) {
      v.emplace_back(i);
    }
    state.SetItemsProcessed(vector_elements);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(allocations_boost_pmr_reserve_vector_eb)
    ->Arg(vector_elements_1)
    ->Arg(vector_elements_2);

static void allocations_boost_pmr_pmr_vector_pb(benchmark::State& state) {
  const auto vector_elements{state.range(0)};
  for (auto _ : state) {
    auto pool_options{boost::container::pmr::pool_options{}};
    pool_options.max_blocks_per_chunk = 1024;
    pool_options.largest_required_pool_block = 1024 * 1024 * 8;
    const size_t resource_size = vector_elements * sizeof(int) + 1024;
    char buffer[resource_size];
    boost::container::pmr::monotonic_buffer_resource monotonic_resource{
        &buffer, resource_size};
    boost::container::pmr::unsynchronized_pool_resource resource{
        pool_options, &monotonic_resource};
    boost::container::pmr::polymorphic_allocator<int> alloc{&resource};
    boost::container::pmr::vector<int> v;
    for (size_t i{0}; i < vector_elements; ++i) {
      v.push_back(i);
    }
    state.SetItemsProcessed(vector_elements);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(allocations_boost_pmr_pmr_vector_pb)
    ->Arg(vector_elements_1)
    ->Arg(vector_elements_2);

static void allocations_boost_pmr_pmr_vector_eb(benchmark::State& state) {
  const auto vector_elements{state.range(0)};
  for (auto _ : state) {
    auto pool_options{boost::container::pmr::pool_options{}};
    pool_options.max_blocks_per_chunk = 1024;
    pool_options.largest_required_pool_block = 1024 * 1024 * 8;
    const size_t resource_size = 20 * vector_elements * sizeof(int) + 1024;
    char buffer[resource_size];
    boost::container::pmr::monotonic_buffer_resource monotonic_resource{
        &buffer, resource_size};
    boost::container::pmr::unsynchronized_pool_resource resource{
        pool_options, &monotonic_resource};
    boost::container::pmr::polymorphic_allocator<int> alloc{&resource};
    boost::container::pmr::vector<int> v;
    for (size_t i{0}; i < vector_elements; ++i) {
      v.emplace_back(i);
    }
    state.SetItemsProcessed(vector_elements);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(allocations_boost_pmr_pmr_vector_eb)
    ->Arg(vector_elements_1)
    ->Arg(vector_elements_2);

static void allocations_boost_pmr_pmr_reserve_vector_pb(
    benchmark::State& state) {
  const auto vector_elements{state.range(0)};
  for (auto _ : state) {
    auto pool_options{boost::container::pmr::pool_options{}};
    pool_options.max_blocks_per_chunk = 1024;
    pool_options.largest_required_pool_block = 1024 * 1024 * 8;
    const size_t resource_size = vector_elements * sizeof(int) + 1024;
    char buffer[resource_size];
    boost::container::pmr::monotonic_buffer_resource monotonic_resource{
        &buffer, resource_size};
    boost::container::pmr::unsynchronized_pool_resource resource{
        pool_options, &monotonic_resource};
    boost::container::pmr::polymorphic_allocator<int> alloc{&resource};
    boost::container::pmr::vector<int> v;
    v.reserve(vector_elements);
    for (size_t i{0}; i < vector_elements; ++i) {
      v.push_back(i);
    }
    state.SetItemsProcessed(vector_elements);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(allocations_boost_pmr_pmr_reserve_vector_pb)
    ->Arg(vector_elements_1)
    ->Arg(vector_elements_2);

static void allocations_boost_pmr_pmr_reserve_vector_eb(
    benchmark::State& state) {
  const auto vector_elements{state.range(0)};
  for (auto _ : state) {
    auto pool_options{boost::container::pmr::pool_options{}};
    pool_options.max_blocks_per_chunk = 1024;
    pool_options.largest_required_pool_block = 1024 * 1024 * 8;
    const size_t resource_size = vector_elements * sizeof(int) + 1024;
    char buffer[resource_size];
    boost::container::pmr::monotonic_buffer_resource monotonic_resource{
        &buffer, resource_size};
    boost::container::pmr::unsynchronized_pool_resource resource{
        pool_options, &monotonic_resource};
    boost::container::pmr::polymorphic_allocator<int> alloc{&resource};
    boost::container::pmr::vector<int> v;
    v.reserve(vector_elements);
    for (size_t i{0}; i < vector_elements; ++i) {
      v.emplace_back(i);
    }
    state.SetItemsProcessed(vector_elements);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(allocations_boost_pmr_pmr_reserve_vector_eb)
    ->Arg(vector_elements_1)
    ->Arg(vector_elements_2);