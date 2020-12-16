#include <stdio.h>

#include "dump.h"

void dump(const char* file, const char* func, int line, const char* flag = "ok") {
    printf("\n\033[1;31mATTENTION\033[0m\n");
    printf("File: %s\n", file);
    printf("Function: %s\n", func);
    printf("Line: %d\n", line);
    printf("\033[1;31mFlag is:->\033[0m %s\n\n", flag);
};