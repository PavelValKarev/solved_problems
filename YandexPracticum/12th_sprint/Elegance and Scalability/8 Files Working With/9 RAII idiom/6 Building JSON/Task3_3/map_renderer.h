#pragma once
#include "svg.h"
#include "geo.h"
#include "domain.h"
#include <deque>
#include <algorithm>

//код, отвечающий за визуализацию карты маршрутов в формате SVG.

inline const double EPSILON = 1e-6;
bool IsZero(double value);

class SphereProjector {
public:
    // points_begin и points_end задают начало и конец интервала элементов geo::Coordinates
    template <typename PointInputIt>
    SphereProjector(PointInputIt points_begin, PointInputIt points_end, double max_width, double max_height, double padding);

    // Проецирует широту и долготу в координаты внутри SVG-изображения
    svg::Point operator()(geo::Coordinates coords) const;

private:
    double padding_;
    double min_lon_ = 0;
    double max_lat_ = 0;
    double zoom_coeff_ = 0;
};

class MapRenderer
{
public:
    // [Нужно переделать] Нарушена инкапсуляция! Вместо `serialized` стоит принимать настройки отрисовки в
    // конструкторе. Чтобы принимать настройки удобнее, создай структуру со всеми ними
    bool serialized = false;
    double width, height, padding, line_width, stop_radius, underlayer_width;
    int bus_label_font_size, stop_label_font_size;
    svg::Point bus_label_offset, stop_label_offset;
    svg::Color underlayer_color;
    std::vector<svg::Color> color_palette;

    std::string GetMap(std::deque<tc::Bus> buses);
    void AddBusText(svg::Document& doc, svg::Point pos, const std::string& name, const svg::Color& routeColor);
    void AddStopText(svg::Document& doc, svg::Point pos, std::string name);
    void PrintMap(std::deque<tc::Bus> buses);


};

template<typename PointInputIt>
inline SphereProjector::SphereProjector(PointInputIt points_begin, PointInputIt points_end, double max_width, double max_height, double padding)
    : padding_(padding)
{
    // Если точки поверхности сферы не заданы, вычислять нечего
    if (points_begin == points_end) {
        return;
    }

    // Находим точки с минимальной и максимальной долготой
    const auto [left_it, right_it] = std::minmax_element(
        points_begin, points_end,
        [](auto lhs, auto rhs) { return lhs.lng < rhs.lng; });
    min_lon_ = left_it->lng;
    const double max_lon = right_it->lng;

    // Находим точки с минимальной и максимальной широтой
    const auto [bottom_it, top_it] = std::minmax_element(
        points_begin, points_end,
        [](auto lhs, auto rhs) { return lhs.lat < rhs.lat; });
    const double min_lat = bottom_it->lat;
    max_lat_ = top_it->lat;

    // Вычисляем коэффициент масштабирования вдоль координаты x
    std::optional<double> width_zoom;
    if (!IsZero(max_lon - min_lon_)) {
        width_zoom = (max_width - 2 * padding) / (max_lon - min_lon_);
    }

    // Вычисляем коэффициент масштабирования вдоль координаты y
    std::optional<double> height_zoom;
    if (!IsZero(max_lat_ - min_lat)) {
        height_zoom = (max_height - 2 * padding) / (max_lat_ - min_lat);
    }

    if (width_zoom && height_zoom) {
        // Коэффициенты масштабирования по ширине и высоте ненулевые,
        // берём минимальный из них
        zoom_coeff_ = std::min(*width_zoom, *height_zoom);
    }
    else if (width_zoom) {
        // Коэффициент масштабирования по ширине ненулевой, используем его
        zoom_coeff_ = *width_zoom;
    }
    else if (height_zoom) {
        // Коэффициент масштабирования по высоте ненулевой, используем его
        zoom_coeff_ = *height_zoom;
    }
}
