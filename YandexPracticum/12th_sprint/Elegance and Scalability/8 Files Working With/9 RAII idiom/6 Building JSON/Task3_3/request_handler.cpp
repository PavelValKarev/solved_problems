#include "request_handler.h"
#include "json_builder.h"
/*
 * Здесь можно было бы разместить код обработчика запросов к базе, содержащего логику, которую не
 * хотелось бы помещать ни в transport_catalogue, ни в json reader.
 *
 * Если вы затрудняетесь выбрать, что можно было бы поместить в этот файл,
 * можете оставить его пустым.
 */

RequestHandler::RequestHandler(TransportCatalogue& tc) :
	jsonReader_(tc), catalogue_(tc)
{
}


void RequestHandler::ReadInput()
{
	// [Нужно переделать] Нет возможности задать другой поток
	jsonReader_.ReadInput(std::cin);

	jsonReader_.ParseStopRequests();

	jsonReader_.ParseBusRequests();


	// [Можно лучше] Стоит оформить в отдельную функцию по чтению настроек
	const json::Dict renderSettings = jsonReader_.GetRenderSettings();
	if (renderSettings.size() > 0)
	{
		mapRenderer_.serialized = true;
		mapRenderer_.width = renderSettings.at("width").AsDouble();
		mapRenderer_.height = renderSettings.at("height").AsDouble();
		mapRenderer_.padding = renderSettings.at("padding").AsDouble();
		// [Можно лучше] А откуда это условие пришло?
		const double maxPad = std::min(mapRenderer_.width, mapRenderer_.height) / 2;
		if (mapRenderer_.padding > maxPad)
			mapRenderer_.padding = maxPad;

		mapRenderer_.line_width = renderSettings.at("line_width").AsDouble();
		mapRenderer_.stop_radius = renderSettings.at("stop_radius").AsDouble();
		mapRenderer_.underlayer_width = renderSettings.at("underlayer_width").AsDouble();

		mapRenderer_.bus_label_font_size = renderSettings.at("bus_label_font_size").AsInt();
		mapRenderer_.stop_label_font_size = renderSettings.at("stop_label_font_size").AsInt();

		const json::Array busLableOffset = renderSettings.at("bus_label_offset").AsArray();
		mapRenderer_.bus_label_offset = svg::Point(busLableOffset[0].AsDouble(), busLableOffset[1].AsDouble());

		const json::Array stopLableOffset = renderSettings.at("stop_label_offset").AsArray();
		mapRenderer_.stop_label_offset = svg::Point(stopLableOffset[0].AsDouble(), stopLableOffset[1].AsDouble());

		// [Нужно исправить] `Node` принимается по значению, но используется только для чтения.
		// [Павел: попробовал - лезут ошибки, не пойму как исправить]
		// [Исправлено]
		auto GetColor = [](const json::Node& c)
		{
			if (c.IsArray())
			{
				const json::Array colorArr = c.AsArray();
				if (colorArr.size() == 3)
				{
					return svg::Color(svg::Rgb(colorArr[0].AsInt(), colorArr[1].AsInt(), colorArr[2].AsInt()));
				}
				else if (colorArr.size() == 4)
				{
					return svg::Color(svg::Rgba(colorArr[0].AsInt(), colorArr[1].AsInt(), colorArr[2].AsInt(), colorArr[3].AsDouble()));
				}
			}
			else if (c.IsString())
			{
				return svg::Color(c.AsString());
			}

			// [Отлично] Интересное решение, я в такой момент лично предпочёл исключение кинуть, так как все форматы
			// обработаны
			return svg::Color("magenta");
		};

		mapRenderer_.underlayer_color = GetColor(renderSettings.at("underlayer_color"));

		const json::Array pallete = renderSettings.at("color_palette").AsArray();
		for (const json::Node& color : pallete)
		{
			mapRenderer_.color_palette.push_back(GetColor(color));
		}

	}
}

void RequestHandler::PrintMap()
{
	mapRenderer_.PrintMap(catalogue_.GetBuses());
}

// [Можно лучше] Если здесь планируется выводить статистику, то формировать её, мне кажется, имеет смысл в json_reader,
// а не в RequestHandler
void RequestHandler::PrintStat()
{
	using namespace json;
	//[Использование Builder]

	Builder responses;
	responses.StartArray();
	//Array responses;

	// [Нужно исправить] Снова происходит копирование
	const std::deque<json::Dict> stat_requests = jsonReader_.GetStatRequests();

	if (stat_requests.size() == 0)
		return;

	for (const Dict& req : stat_requests)
	{
		//[Добавлен Builder]
		//Dict response;
		Builder response;
		response.StartDict();
		response.Key("request_id").Value(req.at("id"));
		//response["request_id"] = Node(req.at("id").AsInt());

		if (req.at("type").AsString() == "Bus")
		{
			try {
				tc::BusInfo busInfo = catalogue_.GetBusInfo(req.at("name").AsString());

				// [Можно лучше] Преобразование в Node произойдёт автоматически, код можно сделать чище
				//[Исправлено, добавлен Builder]

				response.
					Key("curvature").Value(busInfo.curvature).
					Key("route_length").Value(busInfo.route_length).
					Key("stop_count").Value(busInfo.stops_on_route).
					Key("unique_stop_count").Value(busInfo.unique_stops);

				/*response["curvature"] = Node(busInfo.curvature);
				response["route_length"] = Node(busInfo.route_length);
				response["stop_count"] = Node(busInfo.stops_on_route);
				response["unique_stop_count"] = Node(busInfo.unique_stops);*/
			}
			catch (std::out_of_range&)
			{
				response.Key("error_message").Value(std::string("not found"));
				//response["error_message"] = Node(std::string("not found"));
			}

		}
		else if (req.at("type").AsString() == "Stop")
		{
			try {
				tc::StopInfo stopInfo = catalogue_.GetStopInfo(req.at("name").AsString());
				//Array buses;
				Builder buses;
				buses.StartArray();
				for (const std::string& busName : stopInfo.buses)
				{
					buses.Value(busName);
					//buses.push_back(Node());
				}
				response.Key("buses").Value(buses.EndArray().Build());
				//response["buses"] = Node(buses);
			}
			catch (std::out_of_range&)
			{
				response.Key("error_message").Value(std::string("not found"));
				//response["error_message"] = Node(std::string("not found"));
			}

		}
		else if (req.at("type").AsString() == "Map")
		{
			response.Key("map").Value(mapRenderer_.GetMap(catalogue_.GetBuses()));
			//response["map"] = Node(mapRenderer_.GetMap(catalogue_.GetBuses()));
		}
		else
			throw std::invalid_argument("invalid request type");

		response.EndDict();
		responses.Value(response.Build());
		//responses.push_back(response);
	}
	responses.EndArray();
	json::Print(Document(responses.Build()), std::cout);
	//json::Print(Document(responses), std::cout);

}
