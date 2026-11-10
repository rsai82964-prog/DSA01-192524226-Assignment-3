# Q1 – Constructors and constructor overloading

**Design:** `Book` represents one library record. Its private `title` and `copies` are established at construction; public `print()` exposes a safe view. The default constructor delegates to the two-argument constructor, and the title-only donated-book constructor delegates too. `checked()` rejects negative copies before the object can be created.

**Initializer lists:** They directly initialize members and are required for const/reference members. Members initialize in declaration order, not the written initializer-list order. `wrong_order.cpp` deliberately reverses the list to elicit `-Wreorder`/related diagnostics.

**Compiler default constructor:** A compiler-generated default constructor is available only when no user-declared constructor prevents it (and member/base requirements permit it). `no_default.cpp` intentionally fails because `Book` has only a one-argument constructor.

**Explicit:** Mark a one-argument constructor `explicit` to prevent unintended implicit conversions, e.g. `Book b = std::string("Novel")` is rejected when the title constructor is explicit.

**Alternative:** One constructor with defaults can cover the same cases, but overloads make intent clearer. Both creation and validation are O(1) time and O(1) auxiliary space. Centralizing validation in the delegated target avoids duplicated checks.

**Object states:** `empty` = (Untitled,0); `donated` = (The Alchemist,1); `full` = (C++ Primer,4).
