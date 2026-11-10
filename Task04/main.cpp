#include <iomanip>
#include <iostream>
class Money {
    long long paise;
public:
    Money(long long rupees=0,int p=0):paise(rupees*100+p){}
    explicit Money(long long totalPaise, bool):paise(totalPaise){}
    Money operator+(const Money& rhs) const { return Money(paise+rhs.paise,true); }
    Money operator-(const Money& rhs) const { return Money(paise-rhs.paise,true); }
    Money& operator+=(const Money& rhs) { paise+=rhs.paise; return *this; }
    bool operator==(const Money& rhs) const { return paise==rhs.paise; }
    bool operator<(const Money& rhs) const { return paise<rhs.paise; }
    friend std::ostream& operator<<(std::ostream& os,const Money& m) {
        long long a=m.paise; if(a<0){os<<"-Rs ";a=-a;} else os<<"Rs ";
        return os<<a/100<<'.'<<std::setw(2)<<std::setfill('0')<<a%100<<std::setfill(' ');
    }
    friend std::istream& operator>>(std::istream& is,Money& m) { long long r; int p; if(is>>r>>p) m=Money(r,p); return is; }
};
int main(){ Money a(120,75),b(79,25); Money c=a+b; std::cout<<c<<'\n'<<std::boolalpha<<(c==Money(200))<<'\n'; std::cout<<Money(0,75)+Money(0,50)<<'\n'; std::cout<<Money(1)-Money(2)<<'\n'; Money bill; bill+=a; bill+=b; std::cout<<"Bill: "<<bill<<'\n'; }
