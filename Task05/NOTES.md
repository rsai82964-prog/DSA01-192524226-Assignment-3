# Q5 – Increment, comparison and subscript operators

Prefix `++x` increments and returns `*this` by reference. Postfix `x++` is distinguished by a dummy `int` parameter; it saves and returns the old value, so it creates a copy. For class types prefix is generally preferred when the old value is not needed.

`Time` normalizes seconds/minutes and wraps hours at 24. It overloads `==` and lexicographic `<`. `Playlist` supplies const and non-const `operator[]` overloads: a mutable playlist returns `string&`, while a const playlist returns `const string&`. Invalid negative or size-equal indices throw `std::out_of_range`.

**Prediction program:** starting at 5, `a=c++` stores 5 and increments c to 6; `b=++c` increments to 7 and stores 7. Output: `5 7 7`.

Checked access adds one comparison but remains O(1). `at()` commonly throws on invalid access; unchecked access has undefined behaviour if out of range. Prefix avoids the old-value copy; optimization may remove some costs, so benchmark under both `-O0` and `-O2` before drawing conclusions.
