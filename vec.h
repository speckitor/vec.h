#ifndef VEC_H_
#define VEC_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define VEC_INIT_SIZE 8

typedef struct {
    int64_t *data;
    size_t len;
    size_t cap;
} Vec;

Vec *vec_new(void);
void vec_free(Vec *vec);

int64_t vec_get(Vec *vec, size_t index);

void vec_append(Vec *vec, int64_t element);
void vec_insert(Vec *vec, int64_t element, size_t index);

int64_t vec_pop(Vec *vec);
int64_t vec_delete(Vec *vec, size_t index);


#ifdef VEC_IMPLEMENTATION

// Static functions

static void vec_check_realloc(Vec *vec) {
    if (vec->len >= vec->cap) {
        vec->cap *= 2;
        vec->data = realloc(vec->data, vec->cap * sizeof(*vec->data));
        assert(vec->data && "Realloc failed");
    }
}

static void vec_memmove(Vec *vec, size_t dest, size_t src, size_t bytes) {
    memmove(&vec->data[dest], &vec->data[src], bytes);
}

// Public function implementations

Vec *vec_new(void)
{
    Vec *vec = malloc(sizeof(Vec));
    assert(vec && "Malloc failed");
    vec->data = malloc(sizeof(int64_t) * VEC_INIT_SIZE);
    assert(vec->data && "Malloc failed");
    vec->len = 0;
    vec->cap = VEC_INIT_SIZE;
    return vec;
}

void vec_free(Vec *vec)
{
    free(vec->data);
    free(vec);
}

int64_t vec_get(Vec *vec, size_t index)
{
    assert(index < vec->len && "Index out of range");
    return vec->data[index];
}

void vec_append(Vec *vec, int64_t element)
{
    vec_check_realloc(vec);
    vec->data[vec->len++] = element;
}

void vec_insert(Vec *vec, int64_t element, size_t index)
{
    assert(index <= vec->len && "Index out of range");
    vec_check_realloc(vec);
    if (index < vec->len) {
        vec_memmove(vec, index + 1, index, (vec->len - index) * sizeof(*vec->data));
    }
    vec->data[index] = element;
    vec->len++;
}

int64_t vec_pop(Vec *vec)
{
    assert(vec->len > 0 && "Pop from empty vector");
    int64_t element = vec->data[--vec->len];
    return element;
}

int64_t vec_delete(Vec *vec, size_t index)
{
    assert(index < vec->len && "Index out of range");
    int64_t element = vec->data[index];
    if (vec->len - 1 > index) {
        vec_memmove(vec, index, index + 1, (vec->len - index - 1) * sizeof(*vec->data));
    }
    vec->data[--vec->len] = 0;
    return element;
}

#endif // VEC_IMPLEMENTATION


#endif // VEC_H_
