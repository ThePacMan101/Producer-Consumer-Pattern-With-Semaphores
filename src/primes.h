#ifndef PRIMES_H
#define PRIMES_H

#include <stdbool.h>
#include <math.h>

bool is_prime(long long int n){
    int i;
    if(n   <= 1) return false;
    if(n   == 2) return true;
    if(n%2 == 0) return false;
    for(int i = 3 ; i < sqrt(n) + 1 ; ++i)
        if(n%i == 0) return false;
    return true;
}

#endif