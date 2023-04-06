#include <iostream>
#include <functional>

/*
Во-вторых, вы можете объявить тип Alarm с использованием std::function.
std::function выбрасывает исключение std::bad_function_call, если
функция не была инициализирована. Кроме того, std::function позволяет 
хранить любой объект, который можно вызвать, включая лямбда-функции
и методы классов:
*/

using namespace std;

// Указатель на функцию без параметров, которая возвращает void
using Alarm = function<void()>;

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
    cout << "Test succeeded"sv << endl;
}

int main() {
    Test();
}


/*
Данный код объявляет тип Alarm с помощью std::function. std::function
представляет собой шаблонный класс, который инкапсулирует в себе объект,
который можно вызвать как функцию.

В данном случае, тип Alarm определен как function<void()>, то есть это
функция без аргументов, которая ничего не возвращает.

Кроме того, в данном коде std::function используется для создания
объекта alarm, который затем вызывается в функции Test(). Это означает,
что alarm должен быть инициализирован объектом, который можно вызвать
как функцию (например, лямбда-функцией), иначе будет выброшено 
исключение std::bad_function_call.

Функция Test() вызывает alarm() и затем выводит сообщение в консоль,
если вызов alarm() не привел к выбросу исключения.
*/
