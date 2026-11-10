# Q2 – Copy constructors: shallow and deep copies

`Prescription` owns a dynamic array, so the compiler-generated memberwise copy would copy only the pointer. Both objects would then delete the same array: a dangling pointer/double-free risk. The Rule of Three groups destructor, copy constructor and copy assignment whenever a class manually owns a resource.

The copy constructor allocates a new array and copies each string (deep copy). Assignment first builds a new array, then releases old storage, and checks `this != &other`; this gives safe self-assignment and avoids losing the old data if allocation fails before replacement. Destructor uses `delete[]`.

**Expected main output:** `Ibuprofen ORS | Paracetamol Cetirizine | Paracetamol ORS`. Passing by value invokes a copy; passing by `const&` does not. Copy construction is used for initialization from another object, pass-by-value, and returning a value when elision does not remove the copy.

**Memory diagrams:** shallow: `p.m ──► [A,B] ◄── q.m` (shared allocation); deep: `p.m ──► [A,B]`, `q.m ──► [A,B]` (independent allocations).

Copying n medicine names is O(n) time and O(n) additional space. A shallow pointer copy is O(1) but is incorrect for unique ownership. Replacing the raw array with `std::vector<std::string>` gives Rule of Zero: generated copy operations correctly copy elements. References avoid the copy when mutation is not required.
