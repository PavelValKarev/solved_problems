
// https://quick-bench.com/q/4nfSMr2kTDVIWJTNEZqPt2qO5kk
// compare throw and variant

static void TestReturn(benchmark::State& state) {
    for (auto _ : state) {
        array stat = {0, 0, 0, 0, 0};
        for (int i = 0; i < ITER_COUNT; ++i) {
            const auto result = GraduateReturn(++i);
            if (holds_alternative<Diploma>(result)) {
                const auto diploma = get<Diploma>(result);
                stat[4] += diploma.x;
            } else {
                const auto reason = get<GraduateFailReason>(result);
                ++stat[static_cast<int>(reason)];
            }
        }
        benchmark::DoNotOptimize(stat);
    }
}
BENCHMARK(TestReturn);

static void TestExcept(benchmark::State& state) {
    for (auto _ : state) {
        array stat = {0, 0, 0, 0, 0};
        for (int i = 0; i < ITER_COUNT; ++i) {
            try {
                Diploma ans = GraduateExcept(++i);
                stat[4] += ans.x;
            }
            catch (GraduateFailReason reason) {
                ++stat[static_cast<int>(reason)];
            }
        }
        benchmark::DoNotOptimize(stat);
    }
}
BENCHMARK(TestExcept);
