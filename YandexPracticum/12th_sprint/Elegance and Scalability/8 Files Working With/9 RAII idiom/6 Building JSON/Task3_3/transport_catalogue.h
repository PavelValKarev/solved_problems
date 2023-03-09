#pragma once

/*
 * Здесь можно разместить код транспортного справочника
 */

#include "domain.h"
#include <deque>
#include <unordered_map>

 // [Нужно исправить] мем_у_нас_здесь_так_не_принято.jpg Используй using, если хочется сделать синоним типу
 // Чтобы тип сделать чуть полегче (его всё равно придётся только по ссылке принимать), мы можем использовать указатели
 // на остановки вместо их имён. Если не нравится, подумай о string_view
#define StrPair std::pair<std::string, std::string>

class TransportCatalogue {

private:
    std::deque<tc::Stop> stops;
    std::deque<tc::Bus> buses;
    std::unordered_map<std::string, tc::Stop*> stopname_to_stop;
    std::unordered_map<std::string, tc::Bus*> busname_to_bus;
    std::unordered_map <tc::StopPtrPair, double, tc::DistanceHash> distance;
    std::unordered_map<std::string, tc::StopInfo> stopname_to_info;
    std::unordered_map<std::string, tc::BusInfo> busname_to_info;
    std::unordered_map<StrPair, double, tc::Close_Stops_Hash> close_stop_distance;

public:

    // [Нужно исправить] Пустой конструктор и деструктор создадутся сами, нет нужды писать их самому.
    // Что ещё интересно, что объявляя так конструктор, он не будет noexcept. Вот такие пироги
    // [Павел: Сделано]
    // Удалил пустой конструктор и деструктор
    //-----Методы меяющие класс-------------------------------------------------
    void AddStop(const tc::Stop& stop);
    void AddBusToStopInfo(const std::string& stop_name, const std::string& bus_name);
    void AddBusInfo(const std::string& bus_name, const tc::BusInfo& bus_info);
    void AddBus(const tc::Bus& bus);
    void AddDistance(tc::StopPtrPair stops, double dist);
    void AddCloseDistance(StrPair stops, double dist);
    //-----Константные методы-------------------------------------------------
    tc::Stop* GetStopPtr(const std::string& stop_name) const;
    bool CheckBus(const std::string& bus_name) const;
    bool CheckStop(const std::string& stop_name) const;
    tc::Bus* GetBusPtr(const std::string& bus_name) const;
    double GetDistance(const tc::StopPtrPair& spp) const;
    bool CheckCloseDistance(const StrPair& stops) const ;
    double GetCloseStopDistance(const StrPair& stops) const ;
    const tc::BusInfo& GetBusInfo(const std::string& bus_name) const;
    const tc::StopInfo& GetStopInfo(const std::string& stop_name) const;

    const std::deque<tc::Bus>& GetBuses() const;
    const std::deque<tc::Stop>& GetStopes() const;    
};
