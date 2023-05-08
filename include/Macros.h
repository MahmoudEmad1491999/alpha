#define FAIL_IF_NULL(ptr)\
    if(!ptr)\
{\
    fprintf(stderr,  #ptr" is NULL.\n");\
    exit(-1);\
}

#define FAIL_IF_LESS(x, y)\
    if(x < y)\
{\
    fprintf(stderr,  #x" is less than "#y".\n");\
    exit(-1);\
}

#define FAIL_IF_GREATER(x, y)\
    if(x > y)\
{\
    fprintf(stderr,  #x" is greater than "#y".\n");\
    exit(-1);\
}

#define FAIL_IF_LESS_OR_EQUAL(x, y)\
    if(x <= y)\
{\
    fprintf(stderr,  #x" is less or equal to"#y".\n");\
    exit(-1);\
}

#define FAIL_IF_GREATER_OR_EQUAL(x, y)\
    if(x >= y)\
{\
    fprintf(stderr,  #x" is greater or equal to"#y".\n");\
    exit(-1);\
}

#define FAIL_IF_ZERO(x)\
    if(!x)\
{\
    fprintf(stderr,  #x" is Zero.\n");\
    exit(-1);\
}

#define FAIL(msg)\
fprintf(stderr, msg);\
exit(-1);

