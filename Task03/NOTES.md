# Q3 – Dynamic constructors and destructors

`Event` allocates a row-pointer array and one seat array per row. Each cell is initially unbooked. `book` and `cancel` validate bounds and state. The destructor releases each row with `delete[]` and then the row-pointer array. The constructor handles zero dimensions and cleans partially allocated rows if allocation throws.

**Lifetime order:** automatic local objects are destroyed in reverse construction order at scope exit; block-scope objects are destroyed at the closing brace; a heap object lives until `delete`. Forgetting delete leaks memory. Using scalar `delete` for an array allocated by `new[]` is undefined behaviour; use `delete[]`. A destructor has no parameters or return type and cannot be overloaded because destruction has one fixed signature per class.

**Memory layout:** `map` points to `rows` row pointers; each row pointer points to `seats` bool cells. Approximate payload for bool cells is rows×seats bytes on common implementations, plus rows×sizeof(bool*) and allocator overhead. For 10×20, 100×200 and 1000×2000 payload estimates are 200, 20,000 and 2,000,000 bytes.

**Alternative:** one contiguous block needs one allocation and index `r*seats+s`; a row-pointer layout needs rows+1 allocations and pointer overhead. `vector<vector<bool>>` manages memory automatically but has specialization semantics; `vector<vector<char>>` is simpler. Access is O(1) either way. RAII ties resource release to object lifetime and prevents forgotten cleanup on normal scope exit.
