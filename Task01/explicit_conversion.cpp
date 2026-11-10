#include <string>
struct Book { std::string title; explicit Book(std::string t) : title(t) {} };
int main() { Book b = std::string("Novel"); return b.title.empty(); }
