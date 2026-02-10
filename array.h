#ifndef ARRAY_H_
#define ARRAY_H_

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdint.h"
#include "assert.h"

#ifndef MIN_ARRAY_DIM
    #define MIN_ARRAY_DIM 2
#endif

#ifndef MAX_ARRAY_SIZE
    #define MAX_ARRAY_SIZE (1U << 15)
#endif

typedef struct {
    size_t element_size;
    size_t size;
    size_t capacity;
}array_header_t;


static const size_t array_header_size = sizeof(array_header_t);
static const size_t array_max_cap = MAX_ARRAY_SIZE - array_header_size - 1;
static const size_t array_half_max_cap = (MAX_ARRAY_SIZE >> 1 ) - array_header_size - 1;

array_header_t* array_header(const void* array);

size_t array_size(void* array);

size_t array_element_size(void* array);

size_t array_capacity(void* array);

size_t array_increase_len(void* array);

size_t array_decrease_len(void* array);

// TODO: could it be usefullt to have an enum to represent
// EXPANSION_OK, EXPANSION_KO, EXPANSION_NOT_NEEDED?
bool array_expand(void** array);

void* array_init(size_t element_size, size_t min_elements);


#define array(T) (T*)array_init(sizeof(T), MIN_ARRAY_DIM)
#define array_free(arr) free(array_header(arr)), arr = NULL
#define array_push(arr, element) (array_expand((void**)&arr) ? arr[array_increase_len(arr)] = element , true : false)
#define array_pop_back(arr) arr[array_decrease_len(arr)]
#define array_get_ref_at(arr,i) i<array_size(arr) ? &arr[i] : NULL
#define array_iter(arr,var_def,body) for(size_t i = 0; i<array_size(arr); i++){\
    var_def = array_get_ref_at(arr,i);\
    body\
}

#ifdef ARRAY_H_IMPLEMENTATION_

array_header_t* array_header(const void* array){
    return (array_header_t *)(array)-1;
}

size_t array_size(void* array){
    array_header_t* header = array_header(array);
    return header->size;
}

size_t array_element_size(void* array){
    array_header_t* header = array_header(array);
    return header->element_size;
}

size_t array_capacity(void* array){
    array_header_t* header = array_header(array);
    return header->capacity;
}

size_t array_increase_len(void* array){
    array_header_t* header = array_header(array);
    return (header->size)++;
}

size_t array_decrease_len(void* array){
    array_header_t* header = array_header(array);
    return --(header->size);
}

bool array_expand(void** array){
    array_header_t* old_header = array_header(*array);
    if(old_header->size < old_header->capacity){
        return true;
    }
    size_t old_array_allocation_size = old_header->element_size * old_header->capacity;
    size_t new_array_capacity = old_header->capacity;
    size_t new_array_allocation_size = 0;
    if (old_array_allocation_size >= array_half_max_cap){
        new_array_capacity = (array_max_cap / old_header->element_size);
        new_array_allocation_size = old_header->element_size * new_array_capacity;
    }else{
        new_array_capacity = new_array_capacity * 2;
        new_array_allocation_size = old_array_allocation_size * 2;
    }
    new_array_allocation_size += array_header_size;
    old_array_allocation_size += array_header_size;

    // could't expand array, max array size reached
    if(old_array_allocation_size == new_array_allocation_size){
        return false;
    }
    array_header_t* new_header =(array_header_t*) realloc(old_header,new_array_allocation_size);
    if (new_header == NULL){
        return false;
    }else{
        new_header->capacity = new_array_capacity;
        *array = (new_header + 1);
        return true;
    }
}

void* array_init(size_t element_size, size_t min_elements){
    size_t memory_to_alloc = element_size * min_elements;
    assert(memory_to_alloc <= array_max_cap);
    memory_to_alloc += array_header_size;
    array_header_t *header =(array_header_t*) malloc(memory_to_alloc);
    memset(header, 0, memory_to_alloc);
    header->element_size = element_size;
    header->size = 0;
    header->capacity = min_elements;
    return header + 1;
}

#endif // ARRAY_H_IMPLEMENTATION_

#endif // ARRAY_H_
