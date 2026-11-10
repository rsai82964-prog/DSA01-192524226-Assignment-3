# Q6 – Text class and operator-overloading rules

`Text` owns a null-terminated character array. Constructor, copy constructor, copy assignment and destructor implement the Rule of Three. Assignment uses a fresh allocation before deleting the old buffer and guards self-assignment. `+` concatenates into a new object; `==` and `!=` compare contents; `<<` is a friend non-member because the left operand is a stream.

Operators that cannot be overloaded include `::`, `.`, `.*`, `?:` and `sizeof`. Overloading cannot change precedence, associativity or arity; at least one operand must be a user-defined type. `operator=` must be a member. A friend is useful when a non-member needs private access (e.g. stream insertion), but should not be used unnecessarily.

`a+b+c` groups left-to-right as `(a+b)+c`; intermediate strings may be copied/allocated. For lengths n1,n2,n3, a straightforward two-step concatenation copies approximately (n1+n2)+(n1+n2+n3) characters, O(n1+n2+n3) asymptotically for three strings, with a temporary allocation. `std::string` is normally preferable and follows Rule of Zero. For repeated concatenation, reserve capacity or append with `+=` to reduce allocations.
