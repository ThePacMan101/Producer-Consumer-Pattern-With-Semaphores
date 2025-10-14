#ifndef PC_H
#define PC_H

static long long int *buffer;
static int buffer_size;

void init_buffer(int _buffer_size);
void destroy_buffer(void);

typedef struct {
    int id;
} t_consumer_args;
void* thread_consumer(void* void_args);

typedef struct {
    long long int number_ammount;
    int id;
} t_producer_args;
void* thread_producer(void* void_args);

#endif