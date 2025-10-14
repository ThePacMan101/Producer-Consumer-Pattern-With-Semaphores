#ifndef ERROR
#define ERROR(err_code,...) {fprintf(stderr,__VA_ARGS__);exit(err_code);}
typedef enum{
    BAD_MEMORY_ALLOCATION=1,
    BAD_ARGUMENTS,
} ERR_CODE;
#endif