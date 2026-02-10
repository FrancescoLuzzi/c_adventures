#ifndef SORT_H_
#define SORT_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

#define vec_size(vec) (sizeof(vec)/sizeof(vec[0]))

#define quicksort(vec, cmp){\
    size_t __size = array_size(vec);\
    if (__size > 1){\
        size_t __element_size = array_element_size(vec);\
        quicksort_recursive(vec, __element_size, 0, __size*__element_size-__element_size, cmp);\
    }\
}

int cmp_int(void *a, void *b);

typedef int (*cmp_func)(void*, void*);

void quicksort_recursive(void *vec, size_t size, size_t start, size_t end, cmp_func cmp);

#ifdef SORT_H_IMPLEMENTATION_

int cmp_int(void *a, void *b){
    int tmp_a = *(int*) a;
    int tmp_b = *(int*) b;
    if (tmp_a == tmp_b){
        return 0;
    }
    else if (tmp_a > tmp_b) {
        return 1;
    }
    else {
        return -1;
    }
}

void swap(void *a, void *b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

size_t partition(void *vec, size_t size, size_t start, size_t end, cmp_func cmp){
    char pivot_value[size];
    memcpy(pivot_value, vec+end, size);
    size_t i = start;
    size_t j = end;
    while (i<j){
        while(i<j && cmp(vec + i, pivot_value) <= 0)i+=size;
        while(i<j && cmp(vec + j, pivot_value) >= 0)j-=size;
        if (i<j)swap(vec + i, vec + j, size);
    }
    swap(vec + j, vec + end, size);
    return j;
}

void quicksort_recursive(void *vec, size_t size, size_t start, size_t end, cmp_func cmp){
    if (end <= start){
        return;
    }
    size_t j = partition(vec, size, start, end, cmp);
    if(j > start){
        quicksort_recursive(vec, size, start, j - size, cmp);
    }
    if(j < end){
        quicksort_recursive(vec, size, j + size, end, cmp);
    }
}

#endif // SORT_H_IMPLEMENTATION_
#endif // SORT_H_