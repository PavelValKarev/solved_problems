#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <random>
#include <string_view>

//https://quick-bench.com/q/RpnpY63KQLUXImxV9cg0LqcDUbs

using namespace std;

// псевдоним для типа по итератору
template<typename Iterator>
using IterValType = decay_t<decltype(*declval<Iterator>())>;

// псевдоним для компаратора по типу
template<typename T>
using ComparatorByType = bool (const T& x, const T& y);

// псевдоним для компаратора по итератору
template<typename Iterator>
using ComparatorByIterator = ComparatorByType<IterValType<Iterator>>;

// псевдоним для компаратора по типу
template<typename T>
using PredicateByType = bool (const T& x);

// псевдоним для компаратора по итератору
template<typename Iterator>
using PredicateByIterator = PredicateByType<IterValType<Iterator>>;

template<typename RandomIt, typename Comp>
__attribute__((noinline)) auto SortTemplate(RandomIt first, RandomIt last, Comp comp) {
    return sort(first, last, move(comp));
}

template<typename RandomIt>
__attribute__((noinline)) auto SortFuncPtr(RandomIt first, RandomIt last, ComparatorByIterator<RandomIt>* comp) {
    return sort(first, last, comp);
}

template<typename RandomIt>
__attribute__((noinline)) auto SortFunction(RandomIt first, RandomIt last, const function<ComparatorByIterator<RandomIt>>& comp) {
    return sort(first, last, ref(comp));
}

vector<int> GenerateRandomVector(size_t size = 10000) {
    static mt19937 gen;
    vector<int> res(size);

    for(int& elem : res) {
        elem = uniform_int_distribution<int>(0, 1000)(gen);
    }

    return res;
}

auto random_vector = GenerateRandomVector(1000);

static void TestSortTemplate(benchmark::State& state) {
  auto vec = random_vector;

  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    SortTemplate(vec.begin(), vec.end(), [](int x, int y){
        return x < y;
    });
    SortTemplate(vec.begin(), vec.end(), [](int x, int y){
        return x > y;
    });
  }
}
// Register the function as a benchmark
BENCHMARK(TestSortTemplate);

bool Less(const int& x, const int& y) {
    return x < y;
}

bool Greater(const int& x, const int& y) {
    return x > y;
}

static void TestSortFuncPtr(benchmark::State& state) {
  auto vec = random_vector;

  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    SortFuncPtr(vec.begin(), vec.end(), Less);
    SortFuncPtr(vec.begin(), vec.end(), Greater);
  }
}
// Register the function as a benchmark
BENCHMARK(TestSortFuncPtr);


static void TestSortFunction(benchmark::State& state) {
  auto vec = random_vector;

  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    SortFunction(vec.begin(), vec.end(), [](int x, int y){
        return x < y;
    });
    SortFunction(vec.begin(), vec.end(), [](int x, int y){
        return x > y;
    });
  }
}
// Register the function as a benchmark
BENCHMARK(TestSortFunction);

