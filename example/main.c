#define ARRAY_H_IMPLEMENTATION_
#define SORT_H_IMPLEMENTATION_

#include "array.h"
#include "sort.h"

typedef struct {
    size_t element_a;
    size_t element_b;
    size_t element_c;
}test_struct_t;

void print_test_struct_t(test_struct_t *s){
    printf("{ a = %zu, b = %zd, c = %zu},\n", s->element_a, s->element_b, s->element_c);
}

void print_vec_test_struct_t(test_struct_t *vec, size_t size){
    printf("[");
    for (size_t i=0; i<size; i++){
        print_test_struct_t(vec+i);
    }
    printf("]\n");
}

int cmp_struct(void *a, void *b){
    size_t tmp_a = ((test_struct_t*) a)->element_b;
    size_t tmp_b = ((test_struct_t*) b)->element_b;
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

int main(){
    test_struct_t *arr = array(test_struct_t);
    test_struct_t el = {0};
    for (size_t i = 0; i < ((size_t)1 << 5); i++){
        el.element_a = i;
        el.element_b = -i;
        el.element_c = i*3;
        if(!array_push(arr,el)){
            printf("array filled up at iteration %zu\n", i);
            break;
        }
    }
    array_iter(arr, test_struct_t, el) {
        print_test_struct_t(el);
    }

    printf("%zu\n",array_capacity(arr));
    printf("%zu\n",array_size(arr));
    printf("%zu\n",sizeof(test_struct_t));

    quicksort(arr,cmp_struct);
    print_vec_test_struct_t(arr,array_size(arr));

    array_free(arr);
    return EXIT_SUCCESS;
}
