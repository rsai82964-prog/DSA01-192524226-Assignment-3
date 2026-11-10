# UML / Class design sketches – Assignment 3

## Q1 – Book
```text
Book
--------------------------------
- title : string
- copies : int
--------------------------------
+ Book()
+ Book(title : string)
+ Book(title : string, copies : int)
+ print() : void
- checked(copies : int) : int
```

## Q2 – Prescription
```text
Prescription
--------------------------------
- n : int
- medicines : string*
--------------------------------
+ Prescription(count : int)
+ Prescription(other : Prescription const&)
+ operator=(other : Prescription const&) : Prescription&
+ ~Prescription()
+ set(i : int, medicine : string const&) : void
+ get(i : int) : string
```

## Q3 – Event
```text
Event
--------------------------------
- rows : int
- seats : int
- map : bool**
--------------------------------
+ Event(rows : int, seats : int)
+ book(row : int, seat : int) : bool
+ cancel(row : int, seat : int) : bool
+ ~Event()
- valid(row : int, seat : int) : bool
```

## Q4 – Money
```text
Money
--------------------------------
- paise : long long
--------------------------------
+ operator+(Money const&) : Money
+ operator-(Money const&) : Money
+ operator+=(Money const&) : Money&
+ operator==(Money const&) : bool
+ operator<(Money const&) : bool
+ operator<<(ostream&, Money const&) : ostream& [friend]
+ operator>>(istream&, Money&) : istream& [friend]
```

## Q5 – Time and Playlist
```text
Time: h, m, s
+ prefix ++ : Time&
+ postfix ++(int) : Time
+ ==, <, <<

Playlist: tracks, n
+ operator[](int) : string&
+ operator[](int) const : string const&
```

## Q6 – Text
```text
Text
--------------------------------
- data : char*
- copies : int [static]
--------------------------------
+ Text(char const*)
+ Text(Text const&)
+ operator=(Text const&) : Text&
+ operator+(Text const&) : Text
+ operator==(Text const&) : bool
+ operator!=(Text const&) : bool
+ ~Text()
+ operator<<(ostream&, Text const&) : ostream& [friend]
```

## Q7 – Complex
```text
Complex
--------------------------------
- re : double
- im : double
--------------------------------
+ Complex()
+ Complex(real : double)
+ Complex(real : double, imag : double)
+ operator+, -, *, / : Complex
+ operator==(Complex const&) : bool
+ magnitude() : double
+ operator<<(ostream&, Complex const&) : ostream& [friend]
```
