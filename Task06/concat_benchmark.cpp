#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
class TinyText {
    char* p;
public:
    explicit TinyText(const char* s) : p(new char[std::strlen(s)+1]) { std::strcpy(p,s); }
    TinyText(const TinyText& x) : p(new char[std::strlen(x.p)+1]) { std::strcpy(p,x.p); }
    ~TinyText() { delete[] p; }
    TinyText operator+(const TinyText& x) const {
        char* joined=new char[std::strlen(p)+std::strlen(x.p)+1];
        std::strcpy(joined,p); std::strcat(joined,x.p);
        TinyText result(joined); delete[] joined; return result;
    }
    std::size_t size() const { return std::strlen(p); }
};
int main() {
    constexpr int N=100000; TinyText a("A"),b("B");
    auto x=std::chrono::steady_clock::now(); std::size_t total=0;
    for(int i=0;i<N;++i){TinyText c=a+b;total+=c.size();}
    auto y=std::chrono::steady_clock::now();
    std::string sa="A",sb="B"; std::size_t total2=0;
    auto z=std::chrono::steady_clock::now();
    for(int i=0;i<N;++i){std::string sc=sa+sb;total2+=sc.size();}
    auto w=std::chrono::steady_clock::now();
    std::cout<<"custom Text +: "<<std::chrono::duration_cast<std::chrono::microseconds>(y-x).count()<<" us, chars="<<total<<'\n';
    std::cout<<"std::string +: "<<std::chrono::duration_cast<std::chrono::microseconds>(w-z).count()<<" us, chars="<<total2<<'\n';
}
