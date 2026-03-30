#include <iostream>
#include <string>

using namespace std;

class Tracker {
public:
    int id;

    Tracker() : id(0) {
        cout << "Default: 0\n";
    }

    Tracker(int i) : id(i) {
        cout << "Param: " << id << "\n";
    }

    Tracker(double d) : Tracker(static_cast<int>(d)) {}

    explicit Tracker(const string& str) : id(0) {
        cout << "String: " << str << "\n";
    }

    Tracker(const Tracker& other) : id(other.id) {
        cout << "Copy: from " << other.id << " to " << id << "\n";
    }

    Tracker(Tracker&& other) noexcept : id(other.id) {
        cout << "Move: from " << other.id << " to " << id << "\n";
    }

    ~Tracker() {
        cout << "Destroy: " << id << "\n";
    }
};