#include <absl/container/flat_hash_map.h>
#include <benchmark/benchmark.h>

#include <map>
#include <string>
#include <unordered_map>

constexpr size_t elements = 100000;

static std::string gen_random_string(std::size_t const length) {
  static const char characters[] =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  std::string result{""};

  for (auto i{0U}; i < length; ++i) {
    result.push_back(characters[rand() % (sizeof(characters) - 1)]);
  }

  return result;
}

static void containers_map_insert(benchmark::State& state) {
  std::map<std::string, int> map;
  for (auto _ : state) {
    for (int i{0}; i < elements; ++i) {
      map.try_emplace(gen_random_string(9), (int)rand());
    }
    state.SetItemsProcessed(elements);
  }
}
BENCHMARK(containers_map_insert);

static void containers_unordered_map_insert(benchmark::State& state) {
  std::unordered_map<std::string, int> map;
  for (auto _ : state) {
    for (int i{0}; i < elements; ++i) {
      map.try_emplace(gen_random_string(9), (int)rand());
    }
    state.SetItemsProcessed(elements);
  }
}
BENCHMARK(containers_unordered_map_insert);

static void containers_absl_flat_hash_map_insert(benchmark::State& state) {
  absl::flat_hash_map<std::string, int> map;
  for (auto _ : state) {
    for (int i{0}; i < elements; ++i) {
      map.try_emplace(gen_random_string(9), (int)rand());
    }
    state.SetItemsProcessed(elements);
  }
}
BENCHMARK(containers_absl_flat_hash_map_insert);