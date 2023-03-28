/*
метод std::map::insert возвращает итератор на 
добавленный эл-т и флаг успеха
*/

std::pair<iterator, bool> insert(const value_type& value);
std::pair<iterator, bool> insert(value_type&& value);
