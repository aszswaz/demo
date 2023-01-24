#include "../array_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STAND_ERROR(expression) \
    if (expression) { \
        perror(""); \
        return; \
    }

static void add_elements() {
    array_list_t *list;
    uint32_t i;

    list = array_list_new(10, free);
    for (i = 0; i < 20; i++) {
        char *str = malloc(BUFSIZ);
        memset(str, 0, BUFSIZ);
        sprintf(str, "Hello Word%03d", i);
        STAND_ERROR(array_list_add(list, (void *)str));
    }

    uint32_t size = array_list_size(list);
    printf("array list size: %u\n", size);

    array_list_remove(list, 10);
    size = array_list_size(list);
    printf("array list size: %d\n", size);

    for (i = 0; i < size; i++) {
        char *str = (char *)array_list_get(list, i);
        STAND_ERROR(!str);
        printf("element %d: %s\n", i, str);
    }

    array_list_free(list);
}

int main() {
    add_elements();
    return EXIT_SUCCESS;
}
