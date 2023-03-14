#include <cstdint>
#include <random>

__attribute__((noinline)) uint8_t ClampFloatVal(float v) {
    return static_cast<uint8_t>(std::max(0.f, std::min(255.f, v + .5f)));
}

__attribute__((noinline)) uint8_t ClampFloatRef(const float& v) {
    return static_cast<uint8_t>(std::max(0.f, std::min(255.f, v + .5f)));
}

float GetRandomFloat() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dist(-1000, 1000);
    return dist(gen);
}

static void TestClampVal(benchmark::State& state) {
    float v0 = GetRandomFloat(), v1 = GetRandomFloat(), v2 = GetRandomFloat(), v3 = GetRandomFloat();

    // код внутри этого цикла будет измеряться
    for (auto _ : state) {
        benchmark::DoNotOptimize(ClampFloatVal(v0) + ClampFloatVal(v1) + ClampFloatVal(v2) + ClampFloatVal(v3));
    }
}
// регистрируем функцию как задачу
BENCHMARK(TestClampVal);

static void TestClampRef(benchmark::State& state) {
    float v0 = GetRandomFloat(), v1 = GetRandomFloat(), v2 = GetRandomFloat(), v3 = GetRandomFloat();

    // код внутри этого цикла будет измеряться
    for (auto _ : state) {
        benchmark::DoNotOptimize(ClampFloatRef(v0) + ClampFloatRef(v1) + ClampFloatRef(v2) + ClampFloatRef(v3));
    }
}
// регистрируем функцию как задачу
BENCHMARK(TestClampRef);
