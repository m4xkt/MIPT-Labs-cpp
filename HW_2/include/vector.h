#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class subvector {
public:
    T *mas;
    unsigned int top;
    unsigned int capacity;

    subvector();
    subvector(unsigned int size, T value = T{});
    ~subvector();
    subvector(const subvector& rhs);
    subvector& operator=(const subvector& rhs);

    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;

    bool push_back(const T& d);
    T pop_back();
    bool resize(unsigned int new_capacity);
    void shrink_to_fit();
    void clear();
};

#endif