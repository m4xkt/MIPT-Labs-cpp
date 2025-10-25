#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/**
Сортирует массив по заданному алгоритму 
 @param n -- размер массива
 @param array -- массив (сколько звездочек насыпать в тип решайте сами)
 */

 //---2.1---
namespace sort_bin_kucha{

    //Обмен жизненным опытом
    void swap(int *arr, int i1, int i2)
    {
        int temp = *(arr+i1);
        *(arr+i1) = *(arr+i2);
        *(arr+i2) = temp;
    }

    //Наваливаем кучу
    void kucha(int *array, int i, int n)
    {
        while (true) {
            int max_ind = i;
            int l_ind = 2 * i + 1;
            int r_ind = 2 * i + 2;

            if (l_ind < n && array[l_ind] > array[max_ind])
                max_ind = l_ind;
            if (r_ind < n && array[r_ind] > array[max_ind])
                max_ind = r_ind;
            if (max_ind == i) break;
            
            swap(array, i, max_ind);
            i = max_ind;
        }
    }

    //Сортировка мусора
    void my_sort(int *array, int n)
    {
        //Перелопачиваем массив, чтобы он стал кучей
        for (int i = (n/2 - 1); i >= 0; i--)
            kucha(array, i, n);
        
        for (int i = n - 1; i > 0; i--) {
            swap(array, 0, i);
            kucha(array, 0, i);
        }
    };

    //Сюда вводить
    /*
    void init(int *arr, int *num){
        int n = *num;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> *(arr+j);
    }
    */
    void clear(int *arr){
        delete[] arr;
    }
}

//---2.2---
namespace sort_sliyaniem{
    //Обоюдовыгодный союз массивов (слияние)
    void sliyanie(int *arr, int l_ind, int mid_ind, int r_ind)
    {
        int i1 = 0, i2 = 0;
        int *res = new int[r_ind-l_ind];

        //Проходим массивы и, находя наименьший невыбранный элемент,
        //ставим его на первое место в объединённом массиве
        while(l_ind+i1 < mid_ind && mid_ind+i2 < r_ind)
        {
            if(*(arr+l_ind+i1) < *(arr+mid_ind+i2)){
                *(res+i1+i2) = *(arr+l_ind+i1);
                ++i1;
            }
            else{
                *(res+i1+i2) = *(arr+mid_ind+i2);
                ++i2;
            }
        }
        
        //Проверяем остатки массива на всякий пожарный
        while(l_ind+i1 < mid_ind){
            *(res+i1+i2) = *(arr+l_ind+i1);
            ++i1;
        }
        while(mid_ind+i2 < r_ind){
            *(res+i1+i2) = *(arr+mid_ind+i2);
            ++i2;
        }

        for(int j = 0; j < i1+i2; j++)
            *(arr+l_ind+j) = *(res+j);
        delete[] res;
    }

    //Сортируется подотрезок массива от элемента с индексом l_ind до r_ind
    void my_sort(int* array, int r_ind, int l_ind=0)
    {
        if (l_ind+1 >= r_ind)
            return ;
        
        int mid_ind = (l_ind+r_ind)/2;
        my_sort(array, mid_ind, l_ind);
        my_sort(array, r_ind, mid_ind);
        sliyanie(array, l_ind, mid_ind, r_ind);
    }

}

using sort_bin_kucha::clear;

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];
    for (int j = 0; j < n; j++)
        cin >> *(arr+j);
    
    cout << endl << "Введите 1, если хотите сортировать бинарной кучей, или 0, если слиянием: ";
    bool x;
    cin >> x;

    //===СОРТИРОВКА БИНАРНОЙ КУЧЕЙ===
    if (x){
        //sort_bin_kucha::init(arr, &n);
        sort_bin_kucha::my_sort(arr, n);
        for (int i = 0; i < n; i++){
            cout << *(arr+i) << " ";
        }
    }
    //===СОРТИРОВКА СИЯНИЕМ===
    else{
        sort_sliyaniem::my_sort(arr, n);
        for (int i = 0; i < n; i++){
            cout << *(arr+i) << " ";
        }
    }
    clear(arr);

    return 0;
}