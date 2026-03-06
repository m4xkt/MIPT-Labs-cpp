#ifndef SUBVECTOR_H
#define SUBVECTOR_H

struct subvector {
    int* mas;              ///< Указатель на динамический массив
    unsigned int top;      ///< Индекс последнего элемента + 1 (количество элементов)
    unsigned int capacity; ///< Текущая выделенная ёмкость массива
};

bool init(subvector* qv);
bool resize(subvector* qv, unsigned int new_capacity);
bool push_back(subvector* qv, int elem);
int pop_back(subvector* qv);
void shrink_to_fit(subvector* qv);
void clear(subvector* qv);
void destructor(subvector* qv);

#endif