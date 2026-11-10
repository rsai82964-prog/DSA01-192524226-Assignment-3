struct Sample { int first; int second; Sample() : second(2), first(second) {} };
int main() { Sample s; return s.first; }
