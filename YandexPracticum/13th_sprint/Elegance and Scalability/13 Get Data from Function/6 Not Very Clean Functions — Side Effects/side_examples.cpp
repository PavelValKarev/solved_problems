//Функция принимает параметр по неконстантной ссылке — признак побочного эффекта.
void Swap(int& l, int& r);

//Несмотря на наличие возвращаемого значения, функция имеет побочный эффект.
char RemoveLastChar(std::string& str);

//Метод принимает параметры по значению и константной ссылке, но он не 
//константный — побочный эффект.
class Park {
public:
    std::vector<Tickets> Enter(const std::vector<Person>& who,
        std::chrono::system_clock::time_point when);
};
