#include <raylib.h>

// returns a sequence of numbers from 1..n one by one

class RandomSeq
{
    int n;
    int remained; // no. of elements are remained
    bool *arr; // whether an element is already used(returned) or not, true if used, false if not

public:
    RandomSeq(int n=0);
    int next();
    ~RandomSeq();
};