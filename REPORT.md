# Assignment 3 – CO3: Constructors, Destructors and Operator Overloading

**Student:** [Enter your full name]  
**Register number:** [Enter your register number]  
**Repository:** `DSA01-<RegisterNumber>-Assignment3`  
**Compiler:** GNU g++ 14.2.0, C++17, Linux x86_64  
**Build flags:** `-std=c++17 -Wall -Wextra -Wconversion -pedantic`

## Aim
To design, implement, analyse and evaluate C++ programs using constructors, destructors, dynamic memory management, copy control and operator overloading, following the seven questions in the supplied CO3 assignment.

## Q1 – Constructors and constructor overloading (6 marks)

### Design and implementation
`Book` stores a title and copy count privately. It provides a default constructor, title-only donated-book constructor and full parameterized constructor. The first two delegate to the full constructor, centralizing validation. The initializer list initializes members directly. `checked()` throws `invalid_argument` for a negative copy count, so invalid state is rejected.

### Constructor concepts
- The compiler supplies a default constructor only if no user-declared constructor prevents implicit default construction and all bases/members can be default-constructed.
- Initializer lists directly initialize members; assignment in the body first default-constructs then assigns.
- Members initialize in their declaration order, not initializer-list order. `wrong_order.cpp` records `-Wreorder` and uninitialized-use diagnostics.
- `explicit` prevents unintended implicit conversion through a one-argument constructor. A copy-initialization such as `Book b = std::string("Novel")` is rejected when the title constructor is explicit.

### Observed output
```text
Untitled | copies=0
The Alchemist | copies=1
C++ Primer | copies=4
Rejected: copies cannot be negative
```

`no_default.cpp` intentionally fails to compile when an array is created without a default constructor. The compiler diagnostic is saved in `Task01/no_default_diagnostic.txt`.

### Alternative and complexity
A single constructor with default arguments can represent the same three cases, but can make call intent less explicit. Both approaches create one object in O(1) time and O(1) auxiliary space. Constructor delegation checks the invariant in one place, reducing duplicated validation.

## Q2 – Copy constructors: shallow and deep copies (7 marks)

### Design and implementation
`Prescription` owns a dynamic array of medicine names. Its copy constructor allocates a distinct array and copies all elements. Copy assignment guards against self-assignment, creates and fills replacement storage, deletes the old array, updates the size and returns `*this`. The destructor uses `delete[]`.

The compiler-generated shallow copy would copy only the pointer. Two objects would then refer to the same allocation and both attempt to release it. The intentionally faulty `shallow_bad.cpp` was run under AddressSanitizer; its report is saved in `Task02/shallow_asan.txt` and identifies a heap-use-after-free/double-release path. The corrected deep-copy version ran under AddressSanitizer without a reported memory error (`Task02/asan.txt`).

### Observed output
```text
Ibuprofen ORS | Paracetamol Cetirizine | Paracetamol ORS
Copies: by-value=1 by-const-reference=0
```

Copy construction can occur during initialization from another object, pass-by-value, and returning an object where copy elision does not remove the copy. Pass-by-const-reference avoids making a copy when the function only reads the object.

### Rule of Three and diagrams
If a class manually owns a resource, destructor, copy constructor and copy assignment usually need to be considered together. Shallow diagram: two object pointers share one allocation. Deep diagram: each object points to a separate allocation containing equivalent strings. A vector-based implementation follows Rule of Zero because `std::vector` manages its own storage and generated copy operations copy elements correctly.

### Measurements and complexity
The observed copy timings on this run were recorded in `Task02/output.txt`; values vary with system load. Copying n strings takes O(n) time and O(n) extra storage. Shallow pointer copying is O(1) but unsafe for unique ownership. Self-assignment `r=r` is included in the test.

## Q3 – Dynamic constructors and destructors (7 marks)

