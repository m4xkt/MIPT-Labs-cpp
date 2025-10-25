#include <iostream>

using std::cout;
using std::cin;
using std::endl;

//1.1
void bin_signed(int *n){
    int size = 32;
    cout << "Signed bin: " << endl;
    for(int i = size-1; i >= 0; --i)
        cout << ((*n >> i) & 1);
    cout << endl << endl;
};

//1.2
void bin_unsigned(unsigned *n){
    int size = 32;
    cout << "Unsigned bin: " << endl;
    for(int i = size-1; i >= 0; --i)
        cout << ((*n >> i) & 1);
    cout << endl << endl;
};

//1.3
void rubrika_experimeti(){
    int x = __INT_MAX__;
    cout << __INT_MAX__ + 1 << endl;
    int size = 32;
    cout << "====INT_MAX в двоичной системе координат====" << endl << endl;
    for(int i = size-1; i >= 0; --i)
        cout << ((x >> i) & 1);
    cout << endl << "Этот результат получается, потому что самый первый бит в int отвечает за знак."
    << endl << "То есть мы прибавляем к 2147483648 1 и получаем 10...0 в двоичном виде," << endl 
    << "но это соответствует наименьшему отриц. числу." << endl << endl;

    cout << "====Делаем то же самое, но с ансингед инт====" << endl << endl;
    unsigned x1 = __UINT32_MAX__;
    unsigned nol = 0;
    cout << nol - 1 << " - это 0-1" << endl;
    cout << __UINT32_MAX__ +1<< " - это - АНСИГНЕД_МАКС+1" <<endl;
    cout << "UINT_MAX в двоичной системе координат:" << endl;
    for(int i = size-1; i >= 0; --i)
        cout << ((x1 >> i) & 1);
    cout << endl << "_____________________________" << endl;
    cout << endl << "Этот результат получается, потому что все биты равны 1 и когда мы прибавляем ещё 1,"
    << endl << "наше двоичное число переходит на следующий разряд, как при 11+01 = 100," << endl 
    << "соответственно всё ОБНУЛЯЕТСЯ, а единственная единичка убивается, так как не помещается в область памяти." << endl 
    << "Про ноль объяснение аналогично, но обратно..." << endl;
};


int main(){
    int num;
    cout << "Enter signed int: ";
    cin >> num;

    bin_signed(&num);

    unsigned num1;
    cout << "Enter UNsigned int: ";
    cin >> num1;

    bin_unsigned(&num1);

    rubrika_experimeti();

    return 0;
}