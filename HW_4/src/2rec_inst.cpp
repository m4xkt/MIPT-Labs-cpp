#include <tuple>
#include <iostream>
#include <type_traits>
#include <utility>

using std::endl;
using std::cout;

// выход из рекурсии, если индекс достиг количества типов в кортеже
// std::enable_if_t<I == sizeof...(Ts)> делает перегрузку видимой только при выходе из рекурсии
template<std::size_t I = 0, typename Func, typename Tuple>
std::enable_if_t<I == std::tuple_size_v<std::remove_reference_t<Tuple>>, void>
for_each_tuple(Func&&, Tuple&&) {}

template<std::size_t I = 0, typename Func, typename Tuple>
std::enable_if_t<I < std::tuple_size_v<std::remove_reference_t<Tuple>>, void>
for_each_tuple(Func&& f, Tuple&& t) {
    f(std::get<I>(t));
    for_each_tuple<I + 1>(std::forward<Func>(f), std::forward<Tuple>(t));
}

int main() {
    auto t = std::make_tuple(42, "hello", 3.14f, std::string("world"));
    
    // вывод
    for_each_tuple([](const auto& elem) {
        cout << elem << ' ';
    }, t);
    cout << endl;

    // передача по неконстантной ссылке
    auto t2 = std::make_tuple(1, 2, 3);
    for_each_tuple([](auto& elem) { elem *= 10; }, t2);
    for_each_tuple([](const auto& elem) { cout << elem << ' '; }, t2);
    cout << endl;
}