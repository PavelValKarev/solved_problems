#include "svg.h"

namespace svg {

    using namespace std::literals;

    Rgb::Rgb(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}

    Rgba::Rgba(uint8_t r, uint8_t g, uint8_t b, double op) : red(r), green(g), blue(b), opacity(op) {}

    // ---------- ColorPrinter ------------------

    void ColorPrinter::operator()(std::monostate) const {
        out << "none"s;
    }

    void ColorPrinter::operator()(const std::string& color) const {
        out << color;
    }

    void ColorPrinter::operator()(Rgb color) const {
        out << "rgb("s << static_cast<unsigned>(color.red) << ',' << static_cast<unsigned>(color.green) << ','
            << static_cast<unsigned>(color.blue) << ')';
    }

    void ColorPrinter::operator()(Rgba color) const {
        out << "rgba("s << static_cast<unsigned>(color.red) << ',' << static_cast<unsigned>(color.green) << ','
            << static_cast<unsigned>(color.blue) << ',' << color.opacity << ')';
    }

    // ----------  StrokeLine ------------------

    std::ostream& operator<<(std::ostream& os, StrokeLineCap str_cap) {
        switch (str_cap)
        {
        case StrokeLineCap::BUTT:
        {
            return os << "butt";
        }
        case StrokeLineCap::ROUND:
        {
            return os << "round";
        }
        case StrokeLineCap::SQUARE:
        {
            return os << "square";
        }
        default:
        {
            return os << "stroke-linecap{" << static_cast<int>(str_cap) << '}';
        }
        }
    }

    std::ostream& operator<<(std::ostream& stream, StrokeLineJoin str_line_join)
    {
        switch (str_line_join)
        {
        case StrokeLineJoin::ARCS:
        {
            return stream << "arcs";
        }
        case StrokeLineJoin::BEVEL:
        {
            return stream << "bevel";
        }
        case StrokeLineJoin::MITER:
        {
            return stream << "miter";
        }
        case StrokeLineJoin::MITER_CLIP:
        {
            return stream << "miter-clip";
        }
        case StrokeLineJoin::ROUND:
        {
            return stream << "round";
        }
        default:
        {
            return stream << "stroke-linejoin{" << static_cast<int>(str_line_join) << '}';
        }
        }
    }

    void Object::Render(const RenderContext& context) const {
        context.RenderIndent();

        // Делегируем вывод тега своим подклассам
        RenderObject(context);

        context.out << std::endl;
    }

    // ---------- Circle ------------------

    Circle::Circle() : center_({ 0.0, 0.0 }), radius_(1.0) {}

    Circle& Circle::SetCenter(Point center) {
        center_ = center;
        return *this;
    }

    Circle& Circle::SetRadius(double radius) {
        radius_ = radius;
        return *this;
    }

    void Circle::RenderObject(const RenderContext& context) const {
        auto& out = context.out;
        out << "<circle cx=\""sv << center_.x << "\" cy=\""sv << center_.y << "\" "sv;
        out << "r=\""sv << radius_ << "\""sv;
        // Выводим атрибуты, унаследованные от PathProps
        RenderAttrs(context.out);
        out << "/>"sv;
    }

    // ---------- Polyline ------------------

    Polyline& Polyline::AddPoint(Point point) {
        poli_line_coordinates_.push_back(point);
        return *this;
    }
    void Polyline::RenderObject(const RenderContext& context) const {
        auto& out = context.out;
        out << "<polyline points=\"";
        for (auto i = poli_line_coordinates_.begin(); i != poli_line_coordinates_.end(); i++) {
            if (i != poli_line_coordinates_.begin()) {
                out << " ";
            }
            out << i->x << "," << i->y;//" "
        }
        out << "\"";
        RenderAttrs(context.out);
        out << "/>"sv;
    }

    // ---------- Text ------------------

    Text::Text() : position_({ 0.0, 0.0 }), offset_({ 0.0, 0.0 }), size_(1) {}

    Text& Text::SetPosition(Point pos) {
        position_ = pos;
        return *this;
    }

    // Задаёт смещение относительно опорной точки (атрибуты dx, dy)
    Text& Text::SetOffset(Point offset) {
        offset_ = offset;
        return *this;
    }

    // Задаёт размеры шрифта (атрибут font-size)
    Text& Text::SetFontSize(uint32_t size) {
        size_ = size;
        return *this;
    }

    // Задаёт название шрифта (атрибут font-family)
 
    // [Нужно исправить] `std::string` принимается по значению, но далее снова копируется.
    // Нужно сделать более оптимизированный код.
    Text& Text::SetFontFamily(std::string font_family) {
        font_family_ = font_family;
        return *this;
    }

    // Задаёт толщину шрифта (атрибут font-weight)
    Text& Text::SetFontWeight(std::string font_weight) {
        font_weight_ = font_weight;
        return *this;
    }

    // Задаёт текстовое содержимое объекта (отображается внутри тега text)            
    Text& Text::SetData(std::string data) {
        Text::data_ = data;
        return *this;
    }

    void Text::ReplaceServiceChars(std::string& data) {
        for (const auto& [from, to] : replacements_)
        {
            size_t start_pos = 0;
            while ((start_pos = data.find(from, start_pos)) != std::string::npos)
            {
                data.replace(start_pos, from.length(), to);
                start_pos += to.length();
            }
        }
    }

    void Text::RenderObject(const RenderContext& context) const {
        auto& out = context.out;

        out << "<text ";

        RenderAttrs(out);

        out << " x=\""sv << position_.x << "\" y=\""sv << position_.y << "\""sv;
        out << " dx=\""sv << offset_.x << "\" dy=\""sv << offset_.y << "\""sv;
        out << " font-size=\""sv << size_ << "\""sv;
        if (!font_family_.empty())
        {
            out << " font-family=\""sv << font_family_ << "\""sv;
        }
        if (!font_weight_.empty())
        {
            out << " font-weight=\""sv << font_weight_ << "\""sv;
        }
        
        out << ">" << data_ << "</text>";
    }

    // ---------- Document ------------------   

    // [Отлично] Интересное решение разнести шапку svg по параметрам. Интересно, через сколько лет она поменяется...
    // Но деталь всё равно интересная
    Document::Document() :
        document_objects_(),
        xml_version_("1.0"),
        encoding_("UTF-8"),
        xmlns("http://www.w3.org/2000/svg"),
        xmlns_version_("1.1")
    {
    }

    void Document::AddPtr(std::unique_ptr<Object>&& object) {
        document_objects_.emplace_back(std::move(object));
    }

    void Document::Render(std::ostream& out) const {
        out << "<?xml version=\""sv << xml_version_ << "\" encoding=\"" << encoding_ << "\" ?>\n";
        out << "<svg xmlns=\""sv << xmlns << "\" version=\"" << xmlns_version_ << "\">\n";
        for (const auto& object : document_objects_)
        {
            out << " ";
            object->Render(out);
        }
        out << "</svg>";
    }


}  // namespace svg
