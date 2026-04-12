#include <array>
#include <tuple>
#include <cstddef>
#include <iostream>
#include <utility>

using std::endl;
using std::cout;

// вспомогательная функция для вычисления индекса
template<std::size_t... Ns>
constexpr std::size_t get_index_in_array(std::size_t k, std::size_t array_pos) {
    constexpr std::size_t sizes[] = {Ns...};
    constexpr std::size_t num_arrays = sizeof...(Ns);
    
    std::size_t stride = 1;
    for (std::size_t j = array_pos + 1; j < num_arrays; ++j) {
        stride *= sizes[j];
    }
    return (k / stride) % sizes[array_pos];
}

// генерация одного кортежа для индекса k
template<std::size_t k, std::size_t... Ns, std::size_t... Is, typename... Arrays>
constexpr auto make_tuple_at(std::index_sequence<Is...>, const Arrays&... arrays) {
    constexpr std::size_t indices[] = {get_index_in_array<Ns...>(k, Is)...};
    auto arr_tuple = std::forward_as_tuple(arrays...);
    return std::make_tuple(std::get<Is>(arr_tuple)[indices[Is]]...);
}

//генерация всех кортежей через параметризованную развёртку
template<typename... Ts, std::size_t... Ns, std::size_t... Ks>
constexpr auto cartesian_product_impl(std::index_sequence<Ks...>, 
                                       const std::array<Ts, Ns>&... arrays) {
    return std::array<std::tuple<Ts...>, sizeof...(Ks)>{
        make_tuple_at<Ks, Ns...>(std::index_sequence_for<Ts...>{}, arrays...)...
    };
}

// декартово произведенме
template<typename... Ts, std::size_t... Ns>
constexpr auto cartesian_product(const std::array<Ts, Ns>&... arrays) {
    constexpr std::size_t total_size = (Ns * ...);
    return cartesian_product_impl(std::make_index_sequence<total_size>{}, arrays...);
}

int main() {
    constexpr std::array<int, 2> arr1 = {1, 2};
    constexpr std::array<char, 3> arr2 = {'a', 'b', 'c'};
    constexpr std::array<double, 2> arr3 = {0.5, 1.5};

    constexpr auto product = cartesian_product(arr1, arr2, arr3);

    cout << "декартово произведение: " << endl;
    for (const auto& tup : product) {
        cout << std::get<0>(tup) << " " << std::get<1>(tup) << " " << std::get<2>(tup) << endl;
    }
    return 0;
}