#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <chrono>
#include <algorithm>
#include <functional>

using std::endl;
using std::cout;

// быстро сортируем за нлогн

template<typename RandomAccessIterator, typename Compare>
void q_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    if (first == last) return;
    
    auto partition = [&](auto left, auto right) {
        auto pivot = *(left + (right - left) / 2);
        auto i = left - 1;
        auto j = right + 1;
        
        while (true) {
            do {
                ++i;
            } while (comp(*i, pivot));
            do {
                --j;
            } while (comp(pivot, *j));
            
            if (i >= j) return j;
            std::iter_swap(i, j);
        }
    };
    
    auto quicksort = [&](auto& self, auto left, auto right) -> void {
        while (left < right) {
            auto p = partition(left, right);
            if (p - left < right - p) {
                self(self, left, p);
                left = p + 1;
            } else {
                self(self, p + 1, right);
                right = p;
            }
        }
    };
    
    quicksort(quicksort, first, last - 1);
}

// перегрузка с компаратором
template<typename RandomAccessIterator>
void q_sort(RandomAccessIterator first, RandomAccessIterator last) {
    q_sort(first, last, std::less<decltype(*first)>());
}

// функтор
struct Greater {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

// обычный компаратор
template<typename T>
bool less_func(const T& a, const T& b) {
    return a < b;
}

int main() {
    cout << "Сортируем вектор: ";
    std::vector<int> vec = {5, 2, 8, 1, 9, 3};
    q_sort(vec.begin(), vec.end());
    for (int x : vec) std::cout << x << " ";
    cout << endl;
    
    cout << "сортируем деку: ";
    std::deque<int> deq = {5, 2, 8, 1, 9, 3};
    q_sort(deq.begin(), deq.end());
    for (int x : deq) std::cout << x << " ";
    cout << endl;
    
    cout << "сортировка с обычным компаратором ";
    std::vector<int> vec2 = {5, 2, 8, 1, 9, 3};
    q_sort(vec2.begin(), vec2.end(), less_func<int>);
    for (int x : vec2) std::cout << x << " ";
    cout << endl;
    
    std::cout << "сортировка с лямбдой: ";
    std::vector<int> vec3 = {5, 2, 8, 1, 9, 3};
    q_sort(vec3.begin(), vec3.end(), [](int a, int b) { return a > b; });
    for (int x : vec3) std::cout << x << " ";
    std::cout << endl;
    
    std::cout << "сортировка с функтором: ";
    std::vector<int> vec4 = {5, 2, 8, 1, 9, 3};
    q_sort(vec4.begin(), vec4.end(), Greater());
    for (int x : vec4) std::cout << x << " ";
    std::cout << endl;

/*
//list
std::list<int> lst = {5, 2, 8};
q_sort(lst.begin(), lst.end()); // ошибка
//list использует bidirectional_iterator, а не random_access_iterator\n\n";
*/
    std::cout << endl << endl << "измеряем время";
    
    const int SIZE = 100000;
    std::vector<int> vec_perf(SIZE);
    std::deque<int> deq_perf(SIZE);
    
    // заполняем случайными данными
    for (int i = 0; i < SIZE; ++i) {
        vec_perf[i] = deq_perf[i] = rand() % 10000;
    }
    
    // измеряем vector
    auto start = std::chrono::high_resolution_clock::now();
    q_sort(vec_perf.begin(), vec_perf.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto vec_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // обновляем данные
    for (int i = 0; i < SIZE; ++i) {
        deq_perf[i] = rand() % 10000;
    }
    
    // измеряем deque
    start = std::chrono::high_resolution_clock::now();
    q_sort(deq_perf.begin(), deq_perf.end());
    end = std::chrono::high_resolution_clock::now();
    auto deq_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Время сортировки вектора из " << SIZE << " элементов: " 
              << vec_time.count() << " мс\n";
    std::cout << "Время сортировки деки из " << SIZE << " элементов: " 
              << deq_time.count() << " мс\n";
    
    return 0;
}
