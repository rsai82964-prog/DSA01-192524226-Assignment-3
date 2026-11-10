#include <chrono>
#include <iostream>
struct Counter {
    volatile int value;
    Counter() : value(0) {}
    Counter& operator++() { value = value + 1; return *this; }
    Counter operator++(int) { Counter old; old.value = value; value = value + 1; return old; }
};
int main() {
    constexpr int N = 10000000;
    Counter prefix, postfix;
    auto a = std::chrono::steady_clock::now();
    for (int i=0;i<N;++i) ++prefix;
    auto b = std::chrono::steady_clock::now();
    for (int i=0;i<N;++i) postfix++;
    auto c = std::chrono::steady_clock::now();
    std::cout << "prefix_us=" << std::chrono::duration_cast<std::chrono::microseconds>(b-a).count()
              << " postfix_us=" << std::chrono::duration_cast<std::chrono::microseconds>(c-b).count()
              << " values=" << prefix.value << ',' << postfix.value << '\n';
}
