#include <absl/container/flat_hash_map.h>
#include <benchmark/benchmark.h>

#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

constexpr size_t elements = 100000;

static std::string gen_random_string(std::size_t const length) {
  static const char characters[] =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  std::string result{""};

  for (size_t i{0U}; i < length; ++i) {
    result.push_back(characters[rand() % (sizeof(characters) - 1)]);
  }

  return result;
}

template <typename MAP_TYPE>
static std::pair<MAP_TYPE, std::vector<std::string>> generate_map(
    std::size_t const items_count) {
  MAP_TYPE map;
  std::vector<std::string> keys;
  keys.reserve(items_count);
  for (size_t i{0}; i < items_count; ++i) {
    auto s = gen_random_string(9);
    map.try_emplace(s, (int)rand());
    keys.emplace_back(std::move(s));
  }

  return {map, keys};
}

static void containers_map_lookup(benchmark::State& state) {
  auto [map, keys] = generate_map<std::map<std::string, int>>(elements);
  for (auto _ : state) {
    for (size_t i{0}; i < elements; ++i) {
      auto& e = map.at(keys[i]);
      benchmark::DoNotOptimize(e);
    }
    state.SetItemsProcessed(elements);
  }
}
BENCHMARK(containers_map_lookup);

static void containers_unordered_map_lookup(benchmark::State& state) {
  auto [map, keys] =
      generate_map<std::unordered_map<std::string, int>>(elements);
  for (auto _ : state) {
    for (size_t i{0}; i < elements; ++i) {
      auto& e = map.at(keys[i]);
      benchmark::DoNotOptimize(e);
    }
    state.SetItemsProcessed(elements);
  }
}
BENCHMARK(containers_unordered_map_lookup);

static void containers_absl_flat_hash_map_lookup(benchmark::State& state) {
  auto [map, keys] =
      generate_map<absl::flat_hash_map<std::string, int>>(elements);
  for (auto _ : state) {
    for (size_t i{0}; i < elements; ++i) {
      auto& e = map.at(keys[i]);
      benchmark::DoNotOptimize(e);
    }
    state.SetItemsProcessed(elements);
  }
}
BENCHMARK(containers_absl_flat_hash_map_lookup);