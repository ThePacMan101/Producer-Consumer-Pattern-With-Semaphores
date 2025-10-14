#ifndef PC_H
#define PC_H

void init_buffer(int _buffer_size);
void destroy_buffer(void);


void* thread_consumer(void* void_args);

typedef struct {
    long long int number_ammount;
} t_producer_args;
void* thread_producer(void* void_args);

#endif