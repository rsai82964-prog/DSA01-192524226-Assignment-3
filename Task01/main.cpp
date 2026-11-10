#include <iostream>
#include <stdexcept>
#include <string>
class Book {
    std::string title;
    int copies;
    static int checked(int n) { if (n < 0) throw std::invalid_argument("copies cannot be negative"); return n; }
public:
    Book() : Book("Untitled", 0) {}
    explicit Book(const std::string& t) : Book(t, 1) {}
    Book(const std::string& t, int n) : title(t), copies(checked(n)) {}
    void print() const { std::cout << title << " | copies=" << copies << '\n'; }
};
int main() {
    Book empty;
    Book donated("The Alchemist");
    Book full("C++ Primer", 4);
    empty.print(); donated.print(); full.print();
    try { Book invalid("Invalid", -2); invalid.print(); }
    catch (const std::invalid_argument& e) { std::cout << "Rejected: " << e.what() << '\n'; }
}
