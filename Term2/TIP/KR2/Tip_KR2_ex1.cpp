#include <iostream>
#include <memory>
#include <cmath>

class Node {
public:
    int value;
    std::unique_ptr<Node> next;

    Node() : value(0), next(nullptr) {}

    Node(int val) : value(val), next(nullptr) {}

    Node(double val) : Node(static_cast<int>(std::round(val))) {}

    Node(const Node& other) : value(other.value), next(nullptr) {
        if (other.next) {
            next = std::make_unique<Node>(*other.next);
        }
    }

    Node(Node&& other) noexcept 
        : value(other.value), next(std::move(other.next)) {}

    ~Node() {
        std::cout << "~Node(" << std::to_string(value) << ")" << std::endl;
    }
};