### Design and implementation
`Event` allocates a two-dimensional seat map using a row-pointer array and one allocation per row. It supports booking and cancellation with bounds checks. The destructor counts remaining bookings and releases each row using `delete[]`, then releases the row-pointer array. Zero-row input is supported. The constructor cleans up already-created rows if a later allocation throws.

### Object lifetime and memory
Automatic objects are destroyed in reverse construction order at scope exit. Block-local objects are destroyed at the end of their block. Heap objects remain alive until `delete`. Forgetting `delete` leaks memory; using scalar `delete` on an array allocation is undefined behaviour. A destructor has no arguments/return value and cannot be overloaded.

For a row-pointer representation, `map` points to `rows` pointers, each pointing to `seats` cells. Approximate payload for bool cells is rows×seats bytes on this implementation, plus row pointers and allocator overhead. Payload estimates: 10×20 = 200 bytes; 100×200 = 20,000 bytes; 1,000×2,000 = 2,000,000 bytes.

### Prediction before execution
The manually recorded prediction for the Logger program is in `Task03/prediction.txt`. Actual output in `Task03/logger_output.txt`:
```text
+A +B -B copyAc use -Ac +P -P end -A
```
`a` is constructed first; `b` is constructed and destroyed inside the nested block; passing `a` by value creates a copy which is destroyed after `use`; the heap Logger is constructed and destroyed by `delete`; `a` is destroyed last.

### Sanitizer and alternative
The correct implementation is run under AddressSanitizer (`Task03/asan.txt`). `leak_bad.cpp` intentionally omits `delete[]`; LeakSanitizer reports a 400-byte leak (`Task03/leak_asan.txt`). A single contiguous rows×seats allocation requires one allocation and indexes with `r*seats+s`; the row-pointer design uses rows+1 allocations. Both have O(1) access, but contiguous storage improves locality and simplifies cleanup. RAII ties release to object lifetime.

## Q4 – Arithmetic and stream operator overloading (7 marks)

### Design and implementation
`Money` stores integer paise in `long long`. It overloads `+`, `-`, `+=`, `==`, `<`, `<<` and `>>`. `+` returns a new value; `+=` mutates the left object and returns `Money&`. Stream operators are non-member friends because the left operand is a stream. Currency formatting prints two paise digits. Negative amounts are supported and displayed with a leading minus; a production billing policy could reject them separately.

### Observed output
```text
Rs 200.00
true
Rs 1.25
-Rs 1.00
Bill: Rs 200.00
```
The carry test 75 paise + 50 paise = 125 paise = Rs 1.25. Multiplying Money by Money is not meaningful; multiplication by a quantity may be meaningful with a defined rounding rule.

### Alternative and complexity
Named functions such as `add(a,b)` and `equals(a,b)` have the same O(1) time and O(1) extra space. Non-member overloads can support symmetric expressions such as `100 + m`; a member overload naturally requires the left operand to be Money. Integer paise avoids binary floating-point representation error.

The million-addition experiment in `Task04/precision_output.txt` measured a double-based accumulation of 0.1 and compared it with exact integer paise. On this run the double result was `100000.00000133288`, while the integer-paise result was `100000`, a difference of about `1.33e-6` rupees. This is a measured illustration, not a universal error rate.

## Q5 – Increment, comparison and subscript operators (6 marks)

### Design and implementation
`Time` overloads prefix and postfix `++`, equality and less-than. Prefix returns `Time&` after modifying the object. Postfix is distinguished by a dummy `int`, saves the old object and returns that copy. `Playlist` provides const and non-const subscript overloads, each checking the index and throwing `out_of_range` if invalid.

### Output prediction before execution
The prediction was written in `Task05/prediction.txt` before compiling/running `prediction.cpp`:
```text
5 7 7
```
Starting at 5, postfix returns old value 5 and advances the counter to 6; prefix advances it to 7 and returns the updated value. Actual output is `5 7 7`.

