#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pc.h"
#include "error.h"

#define PRODUCERS 1
#define CONSUMERS 8

int main(int argc, char** argv){
    if(argc < 3) ERROR(BAD_ARGUMENTS,"[ERROR]: try <%s> <number ammount> <buffer size>\n",argv[0]);
    int number_ammount  =   atoi(argv[1]);
    int buffer_size     =   atoi(argv[2]);
    init_buffer(buffer_size);


    pthread_t tid[PRODUCERS+CONSUMERS];
    int i = 0;
    for ( ; i < PRODUCERS ; ++i){
        t_producer_args *args = (t_producer_args*) malloc(sizeof(t_producer_args));
        if (!args) ERROR(BAD_MEMORY_ALLOCATION,"[ERROR]: Couldn\'t allocate memory for arguments in producer thread %d\n",i);
        args->number_ammount=number_ammount;
        pthread_create(&tid[i],NULL,thread_producer,(void*)args);
    }
    for ( ; i < CONSUMERS ; ++i){
        pthread_create(&tid[i],NULL,thread_consumer,NULL);
    }

    i = 0;
    for( ; i < PRODUCERS ; ++i){
        pthread_join(tid[i],NULL);
    }
    int winner_thread = 0;
    long long int total_ammount_of_primes = 0;
    long long int greatest_ammount_of_primes = 0;
    long long int * current_ammount_of_primes = NULL;

    for( ; i < CONSUMERS ; ++i){
        pthread_join(tid[i],(void**)&current_ammount_of_primes);
        printf("Thread %d found %lld primes\n",i,*current_ammount_of_primes);
        total_ammount_of_primes += *current_ammount_of_primes;
        if(*current_ammount_of_primes > greatest_ammount_of_primes){
            greatest_ammount_of_primes = *current_ammount_of_primes;
            winner_thread = i;
        }
        free(current_ammount_of_primes);
    }
    printf("--------------------------------\n");
    printf("Winner thread was thread %d, with %lld primes found\nThere is a total ammount of %d primes\n",winner_thread,greatest_ammount_of_primes,total_ammount_of_primes);

    destroy_buffer();
    exit(0);
}