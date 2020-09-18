cmake_minimum_required(VERSION 3.13)
project(benchmarks)              
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(absl REQUIRED)
find_package(benchmark REQUIRED)
find_package(Boost COMPONENTS container REQUIRED)
find_package(Threads REQUIRED)

set(SOURCE_FILES
  src/allocations/boost_pmr.cpp
  src/containers/map_unordered_map_insert.cpp
  src/containers/map_unordered_map_lookup.cpp
)

add_executable(benchmarks ${SOURCE_FILES})
target_link_libraries(benchmarks
  absl::base
  absl::hash
  benchmark::benchmark
  benchmark::benchmark_main
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)
