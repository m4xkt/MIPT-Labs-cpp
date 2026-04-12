#include <iostream>
#include <deque>
#include <string>
#include <stdexcept>
#include <cstddef>

using std::endl;
using std::cout;

template <typename T, typename Container = std::deque<T>>
class Stack {
protected:
    Container c;

public:
    Stack() = default;
    explicit Stack(const Container& cont) : c(cont) {}

    // добавляем элемент
    void push(const T& value) { c.push_back(value); }

    // удаляем элемет
    void pop() {
        if (c.empty()) {
            throw std::runtime_error("Stack::pop() called on empty stack");
        }
        c.pop_back();
    }

    // ссылка на последний
    T& top() {
        if (c.empty()) {
            throw std::runtime_error("Stack::top() called on empty stack");
        }
        return c.back();
    }

    const T& top() const {
        if (c.empty()) {
            throw std::runtime_error("Stack::top() called on empty stack");
        }
        return c.back();
    }

    bool empty() const { return c.empty(); }

    std::size_t size() const { return c.size(); }
};

template <>
class Stack<char, std::string> {
protected:
    std::string c;

public:
    Stack() = default;
    explicit Stack(const std::string& str) : c(str) {}

    void push(char value) { c.push_back(value); }

    void pop() {
        if (c.empty()) {
            throw std::runtime_error("Stack::pop() called on empty stack");
        }
        c.pop_back();
    }

    char& top() {
        if (c.empty()) {
            throw std::runtime_error("Stack::top() called on empty stack");
        }
        return c.back();
    }

    const char& top() const {
        if (c.empty()) {
            throw std::runtime_error("Stack::top() called on empty stack");
        }
        return c.back();
    }

    bool empty() const { return c.empty(); }
    std::size_t size() const { return c.size(); }
};


int main() {
    // deque<int>
    Stack<int> int_stack;
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);

    cout << "int_stack size: " << int_stack.size() << endl;
    cout << "int_stack top:  " << int_stack.top() << endl;
    int_stack.pop();
    cout << "after pop, top: " << int_stack.top() << endl << endl;

    // string
    Stack<char, std::string> char_stack;
    char_stack.push('H');
    char_stack.push('e');
    char_stack.push('l');
    char_stack.push('l');
    char_stack.push('o');

    cout << "char_stack size: " << char_stack.size() << endl;
    cout << "char_stack top:  " << char_stack.top() << endl;
    
    cout << "Popping all chars: ";
    while (!char_stack.empty()) {
        cout << char_stack.top();
        char_stack.pop();
    }
    cout << endl;

    return 0;
}