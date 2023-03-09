// [Можно лучше] Вот здесь стоит поменять порядок. <> библиотек загружаем первыми, потом ""
// [Павел: сделано]
#include <algorithm>
#include <sstream>
#include <exception>
#include "map_renderer.h"

/*
 * В этом файле вы можете разместить код, отвечающий за визуализацию карты маршрутов в формате SVG.
 * Визуализация маршрутов вам понадобится во второй части итогового проекта.
 * Пока можете оставить файл пустым.
 */


bool IsZero(double value) {
	return std::abs(value) < EPSILON;
}

// [Отлично] Отдельная функция для вывода названя остановки -- класс!
// [Нужно исправить] `std::string` принимается по значению, но используется только для чтения.
// Нужно сделать более оптимизированный код.
// [Павел: сделано.]
// Добавлена ссылка для name И color
void MapRenderer::AddBusText(svg::Document& doc, svg::Point pos, const std::string& name, const svg::Color& routeColor)
{
	using namespace svg;
	doc.Add(Text()
		.SetPosition(pos)
		.SetOffset({ bus_label_offset.x, bus_label_offset.y })
		.SetFontSize(bus_label_font_size)
		.SetFontFamily("Verdana")
		.SetFontWeight("bold")
		.SetData(name)
		.SetFillColor(underlayer_color)
		.SetStrokeColor(underlayer_color)
		.SetStrokeWidth(underlayer_width)
		.SetStrokeLineCap(StrokeLineCap::ROUND)
		.SetStrokeLineJoin(StrokeLineJoin::ROUND));

	doc.Add(Text()
		.SetPosition(pos)
		.SetOffset({ bus_label_offset.x, bus_label_offset.y })
		.SetFontSize(bus_label_font_size)
		.SetFontFamily("Verdana")
		.SetFontWeight("bold")
		.SetData(name)
		.SetFillColor(routeColor));
}

void MapRenderer::AddStopText(svg::Document& doc, svg::Point pos, std::string name)
{
	using namespace svg;
	doc.Add(Text()
		.SetPosition(pos)
		.SetOffset({ stop_label_offset.x, stop_label_offset.y })
		.SetFontSize(stop_label_font_size)
		.SetFontFamily("Verdana")
		.SetData(name)
		.SetFillColor(underlayer_color)
		.SetStrokeColor(underlayer_color)
		.SetStrokeWidth(underlayer_width)
		.SetStrokeLineCap(svg::StrokeLineCap::ROUND)
		.SetStrokeLineJoin(svg::StrokeLineJoin::ROUND));

	doc.Add(Text()
		.SetPosition(pos)
		.SetOffset({ stop_label_offset.x, stop_label_offset.y })
		.SetFontSize(stop_label_font_size)
		.SetFontFamily("Verdana")
		.SetData(name)
		.SetFillColor("black"));
}

// [Нужно переделать] Выводить только в cout - не очень универсально. А если я хочу другой поток?
// Лишнее копирование
void MapRenderer::PrintMap(std::deque<tc::Bus> buses)
{
	std::cout << GetMap(buses);
}

std::string MapRenderer::GetMap(std::deque<tc::Bus> buses)
{
	if (!serialized)
	{
		return "";
	}

	using namespace svg;

	std::vector<tc::Stop> stops;
	std::vector<geo::Coordinates> coords;

	Document doc;

	for (const auto& bus : buses)
	{
		for (const auto& stop : bus.stops)
		{
			// [Нужно переделать] Поиск элемента будет всё медленее и медленее. Лучше предпочесть другой контейнер
			// Что ещё должно помочь, это хранение указателей, вместо ещё одной копии остановок
			if (std::find(stops.begin(), stops.end(), *stop) == stops.end())
			{
				stops.push_back(*stop);
				coords.push_back(stop->coordinates);
			}
		}
	}
	SphereProjector projector(coords.begin(), coords.end(), width, height, padding);


	// [Можно лучше] У строк по умолчанию сортировка лексикографически происходит
	std::sort(buses.begin(), buses.end(), [](const tc::Bus& a, const tc::Bus& b) {
		return std::lexicographical_compare(a.name.begin(), a.name.end(), b.name.begin(), b.name.end());
		});

	int clrIndex = 0;
	for (const tc::Bus& bus : buses)
	{
		// [Можно лучше] Для нуля есть `.empty()`
		if (bus.stops.size() == 0)
			continue;

		svg::Polyline route;

		// [Отлично] Модуло, бомбезно
		const svg::Color routeColor = color_palette[clrIndex % color_palette.size()];

		clrIndex++;

		route.SetStrokeColor(routeColor);
		route.SetFillColor("none");
		route.SetStrokeLineCap(svg::StrokeLineCap::ROUND);
		route.SetStrokeLineJoin(svg::StrokeLineJoin::ROUND);
		route.SetStrokeWidth(line_width);

		for (auto stop : bus.stops)
		{
			svg::Point point = projector({ stop->coordinates.lat, stop->coordinates.lng });
			route.AddPoint(point);
		}

		doc.Add(route);
	}

	clrIndex = 0;

	for (const tc::Bus& bus : buses)
	{
		const svg::Color routeColor = color_palette[clrIndex % color_palette.size()];
		clrIndex++;

		if (bus.is_roundtrip)
		{
			const tc::Stop& firstStop = *(bus.stops[0]);

			AddBusText(doc, projector(firstStop.coordinates), bus.name, routeColor);

		}
		else
		{
			const tc::Stop& firstStop = *(bus.stops[0]);
			const tc::Stop& lastStop = *(bus.stops[(bus.stops.size() - 1) / 2]);

			if (firstStop.name != lastStop.name)
			{
				AddBusText(doc, projector(firstStop.coordinates), bus.name, routeColor);
				AddBusText(doc, projector(lastStop.coordinates), bus.name, routeColor);
			}
			else
			{
				// [Можно лучше] В чём отличие от остановки `firstStop` выше?
				//[Исправлено]
				AddBusText(doc, projector(firstStop.coordinates), bus.name, routeColor);
			}

		}
	}

	std::sort(stops.begin(), stops.end(), [](const tc::Stop& a, const tc::Stop& b) {
		return std::lexicographical_compare(a.name.begin(), a.name.end(), b.name.begin(), b.name.end());
		});

	for (const tc::Stop& stop : stops)
	{
		doc.Add(Circle().SetCenter(projector(stop.coordinates))
			.SetFillColor("white")
			.SetRadius(stop_radius));
	}

	for (const tc::Stop& stop : stops)
	{
		AddStopText(doc, projector(stop.coordinates), stop.name);
	}

	std::stringstream sstr;
	doc.Render(sstr);
	return sstr.str();
}

svg::Point SphereProjector::operator()(geo::Coordinates coords) const {
	return {
		(coords.lng - min_lon_) * zoom_coeff_ + padding_,
		(max_lat_ - coords.lat) * zoom_coeff_ + padding_
	};
}
