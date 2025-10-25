#include<iostream>


using std::cout;
using std::cin;
using std::endl;

//float in memory (like int, but float)
void bin_float(float *n) {
    cout << endl << "=====ПРЕДСТАВЛЕНИЕ ФЛОАТ В ПАМЯТИ=====" << endl << endl;
    int *i = (int*) n;
    cout << "Your float in memory: "<< endl;
    for(int j = 31; j >= 0; --j){
        cout << ((*i >> j) & 1);
        if (j == 31 || j == 23)
            cout << " ";
    }

    cout << endl << endl;
}

//difference between numberx
void sensetivity() {
    cout << endl << "=====РАЗНИЦА МЕЖДУ НОМЕРАМИ (1.2)=====" << endl << endl;
    float x = 1.0f;
    while (x != (x+1.0f))
        x *= 2;
    cout << "x0: для любого x > x0 -> x == x+1: " << static_cast<int>(x) << endl;

    cout << "Числа float, между которыми фатальная ошибка составляет 1.0: " << endl
    << "(1 + 0)*2^23 = " << (2<<23) << " и (1 + 2^-23)*2^23) = "<< ((2<<23)+1) << endl << endl;
}

//ROW
//если бы ряд расходился, цикл был бы бесконечным
void row() {
    cout << endl << "=====ИССЛЕДОВАНИЕ РЯДА=====" << endl << endl;
    float sum = 0.0f;
    int k = 1;
    do{
        sum += 1.0f/k;
        ++k;
    }while(sum+(1.0f/k) != sum);
    cout << "SUM is: " << sum << endl;
    cout << "Искомое число (задание - ряд):  " << 1.0f/k << " ||| С порядковым номером: " << k <<  endl << endl;

    sum = 0.0f;
    for (int i = 1; i <= k + 100; ++i) {
        sum += 1.0f / i;
    }
    cout << "Новая сумма (к+100) is " << sum << endl;

    sum = 0.0f;
    for (int i = k + 100; i >= 1; --i) {
        sum += 1.0f / i;
    }
    cout << "Реверснутая сумма is " << sum << endl;
}

int main()
{
    float num;
    cin >> num;

    bin_float(&num);

    sensetivity();

    //no more associativity
    cout << endl << "=====АССОЦИАТИВНОСТЬ=====" << endl << endl;
    cout << static_cast<bool>(0.1f + (0.1f+0.5f) == (0.1f + 0.1f)+0.5f) << endl;
    /*
    Здесь равенство не выполняется, тк 0.1 невозможно передать во float баз потерь точности,
    потому что это число не представимо в виде (1+ 1/2*k1 + 1/4*k2 ... + 2^-23 * k23)*2^exp,
    где k1 ... k23 - это нули или единицы. При сложении 0.1 и 0.1, результат получается
    0.200000002980232239, а 0.1+0.5 = 0.60000002384185791. теперь мы можем убедиться, что 
    0,100000001490116119+0.60000002384185791 != 0.200000002980232239 + 0.5
    */

    row();

    /*
    СРАВНЕНИЕ ЧЕРЕЗ ==:
    Сравнивать через == флоаты опасно, так как там есть погрешность, которая может не быть учтена.
    Поэтому стоит сравнивать данные этого типа следующим образом: abs(a-b) < 2^-23 * 2^e;

    */


    cout << endl << "=====КОНЕЦ=====" << endl << endl;
    return 0;
}