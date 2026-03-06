#ifndef LIST_H
#define LIST_H

template<typename T>
class subforwardlist {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value, Node* ptr = nullptr) : data(value), next(ptr) {}
    };

    Node* begin;

public:
    subforwardlist() : begin(nullptr) {}
    
    ~subforwardlist() {}
    
    subforwardlist(const subforwardlist&) = delete;
    subforwardlist& operator=(const subforwardlist&) = delete;
    
    subforwardlist(subforwardlist&&) = default;
    subforwardlist& operator=(subforwardlist&&) = default;

    void push_back(const T& data);
    T pop_back();
    void push_forward(const T& data);
    T pop_forward();
    void push_where(unsigned int where, const T& data);
    T erase_where(unsigned int where);
    unsigned int size() const;
    bool empty() const { return begin == nullptr; }
};

#endif