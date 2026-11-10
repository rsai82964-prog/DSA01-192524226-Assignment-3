# Q7 – Complex-number class for AC impedance

**Requirements:** represent real and imaginary parts; construct zero, real-only and real+imaginary values; support +, -, *, /, equality, rectangular printing and magnitude; reject division by zero. Series impedances add. Parallel impedances use `(Z1*Z2)/(Z1+Z2)`.

For `a+jb` and `c+jd`: addition `(a+c)+j(b+d)`; subtraction `(a-c)+j(b-d)`; multiplication `(ac-bd)+j(ad+bc)`; division has denominator `c²+d²` and numerator real `ac+bd`, imaginary `bc-ad`. The division operator throws `domain_error` if denominator is zero. Equality uses a tolerance because components are floating point.

**Worked example:** at ω=100 rad/s, R=10Ω, L=0.1H and C=0.001F: XL=ωL=10Ω and XC=1/(ωC)=10Ω. Series Z = 10+j(10−10)=10+j0Ω; magnitude 10Ω. For 10Ω in parallel with j10Ω, Z=(10·j10)/(10+j10)=5+j5Ω; magnitude ≈7.0711Ω. The standard `std::complex<double>` check should agree within floating-point tolerance.

Each arithmetic operation is O(1) time and O(1) space (two doubles). `std::complex<double>` offers tested standard arithmetic and is preferable in production; a custom class is useful for learning, custom validation and domain-specific formatting. Limitation: double precision and exact-zero division checks may need tolerance-aware engineering policy for noisy measurements.
