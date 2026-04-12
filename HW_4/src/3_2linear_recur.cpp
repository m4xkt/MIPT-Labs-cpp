#include <array>
#include <iostream>
#include <utility>

using std::endl;
using std::cout;

// Вспомогательная функция: скалярное произведение с использованием index_sequence
template<size_t N, size_t... I>
constexpr long long dot_product_impl(const std::array<long long, N>& a,
                                      const std::array<long long, N>& b,
                                      std::index_sequence<I...>) {
    return ((a[I] * b[I]) + ...);  
}

template<size_t N>
constexpr long long dot_product(const std::array<long long, N>& a,
                                 const std::array<long long, N>& b) {
    return dot_product_impl(a, b, std::make_index_sequence<N>{});
}

// Рекурсивное вычисление k-го элемента с использованием index_sequence
template<size_t N, size_t... I>
constexpr long long compute_element_impl(const std::array<long long, N>& coeffs,
                                          const std::array<long long, N>& initial,
                                          size_t k,
                                          std::index_sequence<I...>) {
    if constexpr (N == 0) {
        return 0;
    } else {
        if (k < N) {
            return initial[k];
        }
        
        // Рекурсивно вычисляем предыдущие N значений
        std::array<long long, N> prev_values = {
            compute_element_impl<N>(coeffs, initial, k - N + I, std::index_sequence<I...>{})...
        };
        
        return dot_product(coeffs, prev_values);
    }
}

template<size_t N>
constexpr long long compute_element(const std::array<long long, N>& coeffs,
                                    const std::array<long long, N>& initial,
                                    size_t k) {
    return compute_element_impl(coeffs, initial, k, std::make_index_sequence<N>{});
}

// Шаблон линейного рекуррента
template<size_t N>
struct LinearRecurrence {
    std::array<long long, N> coeffs;
    std::array<long long, N> initial;
    
    constexpr long long compute(size_t k) const {
        return compute_element(coeffs, initial, k);
    }
};

// constexpr функции для создания рекуррентов
template<size_t N>
constexpr LinearRecurrence<N> make_recurrence(std::array<long long, N> coeffs,
                                               std::array<long long, N> initial) {
    return LinearRecurrence<N>{coeffs, initial};
}

// Определения последовательностей
constexpr auto fibonacci = make_recurrence<2>({1, 1}, {0, 1});

// x_{n+2} = 2*x_{n+1} + 3*x_n, x_0=1, x_1=1
constexpr auto custom = make_recurrence<2>({3, 2}, {1, 1});

int main() {
    constexpr auto fib_10 = fibonacci.compute(10);
    constexpr auto fib_15 = fibonacci.compute(15);
    constexpr auto custom_5 = custom.compute(5);
    
    cout << "Fibonacci(10) = " << fib_10 << endl;   
    cout << "Fibonacci(15) = " << fib_15 << endl; 
    cout << "Custom(5) = " << custom_5 << endl; 
    
    cout << endl << "первые 10 фиббоначи: " << endl;
    for (size_t i = 0; i < 10; ++i) {
        cout << "  F(" << i << ") = " << fibonacci.compute(i) << endl;
    }
    
    return 0;
}