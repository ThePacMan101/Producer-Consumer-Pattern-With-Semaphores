# Producer-Consumer-Pattern-With-Semaphores
___
This program is a college assignmnet in which I implemenet a Producer/Consumer pattern in C, using thhe pthread.h and semaphore.h libraries. There is one producer thread that produces sequentially numbers from 1 to "number ammount". Each producer threads waits untill the buffer is empty and then tries to fill it with the next numbers in the sequence until either the buffer is full or it has produced the "number ammount". There are 8 consumer threads, each concurrently removes from the buffer and checks if the number is a prime number using the following method:
```C
bool is_prime(long long int n){
    int i;
    if(n   <= 1) return false;
    if(n   == 2) return true;
    if(n%2 == 0) return false;
    for(int i = 3 ; i < sqrt(n) + 1 ; ++i)
        if(n%i == 0) return false;
    return true;
}
``` 
By the end, each consumer thread returns the ammount of prime numbers it could find, and we show the thread that found the most prime numbers, as well as the total prime numbers found.

___

To compile the program, in src:
```shell
>> make main
```
To run the program, in src:
```shell
>> bin/main <number ammount> <buffer size>
```
___
Example usage:
```shell
>> make main
    gcc -o bin/main main.c pc.c -pthread -lm
>> bin/main 1000000 20
    Thread 1 found 11232 primes
    Thread 2 found 11204 primes
    Thread 3 found 11321 primes
    Thread 4 found 11126 primes
    Thread 5 found 11088 primes
    Thread 6 found 11340 primes
    Thread 7 found 11187 primes
    --------------------------------
    Winner thread was thread 6, with 11340 primes found 
    There is a total ammount of 78498 primes
```