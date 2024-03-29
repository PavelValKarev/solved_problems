class MagicHat {
public:
    //реализуем структуру, в которой будут храниться
    //указатели на функуцию
    struct Vtable {
        //Синтаксис: 
        //-void
        //-в круглых скобках - указатель на функцию
        //имя - с маленькой буквы, чтобы можно было
        //обратиться к этому указателю
        //-в следующих скобках - то что должна принимать
        //эта функция
        //-в первом случае для метода WhatInside() мы
        //будем принимать константный указатель
        void(*inside_this)(const MagicHat*);
        //для реализации деструктора будем применять
        //неконстантный указатель
        void(*delete_this)(MagicHat*);
    };
    virtual void WhatInside() const {
        cout << "Nothing"s << endl;
    }    
};

/*
void(*inside_this)(const MagicHat*);
Указатель на функцию - это переменная, которая хранит адрес функции. 
В данном случае void(*inside_this)(const MagicHat*) - это указатель
на функцию, которая принимает указатель на const MagicHat и не
возвращает значения. Такой указатель может использоваться, например,
для передачи функции в качестве аргумента в другую функцию или для
вызова функции по адресу, хранимому в указателе.
*/
