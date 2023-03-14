class HeavyObject {
};

class HeavyPairSaver {
public:
    // метод принимает ссылки Forwarding reference
    // реализацию напишем чуть позже
    template <typename T1, typename T2>
    void SaveObject(T1&& object1, T2&& object2) {
        
    }

private:
    HeavyObject object1_;
    HeavyObject object2_;
};

int main() {
    HeavyPairSaver saver;

    // сохраняем временные объекты
    saver.SaveObject(HeavyObject(), HeavyObject());

    // сохраняем постоянные объекты
    // если бы объекты принимались по rvalue-ссылке, здесь возникла бы ошибка
    HeavyObject obj1, obj2;
    saver.SaveObject(obj1, obj2);
}
