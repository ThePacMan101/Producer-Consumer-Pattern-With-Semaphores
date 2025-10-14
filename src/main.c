#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pc.h"
#include "error.h"

#define PRODUCERS 1
#define CONSUMERS 4

int main(int argc, char** argv){
    if(argc < 3) ERROR(BAD_ARGUMENTS,"[ERROR]: try <%s> <ammount of numbers to be evaluated> <buffer size>\n",argv[0]);
    int number_ammount  =   atoi(argv[1]);
    int buffer_size     =   atoi(argv[2]);
    init_buffer(buffer_size);


    pthread_t tid[PRODUCERS+CONSUMERS];

    int i = 0;
    for ( ; i < PRODUCERS ; ++i){
        t_producer_args *args = (t_producer_args*) malloc(sizeof(t_producer_args));
        args->id = i;
        args->number_ammount=number_ammount;
        pthread_create(&tid[i],NULL,thread_producer,(void*)args);
    }

    for ( ; i < CONSUMERS ; ++i){
        t_consumer_args *args = (t_consumer_args*) malloc(sizeof(t_consumer_args));
        args->id = i;
        pthread_create(&tid[i],NULL,thread_consumer,(void*)args);
    }


    for(int i = 0 ; i < CONSUMERS+PRODUCERS ; ++i){
        pthread_join(tid[i],NULL);
    }

    destroy_buffer();
    exit(0);
}