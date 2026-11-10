#include <string>
struct BadPrescription { int n; std::string* m; explicit BadPrescription(int x):n(x),m(new std::string[x]){} ~BadPrescription(){delete[] m;} };
int main(){ BadPrescription a(2); a.m[0]="Drug"; BadPrescription b=a; }
