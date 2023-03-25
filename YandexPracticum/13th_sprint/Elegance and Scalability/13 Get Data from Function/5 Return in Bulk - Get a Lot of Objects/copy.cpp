/*
Этот алгоритм передаёт владение, но только не теми объектами, 
которые ему переданы на вход, а их копиями. 

Его реализация может быть крайне простой:
*/

template<class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
    while (first != last) {
        *d_first++ = *first++;
    }
    return d_first;
}
