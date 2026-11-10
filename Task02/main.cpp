#include <chrono>
#include <iostream>
#include <string>
class Prescription {
    int n; std::string* medicines;
public:
    static int copies;
    explicit Prescription(int count) : n(count), medicines(count > 0 ? new std::string[count] : nullptr) {}
    Prescription(const Prescription& other) : n(other.n), medicines(n > 0 ? new std::string[n] : nullptr) {
        ++copies; for (int i=0;i<n;++i) medicines[i]=other.medicines[i];
    }
    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            std::string* fresh = other.n > 0 ? new std::string[other.n] : nullptr;
            for (int i=0;i<other.n;++i) fresh[i]=other.medicines[i];
            delete[] medicines; medicines=fresh; n=other.n;
        }
        return *this;
    }
    ~Prescription() { delete[] medicines; }
    void set(int i,const std::string& m) { if(i>=0&&i<n) medicines[i]=m; }
    std::string get(int i) const { return (i>=0&&i<n)?medicines[i]:""; }
    int size() const { return n; }
};
int Prescription::copies=0;
void byValue(Prescription p) { (void)p.size(); }
void byConstRef(const Prescription& p) { (void)p.size(); }
int main() {
    Prescription p(2); p.set(0,"Paracetamol"); p.set(1,"ORS");
    Prescription q=p; q.set(1,"Cetirizine");
    Prescription r(1); r=p; p.set(0,"Ibuprofen"); r=r;
    std::cout<<p.get(0)<<' '<<p.get(1)<<" | "<<q.get(0)<<' '<<q.get(1)<<" | "<<r.get(0)<<' '<<r.get(1)<<'\n';
    int before=Prescription::copies; byValue(p); int afterValue=Prescription::copies; byConstRef(p); int afterRef=Prescription::copies;
    std::cout<<"Copies: by-value="<<(afterValue-before)<<" by-const-reference="<<(afterRef-afterValue)<<'\n';
    for(int n: {10,1000,100000}) { Prescription x(n); auto t=std::chrono::steady_clock::now(); Prescription y=x; auto us=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-t).count(); std::cout<<"copy "<<n<<" items: "<<us<<" us\n"; }
}
