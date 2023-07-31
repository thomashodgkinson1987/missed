#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

struct array
{
    size_t count;
    size_t capacity;
    size_t bytes;
    void * data;
};

struct array array_create(size_t initial_capacity, size_t bytes);
void array_init(struct array * array);
void array_free(struct array * array);
void array_reset(struct array * array, size_t initial_capacity, size_t bytes);

size_t array_get_count(struct array * array);
size_t array_get_capacity(struct array * array);
size_t array_get_bytes(struct array * array);
void * array_get_data(struct array * array);

void array_insert_at(struct array * array, void * data, size_t index);
void array_append(struct array * array, void * data);
void array_prepend(struct array * array, void * data);

void array_remove_at(struct array * array, size_t index);
void array_remove_first(struct array * array);
void array_remove_last(struct array * array);

void * array_get(struct array * array, size_t index);

void array_clear(struct array * array);
void array_shrink(struct array * array);

#endif
