// Параметр n - лёгкий объект, передавать его через const int& нет смысла
int ComputeFactorial(int n) {
    return n <= 0 ? 1 : n * ComputeFactorial(n - 1);
}

struct Elephant {
    array<ElephantLeg, 4> heavy_leg;
    ElephantTrunk heavy_trunk;
    ElephantBody heavy_body;
};

// Передавать elephant по значению не нужно - это тяжёлый объект, который
// имеет большое значение sizeof
uint64_t ComputeWeight(const Elephant& elephant);
