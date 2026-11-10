#include <iomanip>
#include <iostream>
int main(){const int n=1000000;double d=0;long long p=0;for(int i=0;i<n;++i){d+=0.1;p+=10;}std::cout<<std::setprecision(17)<<"double rupees="<<d<<"\ninteger rupees="<<static_cast<double>(p)/100.0<<"\ndifference="<<d-static_cast<double>(p)/100.0<<'\n';}
