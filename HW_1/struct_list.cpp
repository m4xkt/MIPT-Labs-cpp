#include<iostream>

using std::cout;
using std::cin;
using std::endl;

struct subforwardlist {
    int data;               //элемент списка
    subforwardlist* next;   //указатель на след. элемент
};

//инициализация пустого недосписка 
bool init(subforwardlist** sfl) {
    *sfl = nullptr;
    return true;
}
//добавление элемента в конец недосписка	
bool push_back(subforwardlist** sfl, int d) {
    subforwardlist* new_elem = new subforwardlist;
    new_elem->data = d;
    new_elem->next = nullptr;

    if (*sfl == nullptr) 
        *sfl = new_elem;
    else 
    {
        subforwardlist* cur = *sfl;
        while (cur->next != nullptr)
            cur = cur->next;
        cur->next = new_elem;
    }
    return true;
}
//удаление элемента с конца недосписка, если пустой - возвращать 0
int pop_back(subforwardlist** sfl) {
    if (*sfl == nullptr)
        return 0;

    if ((*sfl)->next == nullptr) {
        int data = (*sfl)->data;
        delete *sfl;
        *sfl = nullptr;
        return data;
    }

    subforwardlist* cur = *sfl;
    while (cur->next->next != nullptr)
        cur = cur->next;

    int data = cur->next->data;
    delete cur->next;
    cur->next = nullptr;

    return data;
}
//добавление элемента в начало недосписка		
bool push_forward(subforwardlist** sfl, int d) {
    subforwardlist* new_elem = new subforwardlist;
    new_elem->data = d;
    new_elem->next = *sfl;
    *sfl = new_elem;

    return true;
}
//удаление элемента из начала недосписка, если пустой - возвращать 0
int pop_forward(subforwardlist** sfl) {
    if (*sfl == nullptr) 
        return 0;
    
    subforwardlist* temp = *sfl;
    int data = temp->data;
    *sfl = (*sfl)->next;
    delete temp;

    return data;
}
//добавление элемента с порядковым номером where		
bool push_where(subforwardlist** sfl, unsigned int where, int d) {
    if (where == 0)    
        return push_forward(sfl, d);
    
    subforwardlist* cur = *sfl;
    for (unsigned int i = 0; i < where - 1; ++i) {
        if (cur->next == nullptr)
            break;
        cur = cur->next;
    }

    subforwardlist* new_node = new subforwardlist;
    new_node->data = d;
    new_node->next = cur->next;
    cur->next = new_node;

    return true;
}
//удаление элемента с порядковым номером where, если пустой - возвращать 0
int erase_where(subforwardlist** sfl, unsigned int where) {
    if (*sfl == nullptr) 
        return 0;

    if (where == 0)
        return pop_forward(sfl);

    subforwardlist* cur = *sfl;
    for (unsigned int i = 0; i < where - 1; ++i) {
        if (cur->next == nullptr) 
            return 0;
        cur = cur->next;
    }

    if (cur->next == nullptr)
        return 0;

    subforwardlist* temp = cur->next;
    int data = temp->data;
    cur->next = temp->next;
    delete temp;

    return data;
}
//определить размер недосписка
unsigned int size(subforwardlist** sfl) {
    unsigned int count = 0;
    subforwardlist* cur = *sfl;
    while (cur != nullptr) {
        ++count;
        cur = cur->next;
    }
    return count;
}
//очистить содержимое недосписка
void clear(subforwardlist** sfl) {
    while (*sfl != nullptr)
        pop_forward(sfl);
}