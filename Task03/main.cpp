#include <iostream>
#include <stdexcept>
class Event {
    int rows, seats; bool** map;
public:
    Event(int r,int s):rows(r),seats(s),map(nullptr) {
        if(r<0||s<0) throw std::invalid_argument("negative dimensions");
        if(rows==0||seats==0) return;
        map=new bool*[rows]{};
        try { for(int i=0;i<rows;++i) map[i]=new bool[seats]{}; }
        catch(...) { for(int i=0;i<rows;++i) delete[] map[i]; delete[] map; throw; }
        std::cout<<"Construct "<<rows<<'x'<<seats<<'\n';
    }
    bool book(int r,int s) { if(!valid(r,s)||map[r][s]) return false; map[r][s]=true; return true; }
    bool cancel(int r,int s) { if(!valid(r,s)||!map[r][s]) return false; map[r][s]=false; return true; }
    ~Event() { int booked=0; for(int i=0;i<rows;++i) for(int j=0;j<seats;++j) booked+=map[i][j]?1:0; if(map){for(int i=0;i<rows;++i) delete[] map[i]; delete[] map;} std::cout<<"Destroy "<<rows<<'x'<<seats<<" booked="<<booked<<'\n'; }
private: bool valid(int r,int s) const { return map && r>=0&&r<rows&&s>=0&&s<seats; }
};
int main(){
    Event local(2,3); local.book(0,1); local.book(1,2); local.cancel(0,1);
    { Event block(1,2); block.book(0,0); }
    Event* heap=new Event(2,2); heap->book(1,1); delete heap;
    Event zero(0,5);
    std::cout<<"Approx bool-map bytes for 10x20, 100x200, 1000x2000: "<<200<<", "<<20000<<", "<<2000000<<" (plus row pointers/allocator overhead)\n";
}
