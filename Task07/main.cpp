#include <cmath>
#include <iostream>
#include <stdexcept>
#include <complex>
class Complex {
    double re,im;
public:
    Complex():re(0),im(0){}
    Complex(double r):re(r),im(0){}
    Complex(double r,double i):re(r),im(i){}
    double real()const{return re;} double imag()const{return im;}
    double magnitude()const{return std::sqrt(re*re+im*im);}
    Complex operator+(const Complex& z)const{return {re+z.re,im+z.im};}
    Complex operator-(const Complex& z)const{return {re-z.re,im-z.im};}
    Complex operator*(const Complex& z)const{return {re*z.re-im*z.im,re*z.im+im*z.re};}
    Complex operator/(const Complex& z)const{double d=z.re*z.re+z.im*z.im;if(d==0.0)throw std::domain_error("division by zero impedance");return {(re*z.re+im*z.im)/d,(im*z.re-re*z.im)/d};}
    bool operator==(const Complex& z)const{return std::abs(re-z.re)<1e-9&&std::abs(im-z.im)<1e-9;}
    friend std::ostream& operator<<(std::ostream& o,const Complex& z){o<<z.re<<(z.im<0?" - j":" + j")<<std::abs(z.im);return o;}
};
int main(){
    // Example series RLC impedance at omega=100 rad/s, R=10 ohm, L=0.1 H, C=0.001 F.
    const double w=100.0,R=10.0,L=0.1,C=0.001;
    Complex resistor(R,0),inductor(0,w*L),capacitor(0,-1.0/(w*C));
    Complex series=resistor+inductor+capacitor;
    std::cout<<"Series Z = "<<series<<" ohm; |Z|="<<series.magnitude()<<'\n';
    // Parallel example: 10 ohm resistor in parallel with j10 ohm inductor.
    Complex z1(10,0),z2(0,10); Complex parallel=(z1*z2)/(z1+z2);
    std::cout<<"Parallel Z = "<<parallel<<" ohm; |Z|="<<parallel.magnitude()<<'\n';
    std::complex<double> stdZ(10,0),stdL(0,10); auto check=(stdZ*stdL)/(stdZ+stdL);
    std::cout<<"std::complex check = "<<check.real()<<" + j"<<check.imag()<<'\n';
    try{Complex bad(1,2);std::cout<<(bad/Complex(0,0))<<'\n';}catch(const std::domain_error& e){std::cout<<"Safe error: "<<e.what()<<'\n';}
}
