#include<iostream>
using std::cout;
using std::cin;
using std::endl;

//тот же вектор, только в профиль...
template<typename T>
class subvector {
public:
    T *mas;
    unsigned int top;
    unsigned int capacity;

    //созидаем
    subvector() : mas(nullptr), top(0), capacity(0) {
        cout << "Ctor" << endl;
    }

    //УБИВАЕМ
    ~subvector() {
        cout << "Dtor" << endl;
        delete[] mas;
    }

    //копи конструктор
    subvector(const subvector& rhs) : mas(nullptr), top(0), capacity(0) {
        if (rhs.capacity > 0) {
            mas = new T[rhs.capacity];
            capacity = rhs.capacity;
            top = rhs.top;
            for (unsigned int i = 0; i < top; i++)
                mas[i] = rhs.mas[i];
        }
    }

    //===РАВНО===
    subvector& operator=(const subvector& rhs) {
        if (this != &rhs) {
            delete[] mas;
            mas = nullptr;
            top = 0;
            capacity = 0;
            
            if (rhs.capacity > 0) {
                mas = new T[rhs.capacity];
                capacity = rhs.capacity;
                top = rhs.top;
                for (unsigned int i = 0; i < top; i++)
                    mas[i] = rhs.mas[i];
            }
        }
        return *this;
    }


    // добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости
    bool push_back(const T& d) {
        if (top >= capacity) {
            unsigned int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            if (!resize(new_capacity))
                return false;
        }
        mas[top] = d;
        top++;
        return true;
    }

    // удаление элемента с конца недовектора, значение удаленного элемента вернуть (если недовектор пустой, вернуть T{})
    T pop_back() {
        if (!top)
            return T{};
        
        top--;
        return mas[top];
    }

    // увеличить емкость недовектора 
    // (можно использовать и для уменьшения - тогда, в рамках данной реализации, 
    // если top меньше новой capacity, то копируем только то, что влезает, и уменьшаем top до capacity)
    bool resize(unsigned int new_capacity) {
        if (new_capacity == capacity)
            return true;
        
        if (new_capacity == 0) {
            delete[] mas;
            mas = nullptr;
            top = 0;
            capacity = 0;
            return true;
        }
        
        T* new_mas = new T[new_capacity];
        unsigned int copy = (top < new_capacity) ? top : new_capacity;
        
        for (unsigned int i = 0; i < copy; i++)
            new_mas[i] = mas[i];
        
        delete[] mas;
        mas = new_mas;
        capacity = new_capacity;
        top = copy;
        
        return true;
    }

    // очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top
    void shrink_to_fit() {
        if (top == 0) {
            delete[] mas;
            mas = nullptr;
            capacity = 0;
            return;
        }
        
        if (top == capacity)
            return;
        
        T* new_mas = new T[top];
        for (unsigned int i = 0; i < top; i++)
            new_mas[i] = mas[i];
        
        delete[] mas;
        mas = new_mas;
        capacity = top;
    }

    // очистить содержимое недовектора, занимаемое место при этом не меняется
    void clear() {
        top = 0;
    }
};
