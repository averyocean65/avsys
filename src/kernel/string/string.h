#ifndef H_STRING
#define H_STRING

#include <stddef.h>

size_t strlen(const char* str) {
    size_t count = 0;
    while(str[count] != '\0') {
        count++;
    }

    return count;
}

#endif