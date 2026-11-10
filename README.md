# DSA01-192524226-Assignment3

## Student details
- **Name:** [P Rahul Sai]
- **Register number:** [192524226]
- **Course outcome:** CO3 – Constructors, destructors and operator overloading
- **Compiler used for this preparation:** GNU g++ 14.2.0 (Linux x86_64)
- **Language standard:** C++17

## Compile and run
From the required task folder:

```bash
g++ -std=c++17 -Wall -Wextra -Wconversion -pedantic main.cpp -o program
./program
```

For AddressSanitizer tasks:

```bash
g++ -std=c++17 -g -fsanitize=address -fno-omit-frame-pointer main.cpp -o asan_program
./asan_program
```

For optimisation measurements, compile the benchmark with `-O0` and `-O2` as recorded in `Task06/benchmark_results.txt`.

## Repository layout
- `Task01/` – constructors, delegation, explicit, initialization order and diagnostics.
- `Task02/` – shallow/deep copies, Rule of Three, copy assignment and sanitizer evidence.
- `Task03/` – dynamic 2D seat map, destructor, lifetime order and leak evidence.
- `Task04/` – Money class and arithmetic/stream operator overloads.
- `Task05/` – prefix/postfix increment, comparisons and checked subscript.
- `Task06/` – dynamic Text class, Rule of Three, concatenation and benchmark.
- `Task07/` – Complex class and AC impedance calculations.
- `REPORT.md` – full question-wise report and complexity analysis.
- `UML.md` – class design sketches.

Each task folder contains source code, `NOTES.md`, compile logs and execution output. Prediction files are recorded before the corresponding prediction programs are executed. Intentionally incorrect programs are clearly named `*_bad.cpp` and are included only to demonstrate the failure mode; do not use them as final implementations.

## Task summaries
1. Constructors validate Book state and use constructor delegation.
2. Prescription performs independent deep copies and safe assignment.
3. Event manages a dynamically allocated seat map and releases it in its destructor.
4. Money stores paise and overloads arithmetic and stream operators.
5. Time and Playlist demonstrate increment, comparison and checked subscript operators.
6. Text implements manual dynamic-memory ownership and the Rule of Three.
7. Complex calculates series/parallel impedances and rejects division by zero.

## Evidence
- `compile.txt`, `output.txt`, `stderr.txt`: compiler and run evidence.
- `output_screenshot.png`: rendered terminal-output evidence for each task.
- `*_diagnostic.txt`, `*_asan.txt`, `*_asan.txt`: negative-test and sanitizer evidence where applicable.
- `prediction.txt`: pre-execution output predictions for Q3 and Q5.

## Git history
The local Git repository contains an initial documentation commit and one progressive commit for each Q1–Q7. Push the existing history with:

```bash
git remote add origin https://github.com/YOUR_USERNAME/DSA01-YOUR_REGISTER_NUMBER-Assignment3.git
git branch -M main
git push -u origin main
```

Replace the URL with the repository you create. Do not upload the hidden `.git` directory using GitHub's browser uploader; use `git push` to preserve commit history.

## Before submission
- Replace the name and register-number placeholders.
- Confirm the faculty has access to the public/private repository.
- Verify the GitHub URL in the report cover page.
- Review every output, prediction, sanitizer result and benchmark on your own computer and be prepared to explain it in the viva.
- Submit the GitHub link and assignment report through Google Classroom.
