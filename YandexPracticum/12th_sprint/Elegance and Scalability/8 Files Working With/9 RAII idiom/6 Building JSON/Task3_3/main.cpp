#include "json_builder.h"
#include "request_handler.h"
#include <iostream>

using namespace std;

int main() {

    TransportCatalogue db;
    RequestHandler handler(db);

    handler.ReadInput();
    //handler.PrintMap();
    handler.PrintStat();
    
    /*
     * Примерная структура программы:
     *
     * Считать JSON из stdin
     * Построить на его основе JSON базу данных транспортного справочника
     * Выполнить запросы к справочнику, находящиеся в массиве "stat_requests", построив JSON-массив
     * с ответами.
     * Вывести в stdout ответы в виде JSON
     */
}
