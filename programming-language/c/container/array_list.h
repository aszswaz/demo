#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdint.h>

struct array_list;
typedef struct array_list array_list_t;

/**
 * Create an array.
 *
 * @param capacity  The initial capacity of the array. The minimum value is 10.
 * @param free_func When destroying the array memory, the function that destroys the elements. If NULL, the element is not destroyed.
 */
array_list_t *array_list_new(uint32_t capacity, void (*free_func) (void *));

/**
 * Get the array size.
 */
uint32_t array_list_size(array_list_t *self);

/**
 * Add an element.
 *
 * @return Returning 0 means the execution is successful, and returning a non-zero number means the executon fails.
 */
int array_list_add(array_list_t *self, void *data);

/**
 * Get the specified element.
 */
void *array_list_get(array_list_t *self, uint32_t index);

/**
 * Remove elements.
 *
 * @param index The starting position of the element to delete.
 */
int array_list_remove(array_list_t *self, uint32_t index);

/**
 * Clear the array.
 */
void array_list_clear(array_list_t *self);

/**
 * Destroy the array.
 */
void array_list_free(array_list_t *self);

#endif