### Other tests and complexity
The main program tests 59 seconds to 1 minute, 59:59 to 1:00:00, const/non-const playlist access, negative index and index equal to size. Checked subscript is O(1) with one additional comparison. Unchecked access may have undefined behaviour for invalid indices; `at()` generally throws. The 10,000,000-increment benchmark (volatile state to prevent loop elimination) measured prefix 21,629 μs versus postfix 28,951 μs at `-O0`, and prefix 3,603 μs versus postfix 15,839 μs at `-O2` on this run. These are environment-specific measurements; prefix avoids constructing/returning the old value.

## Q6 – Text class and operator-overloading rules (7 marks)

### Design and implementation
`Text` owns a dynamic null-terminated character array. Constructor, copy constructor, copy assignment and destructor implement the Rule of Three. Assignment handles self-assignment and allocates replacement storage before deleting the old buffer. `+` concatenates, `==`/`!=` compare content and `<<` prints via a friend non-member.

Operators that cannot be overloaded include `::`, `.`, `.*`, `?:` and `sizeof`. Overloading cannot change precedence, associativity or operand count; at least one operand must be a user-defined type. `operator=` must be a member. A friend is justified for stream insertion because the left operand is an `ostream`.

### Complexity and alternative
For `a+b+c`, evaluation groups as `(a+b)+c`; a simple implementation creates intermediate storage and copies characters. For lengths n1,n2,n3, the first concatenation copies about n1+n2 characters and the second about n1+n2+n3 characters. `std::string` is preferred in normal applications and follows Rule of Zero. Repeated appends can use `reserve`/`+=` to reduce allocations. The 100,000-operation concatenation benchmark is saved in `Task06/concat_benchmark.txt`: custom `Text +` measured 5,447 μs and `std::string +` measured 1,717 μs on this run. Both produced 200,000 total characters. The result illustrates the extra implementation overhead of a minimal manual class; it is not a universal performance guarantee. The separate `std::string` 100,000-character append test is also retained in `Task06/string_benchmark.txt`.

## Q7 – Complex-number class for AC impedance (10 marks)

### Requirements and design
`Complex` stores real and imaginary `double` values. It has zero, real-only and real+imaginary constructors; overloads `+`, `-`, `*`, `/`, `==` and `<<`; and provides magnitude. Division by zero impedance throws `domain_error`.

For `(a+jb)` and `(c+jd)`: addition = `(a+c)+j(b+d)`; subtraction = `(a-c)+j(b-d)`; multiplication = `(ac-bd)+j(ad+bc)`; division denominator = `c²+d²`, real numerator = `ac+bd`, imaginary numerator = `bc-ad`.

### Worked verification
At ω=100 rad/s, R=10Ω, L=0.1H and C=0.001F: XL=ωL=10Ω and XC=1/(ωC)=10Ω. The series result is `10+j0 Ω`, magnitude 10Ω. For 10Ω in parallel with j10Ω, the result is `5+j5 Ω`, magnitude approximately 7.07107Ω. The program compares the parallel result with `std::complex<double>` and catches division by zero safely.

### Alternative and limitation
Both custom Complex and `std::complex<double>` use two doubles and perform each arithmetic operation in O(1) time and O(1) space. The standard class is well-tested and is preferable for production; a custom class provides domain-specific validation and formatting. One limitation is floating-point precision: equality uses a tolerance and real engineering measurements may need a tolerance chosen from measurement accuracy.

## Overall conclusion
The seven programs demonstrate constructor validation, copy ownership, RAII, integer-based money representation, safe operator interfaces, and complex arithmetic. Raw dynamic memory requires explicit copy/destruction discipline; standard containers and `std::string` reduce ownership risks. Operator overloads improve readability only when their meaning matches the operator's conventional meaning. All primary task programs were compiled and executed with g++ 14.2.0 using C++17 and warning flags. Sanitizer, compiler-diagnostic, prediction and benchmark evidence is retained in the task folders.

**Submission reminder:** replace the student placeholders, publish the repository while preserving Git history, add the real GitHub URL to the report cover page, and submit the report plus repository link through Google Classroom. Review all evidence and be prepared to explain it in the viva.
