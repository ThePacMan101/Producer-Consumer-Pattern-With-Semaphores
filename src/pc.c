#include "pc.h"
#include "error.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

static sem_t empty_slot, full_slot, mutex;

void init_buffer(int _buffer_size){
    buffer_size = _buffer_size;
    buffer = (int*) calloc(sizeof(int),buffer_size);
    if(!buffer) ERROR(BAD_MEMORY_ALLOCATION,"[ERROR]: Could\'t initialize buffer with size %d\n",buffer_size);
    
    sem_init ( mutex      , 0 ,     0       );
    sem_init ( empty_slot , 0 ,     0       );
    sem_init ( full_slot  , 0 , buffer_size );
}
void destroy_buffer(void){
    sem_destroy(empty_slot);
    sem_destroy(full_slot);
    free(buffer);
}
void set_number_ammount(long long int _number_amount){
    number_ammount = _number_amount;
}

void insert(long long int number, int id){
    static int in = 0;
    sem_wait(&empty_slot);
        sem_wait(&mutex);
            buffer[in] = number;
            in = (in+1) % buffer_size;
        sem_post(&mutex);
    sem_post(&empty_slot);
}

long long int remove(int id){
    static int out = 0;
    sem_wait(&full_slot);
        sem_wait(&mutex);
            long long int number = buffer[out];
            buffer[out] = 0;
            out = (out+1) % buffer_size;
        sem_post(&mutex);
    sem_post(&full_slot);
    return number;
}


void* thread_consumer(void* void_args){
    t_consumer_args* args = (t_consumer_args*) void_args;
    sem_wait(full_slot);

}
void* thread_producer(void){
    sem_wait(empty_slot);

}