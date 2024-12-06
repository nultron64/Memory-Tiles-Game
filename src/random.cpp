#include "random.hpp"

RandomSeq::RandomSeq(int n) : n(n)
{
    if (n) arr = new bool[n];

    for(int i=0; i<n; i++) arr[i]=false;
    remained = n;
}

int RandomSeq::next()
{
    if (remained==0) return -1;
    int choice = GetRandomValue(1, remained);
    int counted = 0;
    for(int i=0; i<n; i++) {
        if (arr[i]==false) counted++;
        if (counted==choice) {
            arr[i]=true;
            remained--;
            return i+1;
        }
    }
    return -1;
}


RandomSeq::~RandomSeq()
{
    delete[] arr;
}