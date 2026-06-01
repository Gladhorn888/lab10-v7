#include "stack.h"
#include <stdlib.h>

struct stack_t {
    int *data;
    size_t size;
    size_t capacity;
};

stack_t *stack_create(size_t capacity) {
    stack_t *s = NULL;
    stack_error_t err = STACK_SUCCESS;

    if (capacity == 0) {
        err = STACK_ERROR_INVALID_CAP;
    }

    if (err == STACK_SUCCESS) {
        s = malloc(sizeof(stack_t));
        if (!s) err = STACK_ERROR_MEMORY;
    }

    if (err == STACK_SUCCESS) {
        s->data = malloc(capacity * sizeof(int));
        if (!s->data) {
            err = STACK_ERROR_MEMORY;
            free(s);
            s = NULL;
        }
    }

    if (err == STACK_SUCCESS) {
        s->size = 0;
        s->capacity = capacity;
    }

    return s;
}

void stack_destroy(stack_t *s) {
    if (s) {
        free(s->data);
        free(s);
    }
}

static stack_error_t stack_resize(stack_t *s) {
    size_t new_cap = s->capacity * 2;
    int *tmp = realloc(s->data, new_cap * sizeof(int));
    stack_error_t err = STACK_SUCCESS;

    if (!tmp) {
        err = STACK_ERROR_MEMORY;
    } else {
        s->data = tmp;
        s->capacity = new_cap;
    }

    return err;
}

stack_error_t stack_push(stack_t *s, int value) {
    stack_error_t err = STACK_SUCCESS;

    if (!s) {
        err = STACK_ERROR_NULL;
    }

    if (err == STACK_SUCCESS && s->size == s->capacity) {
        err = stack_resize(s);
    }

    if (err == STACK_SUCCESS) {
        s->data[s->size] = value;
        s->size++;
    }

    return err;
}

stack_error_t stack_pop(stack_t *s, int *value) {
    stack_error_t err = STACK_SUCCESS;

    if (!s || !value) {
        err = STACK_ERROR_NULL;
    }

    if (err == STACK_SUCCESS && s->size == 0) {
        err = STACK_ERROR_EMPTY;
    }

    if (err == STACK_SUCCESS) {
        s->size--;
        *value = s->data[s->size];
    }

    return err;
}

stack_error_t stack_peek(const stack_t *s, int *value) {
    stack_error_t err = STACK_SUCCESS;

    if (!s || !value) {
        err = STACK_ERROR_NULL;
    }

    if (err == STACK_SUCCESS && s->size == 0) {
        err = STACK_ERROR_EMPTY;
    }

    if (err == STACK_SUCCESS) {
        *value = s->data[s->size - 1];
    }

    return err;
}

int stack_is_empty(const stack_t *s) {
    int result = -1;
    if (s) {
        result = (s->size == 0) ? 1 : 0;
    }
    return result;
}

int stack_is_full(const stack_t *s) {
    int result = -1;
    if (s) {
        result = (s->size == s->capacity) ? 1 : 0;
    }
    return result;
}

size_t stack_size(const stack_t *s) {
    size_t sz = (size_t)-1;
    if (s) {
        sz = s->size;
    }
    return sz;
}

size_t stack_capacity(const stack_t *s) {
    size_t cap = (size_t)-1;
    if (s) {
        cap = s->capacity;
    }
    return cap;
}
