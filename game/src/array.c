#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "array.h"



void increase_capacity_if_needed(struct array * array);



struct array array_create(size_t initial_capacity, size_t bytes)
{
    assert(initial_capacity != 0);
    assert(((initial_capacity & (initial_capacity - 1)) == 0));
    assert(bytes > 0);

    struct array array = (struct array){ 0, initial_capacity, bytes, NULL };

    return array;
}

void array_init(struct array * array)
{
    void * data = calloc(array->capacity, array->bytes);
    assert(data != NULL);

    array->data = data;
}

void array_free(struct array * array)
{
    array->count = 0;
    array->capacity = 0;
    free(array->data);
    array->data = NULL;
}

void array_reset(struct array * array, size_t initial_capacity, size_t bytes)
{
    array_free(array);
    *array = array_create(initial_capacity, bytes);
    array_init(array);
}



size_t array_get_count(struct array * array)
{
    return array->count;
}

size_t array_get_capacity(struct array * array)
{
    return array->capacity;
}

size_t array_get_bytes(struct array * array)
{
    return array->bytes;
}

void * array_get_data(struct array * array)
{
    return array->data;
}



void array_insert_at(struct array * array, void * data, size_t index)
{
    assert(index >= 0 && index <= array->count);

    increase_capacity_if_needed(array);

    memmove(
        (char *)array->data + (array->bytes * (index + 1)),
        (char *)array->data + (array->bytes * index),
        array->bytes * (array->count - index)
    );
    memcpy(
        (char *)array->data + (array->bytes * index),
        data,
        array->bytes);
    ++array->count;
}

void array_prepend(struct array * array, void * data)
{
    array_insert_at(array, data, 0);
}

void array_append(struct array * array, void * data)
{
    array_insert_at(array, data, array->count);
}



void array_remove_at(struct array * array, size_t index)
{
    assert(array->count > 0);
    assert(index >= 0 && index < array->count);

    memmove(
        (char *)array->data + (array->bytes * index),
        (char *)array->data + (array->bytes * (index + 1)),
        array->bytes * ((array->count - 1) - index)
    );
    memset(
        (char *)array->data + (array->bytes * (array->count - 1)),
        0,
        array->bytes);
    --array->count;
}

void array_remove_first(struct array * array)
{
    array_remove_at(array, 0);
}

void array_remove_last(struct array * array)
{
    array_remove_at(array, array->count - 1);
}



void * array_get(struct array * array, size_t index)
{
    assert(index >= 0 && index < array->count);

    return (char *)array->data + (array->bytes * index);
}



void array_clear(struct array * array)
{
    memset(array->data, 0, array->bytes * array->count);
    array->count = 0;
}

void array_shrink(struct array * array)
{
    if (array->capacity > 1 && array->capacity / 2 >= array->count)
    {
        while (array->capacity > 1 && array->capacity / 2 >= array->count)
        {
            array->capacity /= 2;
        }
        void * ptr = realloc(array->data, array->bytes * array->capacity);
        assert(ptr != NULL);
        array->data = ptr;
    }
}



void increase_capacity_if_needed(struct array * array)
{
    if (array->count == array->capacity)
    {
        void * ptr = realloc(array->data, array->bytes * (array->capacity * 2));
        assert(ptr != NULL);
        array->capacity *= 2;
        array->data = ptr;
        memset((char *)array->data + (array->bytes * array->count), 0, array->bytes * (array->capacity - array->count));
    }
}
