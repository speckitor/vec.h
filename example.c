#define VEC_IMPLEMENTATION
#include "vec.h"

#include <stdio.h>

void print_vec(Vec *vec)
{
    for (size_t i = 0; i < vec->len; ++i) {
        printf("%lld\n", vec_get(vec, i));
    }
}

int main(void)
{
    Vec *vec = vec_new();
    vec_append(vec, 777);
    vec_append(vec, 420);
    vec_append(vec, 69);

    print_vec(vec);
    printf("\n");
    // vec = {777, 420, 69}

    vec_insert(vec, 1337, 0);
    vec_insert(vec, 52, 2);
    vec_insert(vec, 111, 5);

    print_vec(vec);
    printf("\n");
    // vec = {1337, 777, 52, 420, 69, 111}

    vec_pop(vec);
    vec_pop(vec);

    print_vec(vec);
    printf("\n");
    // vec = {1337, 777, 52, 420}

    vec_delete(vec, 0);
    vec_delete(vec, 1);
    vec_delete(vec, 1);

    print_vec(vec);
    printf("\n");
    // vec = {777}

    vec_free(vec);
}
