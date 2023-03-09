#pragma once
#include "transport_catalogue.h"
#include "json.h"
#include "map_renderer.h"

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из JSON,
 * а также код обработки запросов к базе и формирование массива ответов в формате JSON
 */

class JSONReader
{
    TransportCatalogue& catalogue_;
    std::deque<json::Dict> stopRequests_, busRequests_;
    json::Dict render_settings_;
    std::deque<json::Dict> stat_requests_;

    JSONReader() = delete;
public:
    JSONReader(TransportCatalogue& tc);
    
    void ReadInput(std::istream& inp);
    void ParseStopRequests();
    void ParseBusRequests();
    json::Dict GetRenderSettings();
    const std::deque<json::Dict>& GetStatRequests();
    void MakeBusInfo(const std::string& busName);
};
