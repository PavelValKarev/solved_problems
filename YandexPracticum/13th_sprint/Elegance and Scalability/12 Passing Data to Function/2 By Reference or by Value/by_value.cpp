//Даже если функция не принимает владение, может случиться, что ей всё
//равно нужна копия объекта. Тогда передавать по значению тоже выгодно:

// Функция внутри сортирует список, не меняя его. 
// При передаче по ссылке могут происходить лишние копирования
int GetNthNumber(const vector<int>& input_vector, size_t n) {
    auto input_vector_copy = input_vector;
    sort(input_vector_copy.begin(), input_vector_copy.end());
    return input_vector_copy[n];
}

// Лучше принимать по значению.
// При передаче в такую функцию временного объекта копирования не возникает
int GetNthNumber(vector<int> input_vector, size_t n) {
    sort(input_vector.begin(), input_vector.end());
    return input_vector[n];
}
