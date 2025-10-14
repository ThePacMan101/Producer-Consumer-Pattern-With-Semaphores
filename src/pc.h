#ifndef PC_H
#define PC_H

static long long int *buffer;
static int buffer_size;
static long long int number_ammount;

void init_buffer(int _buffer_size);
void destroy_buffer(void);
void set_number_ammount(long long int _number_ammount);

typedef struct {
    int id;
} t_consumer_args;
void* thread_consumer(void* void_args);

void* thread_producer(void);

#endif