#include<iostream>

using std::cout;
using std::cin;
using std::endl;

struct subvector {
    int *mas;              //сам вектор
    unsigned int top;      //индекс последней ненулевой компоненты
    unsigned int capacity; //размернсть вектора
};

// инициализация пустого недовектора (top и capacity по нулям, а mas это NULL)
bool init(subvector *qv)
{
    qv->top = 0;
    qv->capacity = 0;
    qv->mas = NULL;
    return 1;
}; 

//Доп. функция для расширения НАТО (subvector) на восток
//(оказалась не нужна, так как есть resize)
/*
void extend(subvector* v_p) {
    int *new_data = new int[2 * v_p->capacity];
    for (int i = 0; i < v_p->top; i+=1) {
        new_data[i] = v_p->mas[i];
    }
    delete[] v_p->mas;
    v_p->mas = new_data;
    v_p->capacity *= 2;
}
*/

// увеличить емкость недовектора (можно использовать и для уменьшения - тогда, в рамках данной реализации, если top меньше новой capacity, то копируем только то, что влезает, и уменьшаем top до capacity)
bool resize(subvector *qv, unsigned int new_capacity)
{
    int *new_data = new int[new_capacity];
    for (unsigned i = 0; i < ((qv->capacity > new_capacity) ? new_capacity : qv->capacity); i+=1) 
        new_data[i] = qv->mas[i];
    
    delete[] qv->mas;
    qv->mas = new_data;
    qv->capacity = new_capacity;
    return 1;
}; 

// добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости
bool push_back(subvector* qv, int elem) {
    if (qv->top < qv->capacity) 
        qv->mas[qv->top++] = elem;
    else if(qv->capacity == 0)
    {
        resize(qv, 1);
        qv->mas[qv->top++] = elem;
    } 
    else
    {
        //Каждый вызов этой функции добавляет (new_capacity-capacity) мм^2 к территории, на которую распространяется влияние нато.
        resize(qv, qv->capacity*2);
        qv->mas[qv->top++] = elem;
    };
    return 1;
}
// удаление элемента с конца недовектора, значение удаленного элемента вернуть (если недовектор пустой, вернуть ноль)
int pop_back(subvector *qv)
{
    if (qv->top == 0)
        return 0;
    int x = qv->mas[(qv->top)-1];
    qv->mas[qv->top-1] = 0;
    qv->top--;
    return x;
}; 

// очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top
void shrink_to_fit(subvector *qv)
{
    if (qv->top == 0)
    {
        delete[] qv->mas;
        qv->mas = nullptr;
        qv->capacity = 0;
        return;
    }

    if (qv->top == qv->capacity) 
        return;

    resize(qv, qv->top);
}; 
// очистить содержимое недовектора, занимаемое место при этом не меняется
void clear(subvector *qv)
{
    qv->top = 0;
}; 
// очистить всю используемую память, инициализировать недовектор как пустой
void destructor(subvector *qv)
{
    delete[] qv->mas;
    init(qv);
};