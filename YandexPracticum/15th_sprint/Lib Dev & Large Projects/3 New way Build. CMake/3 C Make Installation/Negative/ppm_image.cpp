#include "ppm_image.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

    static const string_view PPM_SIG = "P6"sv;
    static const int PPM_MAX = 255;

    // реализуйте эту функцию самостоятельно
    /*
    Функция SavePPM принимает в качестве аргументов путь к файлу
    file и изображение image в формате PPM и сохраняет его в
    бинарном виде в указанном файле.
    */
    bool SavePPM(const Path& file, const Image& image) {
        ofstream ofs(file, ios::binary);
        /*
        Сначала функция открывает файл для записи в бинарном режиме
        с помощью ofstream ofs(file, ios::binary);. Если файл не
        удалось открыть, функция возвращает false.
        */
        if (!ofs) {
            return false;
        }
        /*
        Затем функция записывает в файл сигнатуру формата PPM - "P6",
        размеры изображения (ширину и высоту) и максимальное значение
        цвета с помощью ofs << PPM_SIG << '\n' << image.GetWidth() <<
        ' ' << image.GetHeight() << '\n' << PPM_MAX << '\n';
        */
        ofs << PPM_SIG << '\n'
            << image.GetWidth() << ' '
            << image.GetHeight() << '\n'
            << PPM_MAX << '\n';

        /*
        Далее функция создает временный буфер std::vector<char> 
        buff(image.GetWidth() * 3);, который используется для записи
        цветов каждого пикселя изображения в файл. 
        */
        std::vector<char> buff(image.GetWidth() * 3);

        /*
        Затем функция проходит по каждому пикселю изображения и записывает
        его цвета в буфер в формате RGB с помощью:
        */
        for (int y = 0; y < image.GetHeight(); ++y) {
            for (int x = 0; x < image.GetWidth(); ++x ) {
                buff[x * 3 + 0] = static_cast<char>(image.GetPixel(x, y).r);
                buff[x * 3 + 1] = static_cast<char>(image.GetPixel(x, y).g);
                buff[x * 3 + 2] = static_cast<char>(image.GetPixel(x, y).b);
            }
            /*
            После того, как буфер заполнен, функция записывает его содержимое
            в файл с помощью ofs.write(buff.data(), image.GetWidth() * 3);.
            */
            ofs.write(buff.data(), image.GetWidth() * 3);
        }
        /*
        Наконец, функция возвращает true, если сохранение прошло успешно.
        */
        return true;
    }

    Image LoadPPM(const Path& file) {
        // открываем поток с флагом ios::binary
        // поскольку будем читать даные в двоичном формате
        ifstream ifs(file, ios::binary);
        std::string sign;
        int w, h, color_max;

        // читаем заголовок: он содержит формат, размеры изображения
        // и максимальное значение цвета
        ifs >> sign >> w >> h >> color_max;

        // мы поддерживаем изображения только формата P6
        // с максимальным значением цвета 255
        if (sign != PPM_SIG || color_max != PPM_MAX) {
            return {};
        }

        // пропускаем один байт - это конец строки
        const char next = ifs.get();
        if (next != '\n') {
            return {};
        }

        Image result(w, h, Color::Black());
        std::vector<char> buff(w * 3);

        for (int y = 0; y < h; ++y) {
            Color* line = result.GetLine(y);
            ifs.read(buff.data(), w * 3);

            for (int x = 0; x < w; ++x) {
                /*
                Данная строка выполняет преобразование целочисленного значения,
                хранящегося в буфере buff, в значение типа byte, и затем
                присваивает это значение к компоненте красного цвета пикселя в
                массиве line, который представляет собой изображение в формате PPM.
                */
                /*
                В частности, buff[x * 3 + 0] представляет собой значение красного
                цвета пикселя, находящегося в строке y и столбце x в файле PPM
                (так как компонента красного цвета имеет смещение 0 в каждом 
                пикселе, а каждый пиксель занимает 3 байта в буфере buff). 
                Затем static_cast<byte>(...) приводит это значение к типу byte,
                который используется в структуре Color для хранения значений
                компонент цвета. Наконец, line[x].r присваивает это значение к
                компоненте красного цвета пикселя в массиве line.
                */
                line[x].r = static_cast<byte>(buff[x * 3 + 0]);
                line[x].g = static_cast<byte>(buff[x * 3 + 1]);
                line[x].b = static_cast<byte>(buff[x * 3 + 2]);
            }
        }

        return result;
    }
    
}  // namespace img_lib
