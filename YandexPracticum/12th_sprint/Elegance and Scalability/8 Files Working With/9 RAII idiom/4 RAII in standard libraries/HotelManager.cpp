#include <iostream>
#include <unordered_map>
#include <deque>
#include <tuple>

using namespace std;

class HotelManager {
public:
    void Book(int64_t time, const string& hotel_name, int64_t client_id, int64_t room_count) {
        //счетчик активных бронирований
        int cnt = 0;
        for (const auto& [hotel, t, client, rooms] : hotel_to_time_to_client_to_rooms) {
            if (t > time - 86400) {
                break;
            }
            else {
                //кол-во активных бронирований увеличилось
                ++cnt;
                //кол-во свободных комнат уменьшилось
                hotel_to_rooms[hotel] -= rooms;
                if (--hotel_to_client_to_books[hotel][client] == 0) {
                    --hotel_to_clients[hotel];
                }
            }
        }
        hotel_to_time_to_client_to_rooms.erase(hotel_to_time_to_client_to_rooms.begin()
            , hotel_to_time_to_client_to_rooms.begin() + cnt);
        hotel_to_time_to_client_to_rooms.emplace_back(hotel_name, time, client_id, room_count);
        hotel_to_rooms[hotel_name] += room_count;
        if (hotel_to_client_to_books[hotel_name][client_id]++ == 0) {
            ++hotel_to_clients[hotel_name];
        }
    
    }
    int ComputeClientCount(const string& hotel_name) {
        return hotel_to_clients[hotel_name];
    };
    int ComputeRoomCount(const string& hotel_name) {
        return hotel_to_rooms[hotel_name];
    }

private:
    //кол-во свободных комнат в отеле
    unordered_map<string, int64_t> hotel_to_rooms;
    //ключ - название отеля. значение (ключ - id клиента, значение: кол-во комнат брони под него)
    unordered_map<string, unordered_map<int64_t, int64_t>> hotel_to_client_to_books;
    unordered_map<string, int64_t> hotel_to_clients;
    deque<tuple<string, int64_t, int64_t, int64_t>> hotel_to_time_to_client_to_rooms;
};

int main() {
    HotelManager manager;
    /*
    В первой строке вводится количество запросов Q — натуральное число,
    не превосходящее 10^5.
    В следующих Q строках в соответствии с описанным выше форматом вводятся запросы.    
    */
    int query_count;
    cin >> query_count;
    /*
    Разработайте систему бронирования отелей, позволяющую клиентам бронировать 
    номера, а владельцам отелей — контролировать спрос. Ваша программа должна
    обрабатывать следующие события:
    */
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        /*
        BOOK time hotel_name client_id room_count — забронировать клиентом
        client_id room_count номеров в отеле hotel_name в момент времени time.
        Время измеряется в секундах, отсчитываемых от некоторого момента.
        */
        if (query_type == "BOOK") {
            int64_t time;
            cin >> time;
            string hotel_name;
            cin >> hotel_name;
            //сколько комнат в отеле бронирует клиент с данным id 
            int client_id, room_count;
            cin >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        }
        else {
            string hotel_name;
            cin >> hotel_name;
            /*
            CLIENTS hotel_name — вывести количество различных клиентов,
            бронировавших номера в отеле hotel_name за последние сутки.
            Более формально диапазон времени описывается так: пусть
            current_time — время последнего события BOOK, тогда в данном
            запросе нужно учесть все события
            с current_time − 86400 < time ⩽ current_time, где
            86400 — количество секунд в сутках. Последнее бронирование
            должно учитываться, а бронирование, случившееся ровно за
            сутки до него, учитываться не должно.
            */
            if (query_type == "CLIENTS") {
                cout << manager.ComputeClientCount(hotel_name) << "\n";
            }
            /*
            ROOMS hotel_name — вывести количество номеров, забронированных
            за последние сутки в отеле hotel_name.
            */
            else if (query_type == "ROOMS") {
                cout << manager.ComputeRoomCount(hotel_name) << "\n";
            }
        }
    }

    return 0;
}
