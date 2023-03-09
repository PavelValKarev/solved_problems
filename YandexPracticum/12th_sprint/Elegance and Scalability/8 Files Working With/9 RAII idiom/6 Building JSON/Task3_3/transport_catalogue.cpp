#include "transport_catalogue.h"
#include <iostream>
#include <algorithm>

void TransportCatalogue::AddStop(const tc::Stop& stop)
{
    // [Можно лучше] Когда поменяешь на emplace_back, тебе понравится, потому что он возвращает ссылку на созданный
    // объект сразу :)
    // [Павел : сделано]
    // Заменил push_back на emplace_back()
    stops.emplace_back(stop);
    stopname_to_stop[stops.back().name] = &stops.back();
    //заполняем информацию об остановках, которые проезжает данный автобус
    tc::StopInfo stop_info;
    stop_info.stop_name = stops.back().name;
    stopname_to_info[stops.back().name] = stop_info;

}

void TransportCatalogue::AddBusToStopInfo(const std::string& stop_name, const std::string& bus_name)
{
    stopname_to_info.at(stop_name).buses.insert(bus_name);
}

void TransportCatalogue::AddBusInfo(const std::string& bus_name, const tc::BusInfo& bus_info)
{
    busname_to_info[bus_name] = bus_info;
}

tc::Stop* TransportCatalogue::GetStopPtr(const std::string& stop_name) const
{
    return stopname_to_stop.at(stop_name);
}

void TransportCatalogue::AddBus(const tc::Bus& bus)
{
    buses.push_back(bus);
    //заполняем мапу остановками, которые проезжает данный автобус
    busname_to_bus[buses.back().name] = &buses.back();
    //заполняем информацию об автобусах, которые проходят через данную остановку
    tc::BusInfo bus_info;
    bus_info.bus_name = buses.back().name;
    busname_to_info[buses.back().name] = bus_info;
}

void TransportCatalogue::AddDistance(tc::StopPtrPair stops, double dist) {
    distance[stops] = dist;
}

void TransportCatalogue::AddCloseDistance(StrPair stops, double dist) {
    close_stop_distance[stops] = dist;
}

// [Можно лучше] Метод, который не меняет состояние класса, должен быть const
// [Павел : сделано]
bool TransportCatalogue::CheckBus(const std::string& bus_name) const {
    return busname_to_bus.count(bus_name) > 0;
}

// [Павел : сделано]
bool TransportCatalogue::CheckStop(const std::string& stop_name) const {
    return stopname_to_stop.count(stop_name) > 0;
}

// [Павел : сделано]
tc::Bus* TransportCatalogue::GetBusPtr(const std::string& bus_name) const {
    return busname_to_bus.at(bus_name);
}

double TransportCatalogue::GetDistance(const tc::StopPtrPair& spp) const {
    return distance.at(spp);
}

bool TransportCatalogue::CheckCloseDistance(const StrPair& stops) const {
    return close_stop_distance.count(stops) > 0;
}

double TransportCatalogue::GetCloseStopDistance(const StrPair& stops) const {
    if (close_stop_distance.count(stops) > 0) {
        return close_stop_distance.at(stops);
    }
    else {
        std::pair<std::string, std:: string> ptr_pair = stops;
        std::swap(ptr_pair.first, ptr_pair.second);
        return close_stop_distance.at(ptr_pair);
    }
}

//double TransportCatalogue::GetCloseStopDistance(const StrPair& stops) const {
//    return close_stop_distance.at(stops);
//}

const tc::BusInfo& TransportCatalogue::GetBusInfo(const std::string& bus_name) const{

    // [Нужно исправить] Здесь всё можно записать прямо в return. Ради чистоты и читабельности
    // [Павел : сделано]
    return busname_to_info.at(bus_name);
}

const tc::StopInfo& TransportCatalogue::GetStopInfo(const std::string& stop_name) const{

    static tc::StopInfo stop_info{};

    stop_info = stopname_to_info.at(stop_name);;

    return stop_info;
}

const std::deque<tc::Bus>& TransportCatalogue::GetBuses() const {
    return buses;
}

const std::deque<tc::Stop>& TransportCatalogue::GetStopes() const {
    return stops;
}

