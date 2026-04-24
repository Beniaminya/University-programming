#include <iostream>
#include <memory>
#include <string>
using namespace std;


class Base {
    public:
    virtual ~Base() = default;
    virtual string name() const{
        return "Base";
    }
};

class Derived1 : public Base {
    public:
    std::string name() const override {return "Derived1";}
};

class Derived2 : public Base {
    public:
    std::string name() const override {return "Derived2";}
};

void process(std::shared_ptr<Base> ptr) {
    std::cout << ptr->name() << std::endl;

    std::shared_ptr<Derived1> d1 = std::dynamic_pointer_cast<Derived1>(ptr);
    if (d1) {
        std::cout << "Is Derived1" << std::endl;
    }

    std::shared_ptr<Derived2> d2 = std::static_pointer_cast<Derived2>(ptr);
    (void)d2;
    std::cout << "Static cast to Derived2" << std::endl;
}

template<typename T>
std::shared_ptr<T> smartCast(std::shared_ptr<Base> ptr) {
    return std::dynamic_pointer_cast<T>(ptr);
}

