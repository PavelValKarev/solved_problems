class MagicHat {
public:
    //реализуем конструкторы////
    MagicHat() {
        MagicHat::SetVTable(this);
        std::cout << "MagicHat::Ctor()"sv << std::endl;
    }

    MagicHat(const MagicHat&) {
        MagicHat::SetVTable(this);
        std::cout << "MagicHat::Ctor()"sv << std::endl;
    }
  ....
