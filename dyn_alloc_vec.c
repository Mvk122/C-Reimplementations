/* 
    Vector-like struct in C that works for structs of all sizes.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Vector {
    int size;
    int capacity;
    size_t elementSize;
    void* elements;
} Vector;



void init_vec(Vector* vec, int initialCapacity, size_t elementSize) {
    vec->capacity = initialCapacity;
    vec->size = 0;
    vec->elementSize = elementSize;
    vec->elements = malloc(initialCapacity * elementSize);
}

void append_vec(Vector* vec, void* element) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        vec->elements = (void*)realloc(vec->elements, vec->elementSize * vec->capacity);
    }
    // casting to a char* allows for pointer arithmetic on a void* pointer
    memcpy((char* )vec->elements + (vec->size * vec->elementSize), element, vec->elementSize);
    
    vec->size++;
}

// Don't bother with resizing to maximise speed
void pop_vec_fast(Vector* vec) {
    vec->size--;
}

void* get_vec(Vector* vec, int index) {

}


void free_vec(Vector* vec) {
    if (vec->elements != NULL) {
        free(vec->elements);
        vec->elements = NULL;
    }
    vec->size = 0;
    vec->capacity = 0;
}

void print_vec_of_ints(Vector* vec) {
    if (vec->size == 0) {
        return;
    }

    printf("[");
    for (int i=0; i<vec->size-1; i++) {
        printf("%d, ", *((int* )vec->elements + i));
    }
    printf("%d]", *((int* )vec->elements + vec->size-1));
}


void test_dyn_alloc_vec() {
    Vector vec_a;
    init_vec(&vec_a, 5, sizeof(int));
    
    for (int i=0; i<100; i++) {
        // Since append_vec takes a void* element, we need to pass a pointer to the element
        append_vec(&vec_a, &i);
    }

    print_vec_of_ints(&vec_a);

    free_vec(&vec_a);
}