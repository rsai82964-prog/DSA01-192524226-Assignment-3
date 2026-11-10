#include <chrono>
#include <iostream>
struct Tiny { int x=0; Tiny& operator++(){++x;return *this;} Tiny operator++(int){Tiny old=*this;++x;return old;} };
int main(){constexpr int N=10000000; volatile int sink=0; Tiny a,b; auto s=std::chrono::steady_clock::now();for(int i=0;i<N;++i)++a;auto p=std::chrono::steady_clock::now();for(int i=0;i<N;++i)b++;auto q=std::chrono::steady_clock::now();sink=a.x+b.x;std::cout<<"prefix_us="<<std::chrono::duration_cast<std::chrono::microseconds>(p-s).count()<<" postfix_us="<<std::chrono::duration_cast<std::chrono::microseconds>(q-p).count()<<" sink="<<sink<<'\n';}
