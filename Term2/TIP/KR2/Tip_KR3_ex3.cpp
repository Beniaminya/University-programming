#include <iostream>
#include <string>

class Animal {
public:
    virtual ~Animal() = default;
    virtual std::string speak() const { return "..."; }
};

class Dog : public Animal {
public:
    std::string speak() const override { return "Woof"; }
    void fetch() const {}
};

class Cat : public Animal {
public:
    std::string speak() const override { return "Meow"; }
    void purr() const {}
};

std::string identify(Animal* obj) {
    if (dynamic_cast<Dog*>(obj)) {
        return "Dog: " + obj->speak();
    }
    if (dynamic_cast<Cat*>(obj)) {
        return "Cat: " + obj->speak();
    }
    return "Unknown";
}

void dangerousCast(Animal* obj) {
    int* p = reinterpret_cast<int*>(obj);
    std::cout << *p;
}