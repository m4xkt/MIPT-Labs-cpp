#include <iostream>
using std::cout;
using std::cin;
using std::endl;
// Чтобы сделать list более похожим на класс, давайте инкапсулировать указатель на начальный элемент

template<typename T>
class subforwardlist {

// структура, описывающая узел списка (раньше указатель на неё был самим списком)
    struct Node {
        T data;
        Node* next;
        
		/*
        Node(const T& value, Node* ptr = nullptr) : data(value), next(ptr) {
            cout << "Node Ctor" << endl;
        }
		*/
    };

    Node* begin = nullptr;
//	Node * end; // (опционально !) можете хранить указатель на последний элемент

public:
    // далее описание методов (и только их!)

    // добавление элемента в конец
    void push_back(const T& data) {
        Node** current = &begin;
        while (*current)
            current = &(*current)->next;
            
        *current = new Node(data);
    }
    
	// удаление элемента с конца (если пустой -- возвращать T{} (default конструирование объекта типа T))
    T pop_back() {
        if (!begin) return T{};
        
        if (!begin->next) {
            T data = begin->data;
            delete begin;
            begin = nullptr;
            return data;
        }
        
        Node* current = begin;
        while (current->next->next) {
            current = current->next;
        }
        T data = current->next->data;
        delete current->next;
        current->next = nullptr;
        return data;
    }

	//добавление элемента в начало недосписка
    void push_forward(const T& data) {
        begin = new Node(data, begin);
    }

	//удаление элемента из начала недосписка (если пустой -- возвращать T{} (default конструирование объекта типа T))
    T pop_forward() {
        if (!begin) return T{};
        
        T data = begin->data;
        Node* temp = begin;
        begin = begin->next;
        delete temp;
        return data;
    }

	//добавление элемента с порядковым номером where
    void push_where(unsigned int where, const T& data) {
        if (where == 0) {
            push_forward(data);
            return;
        }
        
        Node* current = begin;
        for (unsigned int i = 0; current && i < where - 1; ++i) {
            current = current->next;
        }
        
        if (!current) {
            push_back(data);
        } else {
            current->next = new Node(data, current->next);
        }
    }

	//удаление элемента с порядковым номером where (если пустой -- возвращать T{} (default конструирование объекта типа T))
    T erase_where(unsigned int where) {
        if (!begin) return T{};
        
        if (where == 0) {
            return pop_forward();
        }
        
        Node* current = begin;
        for (unsigned int i = 0; current && i < where - 1; ++i) {
            current = current->next;
        }
        
        if (!current || !current->next) {
            return T{};
        }
        
        Node* temp = current->next;
        T data = temp->data;
        current->next = temp->next;
        delete temp;
        return data;
    }

	//определить размер недосписка
    unsigned int size() const {
        unsigned int i = 0;
        Node* current = begin;
        while (current) {
            current = current->next;
            i++;
        }
        return i;
    }

	//операции для правила пяти дефолтные, на них забиваем
};
