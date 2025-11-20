#define ARRAY_H_IMPLEMENTATION
#include "array.h"

typedef struct {
    size_t element_a;
    size_t element_b;
    size_t element_c;
    size_t element_d[256];
}test_struct_t;

int main(){
    test_struct_t *arr = array(test_struct_t);
    test_struct_t el = {0};
    for (size_t i = 0; i<1<<31; i++){
        el.element_a = i;
        el.element_b = i*2;
        el.element_c = i*3;
        if(!array_push(arr,el)){
            printf("array filled up at iteration %u\n", i);
            break;
        }
    }
    array_iter(
        arr,
        test_struct_t* el,
        {
            printf("%u %u\n", el->element_a,el->element_b);
        }
    );

    printf("%u\n",array_capacity(arr));
    printf("%u\n",array_size(arr));
    printf("%u\n",sizeof(test_struct_t));

    array_free(arr);
    printf("%u\n",arr);
}
