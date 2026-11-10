#include <chrono>
#include <iostream>
#include <string>
int main(){const int n=100000;auto a=std::chrono::steady_clock::now();std::string s;for(int i=0;i<n;++i)s+="x";auto b=std::chrono::steady_clock::now();std::cout<<"std::string append 100000 chars: "<<std::chrono::duration_cast<std::chrono::microseconds>(b-a).count()<<" us; size="<<s.size()<<'\n';}
