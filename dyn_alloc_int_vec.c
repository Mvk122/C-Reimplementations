/* 
    Vector-like struct in C that works only for ints.
    Check dyn_alloc_vec.h for an implementation that works for all datatypes.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct IntVector {
    int size;
    int capacity;
    int* elements;
} IntVector;

void init_int_vector(IntVector* vec, int initialCapacity) {
    vec->capacity = initialCapacity;
    vec->size = 0;
    vec->elements = malloc(sizeof(int) * initialCapacity);
}

void append_int_vector(IntVector* vec, int var) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        vec->elements = (int*)realloc(vec->elements, sizeof(int) * vec->capacity);
    }

    vec->elements[vec->size] = var;
    vec->size++;
}

void free_int_vector(IntVector* vec) {
    if (vec->elements != NULL) {
        free(vec->elements);
        vec->elements = NULL;
    }
    vec->size = 0;
    vec->capacity = 0;
}

void print_int_vector(IntVector* vec) {
    if (vec->size == 0) {
        return;
    }

    printf("[");
    for (int i=0; i<vec->size-1; i++) {
        printf("%d, ", vec->elements[i]);
    }
    printf("%d]", vec->elements[vec->size-1]);
}

void test_int_vector() {
    IntVector vec_a;
    init_int_vector(&vec_a, 5);

    for (int i=0; i<100; i++) {
        append_int_vector(&vec_a, i);
    }
    print_int_vector(&vec_a);
}