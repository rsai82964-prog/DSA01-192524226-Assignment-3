# Q4 – Arithmetic and stream operator overloading

`Money` stores integer paise in `long long`, avoiding binary floating-point representation errors. `+` returns a new value; `+=` modifies the left operand and returns `Money&` so chained assignments work. Equality and ordering compare paise. `<<` and `>>` are non-member friends because the left operand is an `ostream`/`istream`, not a `Money` object.

`a+b` is interpreted as `a.operator+(b)` for this member overload. The stream insertion expression `cout << m` is a non-member call. Negative results are allowed and printed with a leading minus; a production billing system may instead reject negative balances at the business-rule layer.

**Expected:** `Rs 200.00`, `true`, `Rs 1.25`, `-Rs 1.00`, `Bill: Rs 200.00`. Paise carry naturally: 75+50=125 paise = Rs 1.25. Multiplying one Money by another is not meaningful; multiplication by a scalar/quantity may be defined with clear rounding rules.

All arithmetic/comparison operations are O(1) time and O(1) extra space. A `double` alternative is also O(1), but can accumulate representation error; use integer minor units for currency. Friend non-members can support symmetric forms such as `100 + m`; member overloads naturally require the left operand to be Money.
