#include "array_list.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct array_list {
    // array capacity.
    uint32_t capacity;
    // The number of array elements.
    uint32_t size;
    // Array element pointer.
    void **elements;
    // Element destory function.
    void (*free_func)    (void *);
};

array_list_t *array_list_new(uint32_t capacity, void (*free_func) (void *)) {
    if (capacity < 10) capacity = 10;

    array_list_t *self;

    self = (array_list_t *)malloc(sizeof(array_list_t));
    if (!self) goto error;
    memset((void *)self, 0, sizeof(array_list_t));
    self->elements = (void **)malloc(capacity * sizeof(size_t));
    if (!self->elements) goto error;

    self->capacity = capacity;
    self->free_func = free_func;
    return self;

error:
    array_list_free(self);
    return NULL;
}

uint32_t array_list_size(array_list_t *self) {
    return self->size;
}

int array_list_add(array_list_t *self, void *data) {
    if (self->size == UINT32_MAX) {
        errno = ENOMEM;
        return -1;
    }
    uint32_t size = self->size + 1;
    if (size > self->capacity) {
        // Array expansion.
        uint32_t capacity = self->capacity + self->capacity * 0.75;
        capacity = capacity < UINT32_MAX ? capacity : UINT32_MAX;
        void **elements = (void **)reallocarray(self->elements, capacity, sizeof(size_t));
        if (!elements) return -1;
        self->elements = elements;
        self->capacity = capacity;
    }
    self->elements[self->size] = data;
    self->size = size;
    return 0;
}

void *array_list_get(array_list_t *self, uint32_t index) {
    if (index < self->size) {
        return self->elements[index];
    } else {
        errno = EINVAL;
        return NULL;
    }
}

int array_list_remove(array_list_t *self, uint32_t index) {
    if (index >= self->size) {
        errno = EINVAL;
        return -1;
    }
    if(self->free_func) self->free_func(self->elements[index]);
    uint32_t last = self->size - 1;
    for (uint32_t i = index; i < last; i++) {
        self->elements[i] = self->elements[i + 1];
    }
    self->size--;
    return 0;
}

void array_list_clear(array_list_t *self) {
    if (self->free_func) {
        for (uint32_t i = 0; i < self->size; i++) {
            self->free_func(self->elements[i]);
        }
    }
    self->size = 0;
}

void array_list_free(array_list_t *self) {
    if (self->free_func) {
        // Recycle all elements.
        for (uint32_t i = 0; i < self->size; i++) {
            self->free_func(self->elements[i]);
        }
    }
    if (self->elements) free(self->elements);
    free(self);
}
