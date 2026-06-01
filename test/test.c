#include "stack.h"
#include <stdio.h>
#include <assert.h>

static void test_create_destroy() {
    stack_t *s = stack_create(5);
    assert(s != NULL);
    assert(stack_size(s) == 0);
    assert(stack_capacity(s) == 5);
    assert(stack_is_empty(s) == 1);
    assert(stack_is_full(s) == 0);
    stack_destroy(s);
    stack_destroy(NULL);
}

static void test_push_pop_peek() {
    stack_t *s = stack_create(2);
    assert(stack_push(NULL, 10) == STACK_ERROR_NULL);
    assert(stack_push(s, 10) == STACK_SUCCESS);
    assert(stack_push(s, 20) == STACK_SUCCESS);
    assert(stack_is_full(s) == 1);
    assert(stack_push(s, 30) == STACK_SUCCESS); 
    assert(stack_capacity(s) == 4);
    int val;
    assert(stack_peek(s, &val) == STACK_SUCCESS && val == 30);
    assert(stack_pop(s, &val) == STACK_SUCCESS && val == 30);
    assert(stack_pop(s, &val) == STACK_SUCCESS && val == 20);
    assert(stack_pop(s, &val) == STACK_SUCCESS && val == 10);
    assert(stack_is_empty(s) == 1);
    assert(stack_pop(s, &val) == STACK_ERROR_EMPTY);
    assert(stack_peek(s, &val) == STACK_ERROR_EMPTY);
    stack_destroy(s);
}

static void test_invalid_args() {
    int v;
    assert(stack_peek(NULL, &v) == STACK_ERROR_NULL);
    assert(stack_pop(NULL, &v) == STACK_ERROR_NULL);
    stack_t *s = stack_create(1);
    assert(stack_peek(s, NULL) == STACK_ERROR_NULL);
    assert(stack_pop(s, NULL) == STACK_ERROR_NULL);
    stack_destroy(s);
}

static void test_null_create() {
    stack_t *s = stack_create(0);
    assert(s == NULL);
}

int main() {
    test_create_destroy();
    test_push_pop_peek();
    test_invalid_args();
    test_null_create();
    printf("All C tests passed.\n");
    return 0;
}
