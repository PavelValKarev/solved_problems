// https://quick-bench.com/q/4nfSMr2kTDVIWJTNEZqPt2qO5kk
// compare throw and variant

static void TestReturn(benchmark::State& state) {
    for (auto _ : state) {
        array stat = { 0, 0, 0, 0, 0 };
        for (int i = 0; i < ITER_COUNT; ++i) {
            const auto result = GraduateReturn(++i);
            if (holds_alternative<Diploma>(result)) {
                const auto diploma = get<Diploma>(result);
                stat[4] += diploma.x;
            }
            else {
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
        array stat = { 0, 0, 0, 0, 0 };
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


/*
Большая разница объясняется тем, что вызываемая функция очень простая.
По сравнению с её кодом, издержки на исключения занимают много времени.
Если бы это была настоящая функция, формирующая PDF-документ диплома
и обращающаяся к базам данных, замедления от исключений никто бы не заметил.

Код обработчика проще читать и писать в случае исключений.
Это их преимущество. Можно сформулировать правило: исключение
действительно должно быть неожиданной, исключительной ситуацией,
которая может внезапно произойти и нарушить всю логику выполнения программы.
Ожидаемая ошибка при работе одной определённой функции к исключительным
ситуациям не относится, и лучше обрабатывать этот случай через распаковку
или variant.
*/
