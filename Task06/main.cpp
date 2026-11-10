#include <cstring>
#include <iostream>
class Text {
    char* data;
public:
    static int copies;
    explicit Text(const char* s=""):data(new char[std::strlen(s)+1]){std::strcpy(data,s);}
    Text(const Text& x):data(new char[std::strlen(x.data)+1]){std::strcpy(data,x.data);++copies;}
    Text& operator=(const Text& x){if(this!=&x){char* fresh=new char[std::strlen(x.data)+1];std::strcpy(fresh,x.data);delete[] data;data=fresh;}return *this;}
    ~Text(){delete[] data;}
    Text operator+(const Text& x)const{Text result;delete[] result.data;result.data=new char[std::strlen(data)+std::strlen(x.data)+1];std::strcpy(result.data,data);std::strcat(result.data,x.data);return result;}
    bool operator==(const Text& x)const{return std::strcmp(data,x.data)==0;}
    bool operator!=(const Text& x)const{return !(*this==x);}
    friend std::ostream& operator<<(std::ostream& o,const Text& x){return o<<x.data;}
};
int Text::copies=0;
int main(){Text a("Hello "),b("Metro"),c("");Text joined=a+b+c;std::cout<<joined<<'\n';std::cout<<std::boolalpha<<(joined!=a)<<' '<<(c==Text(""))<<'\n';a=a;std::cout<<a<<'\n'<<"Copy-constructor calls: "<<Text::copies<<'\n';}
