#pragma once
/*
 * В этом файле вы можете разместить классы/структуры, которые являются частью предметной области (domain)
 * вашего приложения и не зависят от транспортного справочника. Например Автобусные маршруты и Остановки.
 *
 * Их можно было бы разместить и в transport_catalogue.h, однако вынесение их в отдельный
 * заголовочный файл может оказаться полезным, когда дело дойдёт до визуализации карты маршрутов:
 * визуализатор карты (map_renderer) можно будет сделать независящим от транспортного справочника.
 *
 * Если структура вашего приложения не позволяет так сделать, просто оставьте этот файл пустым.
 *
 */
 
#include <string_view>
#include <vector>
#include <string>
#include <set>
#include "geo.h"

namespace tc {
    struct Stop {
        std::string name{};
        geo::Coordinates coordinates{};
               
        bool operator==(const Stop& other) const;        
    };

    struct Bus {
        std::string name;        
        std::vector<Stop*> stops;
        bool is_roundtrip;
    };

    struct StopInfo {
        std::string_view stop_name{};
        std::set<std::string> buses;
    };

    struct StopPtrPair {

        StopPtrPair(Stop* stop1, Stop* stop2) {            
            ptr1_to_Stop1 = reinterpret_cast<size_t>(stop1);
            ptr2_to_Stop2 = reinterpret_cast<size_t>(stop2);
        }
        bool operator==(const StopPtrPair& other) const;
        //указателями на остановки мы пользуемся просто как числом
        size_t ptr1_to_Stop1;
        size_t ptr2_to_Stop2;
    };

    static const uint64_t SIMPLE_NUMBER = 37;

    struct DistanceHash {
        //Можно вычислить хеш каждого из трёх полей структуры, используя
        //хешер std::hash<double>, а затем объединить их, умножив на число 37

        size_t operator() (const StopPtrPair& stop_ptr_pair) const {            
            std::hash<size_t> d_hasher_;
            size_t h_x = d_hasher_(stop_ptr_pair.ptr1_to_Stop1);
            size_t h_y = d_hasher_(stop_ptr_pair.ptr2_to_Stop2);
            return h_x + h_y * SIMPLE_NUMBER;
        }
    };

    struct Close_Stops_Hash {        
        size_t operator() (const std::pair<std::string, std::string>& pair) const {
            std::hash<std::string> d_hasher_;
            size_t h_x = d_hasher_(pair.first);
            size_t h_y = d_hasher_(pair.second);
            return h_x + h_y * SIMPLE_NUMBER;
        }
    };

    struct BusInfo {
        std::string_view bus_name{};
        int stops_on_route{};
        int unique_stops{};
        double route_length{};
        double curvature{};
    };
}

