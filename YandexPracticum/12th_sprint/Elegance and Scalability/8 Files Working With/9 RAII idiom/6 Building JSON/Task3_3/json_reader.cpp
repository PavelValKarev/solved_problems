#include "json_reader.h"
#include <sstream>
#include <iostream>
#include <unordered_set>

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из JSON,
 * а также код обработки запросов к базе и формирование массива ответов в формате JSON
 */

JSONReader::JSONReader(TransportCatalogue& tc) : catalogue_(tc) {

}

void JSONReader::ReadInput(std::istream& inp) {
    using namespace json;
    using namespace std::literals;

    Document doc(json::Load(inp));
    // [Отлично] И почище будет и эффективней вынести хранящееся значение в переменную
    // [Ревью]
    // Ты из base_requests берёшь запросы и помещаешь их по контейнерам. По сути
    // дальше reqDict использоваться не будет. Значит можно их переместить в эти
    // контейнеры. Но для этого надо сделать их неконстантными
    // [Павел: попутно пришлось сделать неконстантные методы AsRoot() и AsMap()]
    Dict& reqs = doc.GetRoot().AsDict();

    if (reqs.count("base_requests") != 0) {
        // [Здесь reqDict принимаем по ссылке]
        // Дальше потребуется еще неконстантный AsArray()
        Array& baseReqs = reqs.at("base_requests").AsArray();
        for (Node& n : baseReqs) {
            // [Здесь reqDict принимаем по ссылке]
            // Создали неконстантный AsArray()
            Dict& reqDict = n.AsDict();
            const std::string& s = reqDict.at("type").AsString();

            if (s == "Stop"s) {
                //stopRequests_.push_back(reqDict);
                stopRequests_.emplace_back(std::move(reqDict));
            }

            // [Можно лучше] Дело вкуса, но можно напороться потом, если в условии будет больше однго выражения.
            // Тем более выше ты пишешь со скобками
            // Кстати, `doc` умрёт в этой функции, а с ним `reqDict`. У тебя не будет проблем, потому что в
            // busRequests_ хранятся не ссылки. Но может переместить их?
            else if (s == "Bus"s) {
                //busRequests_.push_back(reqDict);
                busRequests_.emplace_back(std::move(reqDict));
            }

            else {
                throw std::invalid_argument("Wrong type for base request");
            }
        }
    }

    if (reqs.count("stat_requests") != 0) {
        //тоже убрал константность для избавления от копирования и последующего перемещения
        Array& statReqs = reqs.at("stat_requests").AsArray();
        for (Node& req : statReqs) {
            // [Можно лучше] а вот здесь как раз не вынес :)
            // [Павел: сделано]
            // Добавил фигурные скобки
            if (req.AsDict().count("type") == 0 || req.AsDict().count("id") == 0) {
                throw std::invalid_argument("invalid stat request");
            }
            else {
                //stat_requests_.push_back(req.AsMap());
                // [Павел: сделано]
                //избавился от копирования
                stat_requests_.emplace_back(std::move(req.AsDict()));
            }
        }
    }

    if (reqs.count("render_settings") != 0) {
        render_settings_ = reqs.at("render_settings").AsDict();
    }
}

void JSONReader::ParseStopRequests() {

    using namespace json;

    for (const Dict& stopDict : stopRequests_) {
        tc::Stop stop;
        //заполняем информацию об остановке

        stop.name = stopDict.at("name").AsString();
        stop.coordinates.lat = stopDict.at("latitude").AsDouble();
        stop.coordinates.lng = stopDict.at("longitude").AsDouble();
        catalogue_.AddStop(stop);

        const Dict& closeStops = stopDict.at("road_distances").AsDict();
        
        for (const auto& stp_ptr_pair : closeStops) {
            const std::string& closeName = (stp_ptr_pair).first;
            int dist = (stp_ptr_pair).second.AsInt();

            StrPair stop_pair(stop.name, closeName);
            catalogue_.AddCloseDistance(stop_pair, dist);
        }
    }
}

void JSONReader::ParseBusRequests() {
    using namespace json;

    for (const Dict& busDict : busRequests_) {
        tc::Bus bus;

        bus.name = busDict.at("name").AsString();
        const Array& stops = busDict.at("stops").AsArray();

        for (const Node& stopName : stops) {
            catalogue_.AddBusToStopInfo(stopName.AsString(), bus.name);
            bus.stops.push_back(catalogue_.GetStopPtr(stopName.AsString()));
        }

        bus.is_roundtrip = busDict.at("is_roundtrip").AsBool();
                
        if (!bus.is_roundtrip && stops.size() >= 2) {
            for (int i = stops.size() - 2; i >= 0; i--) {
                bus.stops.push_back(catalogue_.GetStopPtr(stops[i].AsString()));
            }
        }

        catalogue_.AddBus(bus);

        for (size_t i = 0; i < bus.stops.size() - 1; i++) {
            tc::StopPtrPair spp(bus.stops[i], bus.stops[i + 1]);
            //рассчет расстояния между двумя остановками
            catalogue_.AddDistance(spp, ComputeDistance(bus.stops[i]->coordinates, bus.stops[i + 1]->coordinates));
        }

        MakeBusInfo(bus.name);
    }
}

json::Dict JSONReader::GetRenderSettings() {
    return render_settings_;
}

const std::deque<json::Dict>& JSONReader::GetStatRequests() {
    return stat_requests_;
}

void JSONReader::MakeBusInfo(const std::string& busName) {
    tc::BusInfo bus_info{};
    const tc::Bus& bus = *(catalogue_.GetBusPtr(busName));
    bus_info.bus_name = bus.name;

    bus_info.stops_on_route = static_cast<int>(bus.stops.size());
    std::unordered_set<std::string> stv{};
    std::vector<tc::Stop*> stops_ptrs = bus.stops;
    for (tc::Stop* s : stops_ptrs) {
        stv.insert(s->name);
    }

    bus_info.unique_stops = static_cast<int>(stv.size());
    
    double distance = 0;
    //добавляем новую переменную для расчета реальной дистанции
    double dist_to_close_stop = 0;

    for (size_t i = 0; i < bus.stops.size() - 1; ++i) {

        tc::StopPtrPair stop_ptr_pair(bus.stops[i], bus.stops[i + 1]);
        distance += catalogue_.GetDistance(stop_ptr_pair);
        //Cоздаем пару имен.
        //Пара будет соотвествовать (имя i-ой остановки;имя следующей остановки)
        StrPair stp_ptr_pair(bus.stops[i]->name, bus.stops[i + 1]->name);
        //Внутри проверяем есть ли такая пара, если нет то: swap
        dist_to_close_stop += catalogue_.GetCloseStopDistance(stp_ptr_pair);
    }
    
    //записываем общий путь и кривизну маршрута
    bus_info.route_length = dist_to_close_stop;
    bus_info.curvature = dist_to_close_stop / distance;

    catalogue_.AddBusInfo(busName, bus_info);
}
