#include "pc.h"
#include "error.h"
#include "primes.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static long long int *buffer;
static int buffer_size;
static int ammount_of_numbers_in_buffer;

static sem_t empty_slot, full_slot, mutex,empty_buffer;

static bool should_end = false;

void init_buffer(int _buffer_size){
    buffer_size = _buffer_size;
    buffer = (long long int*) calloc(buffer_size,sizeof(long long int));
    if(!buffer) ERROR(BAD_MEMORY_ALLOCATION,"[ERROR]: Could\'t initialize buffer with size %d\n",buffer_size);
    ammount_of_numbers_in_buffer = 0;
    sem_init ( &mutex       , 0 ,     1       );
    sem_init ( &empty_slot  , 0 , buffer_size );
    sem_init ( &full_slot   , 0 ,     0       );
    sem_init ( &empty_buffer, 0 ,     1       );
}
void destroy_buffer(void){
    sem_destroy(&empty_slot);
    sem_destroy(&full_slot);
    free(buffer);
}

void buffer_insert(long long int number){
    static int in = 0;
    sem_wait(&empty_slot);
    sem_wait(&mutex);
    
    buffer[in] = number;
    in = (in+1) % buffer_size;
    ammount_of_numbers_in_buffer ++;

    sem_post(&mutex);
    sem_post(&full_slot);
}

long long int buffer_remove(){
    static int out = 0;
    sem_wait(&full_slot);
    sem_wait(&mutex);
    
    long long int number = buffer[out];
    buffer[out] = 0;
    out = (out+1) % buffer_size;
    ammount_of_numbers_in_buffer --;

    sem_post(&mutex);
    sem_post(&empty_slot);
    return number;
}


void* thread_consumer(void* void_args){
    long long int primes_found = 0;
    static int out = 0;

    while (true) {
        sem_wait(&full_slot);
        sem_wait(&mutex);

        if (ammount_of_numbers_in_buffer == 0 && should_end) {
            sem_post(&mutex);
            sem_post(&full_slot);
            break;
        }
        
        if (ammount_of_numbers_in_buffer == 0) {
            sem_post(&mutex);
            continue;
        }

        
        long long int number = buffer[out];
        buffer[out] = 0;
        out = (out + 1) % buffer_size;
        ammount_of_numbers_in_buffer--;

        if (ammount_of_numbers_in_buffer == 0)
            sem_post(&empty_buffer);

        sem_post(&mutex);
        sem_post(&empty_slot);

        if (is_prime(number))
            primes_found++;
    }

    long long int *result = malloc(sizeof(long long int));
    *result = primes_found;
    pthread_exit((void*) result);
}
void* thread_producer(void* void_args){
    t_producer_args* args = (t_producer_args*) void_args;
    long long int number_ammount = args->number_ammount;
    free(args);
    long long int current_number = 1;
    while(current_number <= number_ammount){
        sem_wait(&empty_buffer);
        for(int i = 0 ; i < buffer_size && current_number <= number_ammount ; ++i){
            buffer_insert(current_number);
            current_number++;
        }
    }

    sem_wait(&mutex);
    should_end = true;
    sem_post(&mutex);

    for (int i = 0; i < buffer_size; i++)
        sem_post(&full_slot);

    pthread_exit(NULL);
}