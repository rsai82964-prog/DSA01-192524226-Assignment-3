#include <iostream>
#include <stdexcept>
#include <string>
class Time {
    int h,m,s;
    void normalize(){ if(s>=60){m+=s/60;s%=60;} if(m>=60){h+=m/60;m%=60;} h%=24; }
public:
    Time(int hh=0,int mm=0,int ss=0):h(hh),m(mm),s(ss){ if(h<0||m<0||s<0) throw std::invalid_argument("negative time"); normalize(); if(hh>=24) throw std::invalid_argument("hour must be below 24"); }
    Time& operator++(){ ++s; normalize(); return *this; }
    Time operator++(int){ Time old=*this; ++(*this); return old; }
    bool operator==(const Time& x)const{return h==x.h&&m==x.m&&s==x.s;}
    bool operator<(const Time& x)const{return h!=x.h?h<x.h:(m!=x.m?m<x.m:s<x.s);}
    friend std::ostream& operator<<(std::ostream& o,const Time& t){return o<<t.h<<':'<<(t.m<10?"0":"")<<t.m<<':'<<(t.s<10?"0":"")<<t.s;}
};
class Playlist {
    std::string* tracks; int n;
public:
    explicit Playlist(int count):tracks(count>0?new std::string[count]:nullptr),n(count){}
    ~Playlist(){delete[] tracks;}
    Playlist(const Playlist&)=delete; Playlist& operator=(const Playlist&)=delete;
    std::string& operator[](int i){if(i<0||i>=n)throw std::out_of_range("track index");return tracks[i];}
    const std::string& operator[](int i)const{if(i<0||i>=n)throw std::out_of_range("track index");return tracks[i];}
};
int main(){ Time t(0,0,59); Time a=t++; Time b=++t; std::cout<<a<<' '<<b<<' '<<t<<'\n'; Time end(0,59,59); ++end; std::cout<<end<<'\n'; Playlist p(2); p[0]="Track A";p[1]="Track B";const Playlist& cp=p;std::cout<<p[0]<<' '<<cp[1]<<'\n';for(int i:{-1,2})try{std::cout<<p[i]<<'\n';}catch(const std::out_of_range& e){std::cout<<"Range error: "<<e.what()<<'\n';}}
