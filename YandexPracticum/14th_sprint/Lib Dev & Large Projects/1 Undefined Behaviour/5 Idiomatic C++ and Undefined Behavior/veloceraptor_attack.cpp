#include <iostream>

using namespace std;

// Указатель на функцию без параметров, которая возвращает void
using Alarm = void (*)();

namespace {
	// Поведение сигнализации определяется значением указателя alarm
	Alarm alarm = nullptr;
}  // namespace

/*
Для установки агрессивного уровня реагирования служит функция 
SetHostileAlarm. Она присваивает указателю alarm адрес функции,
выпускающей велоцираптора:
*/

// Выпустить велоцираптора
void HostileAlarm() {
    cout << "Attack with velociraptor"sv << endl;
}

// Настраиваем сигнализацию на выпуск велоцираптора
void SetHostileAlarm() {
    cout << "Hostile alarm set" << endl;
    alarm = HostileAlarm;
}

/*
Остаётся протестировать работу программы, вызвав функцию
Test. Она, в свою очередь, вызовет функцию, на которую
ссылается указатель alarm:
*/

void Test() {
    // Вызываем функцию, на которую ссылается указатель alarm
    alarm();
    cout << "Test succeeded"sv << endl;
}

int main() {
    Test();
}
