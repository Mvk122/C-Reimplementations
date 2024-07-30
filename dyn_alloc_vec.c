/* 
    Vector-like struct in C that works for structs of all sizes.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void pop_vec(Vector* vec) {
    vec->size--;
    if (vec->size <= vec->capacity/2) {
        vec->capacity /= 2;
        vec->elements = (void*)realloc(vec->elements, vec->elementSize * vec->capacity);
    }
}

void* get_vec(Vector* vec, int index) {
    if (index < 0 || index > vec->size) {
        return NULL;
    }
    // returning a pointer to the element
    return (char*)vec->elements + (index * vec->elementSize);
}

void set_vec(Vector* vec, int index, void* element) {
    if (index < 0 || index > vec->size) {
        return;
    }
    memcpy((char* )vec->elements + (index * vec->elementSize), element, vec->elementSize);
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
    printf("%d]\n", *((int* )vec->elements + vec->size-1));
}


void test_dyn_alloc_vec() {
    Vector vec_a;
    init_vec(&vec_a, 5, sizeof(int));
    
    for (int i=0; i<100; i++) {
        // Since append_vec takes a void* element, we need to pass a pointer to the element
        int to_append = i * 2;
        append_vec(&vec_a, &to_append);
    }

    // Removes the last element from the vector
    pop_vec_fast(&vec_a);

    // Setting also needs to be done via pointers
    int to_set = 33;
    set_vec(&vec_a, 10, &to_set);

    print_vec_of_ints(&vec_a);
    
    // Casting is required when getting elements from the vector
    int* indexed_element = (int*)get_vec(&vec_a, 4);
    printf("%d\n", *indexed_element);

    for (int i=0; i<75; i++) {
        pop_vec(&vec_a);
    }
    print_vec_of_ints(&vec_a);
    
    free_vec(&vec_a);
}