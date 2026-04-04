#include <iostream>
#include <memory>
#include <string>
using namespace std;


class Base {
    public:
    virtual string name() const{
        return "Base";
    }
};

class Derived1 : public Base {
    
};

class Derived2 : public Base {
    // ваш код
};

void process(std::shared_ptr<Base> ptr) {
    // ваш код
}

template<typename T>
std::shared_ptr<T> smartCast(std::shared_ptr<Base> ptr) {
    // ваш код
}