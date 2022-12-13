#ifndef STIVA_H
#define STIVA_H
#include <stdlib.h>

void throw_error(char*);

#define define_stack(type) \
\
    struct stack_##type; \
    typedef struct{ \
        int (*is_empty)(struct stack_##type stack); \
        void (*push)(struct stack_##type*, type); \
        type (*pop)(struct stack_##type*); \
        void (*dealloc)(struct stack_##type*); \
    } stack_functions_##type; \
    \
    typedef struct Node_##type{ \
        type val; \
        struct Node_##type* next; \
    }NODE_##type; \
    \
    typedef struct stack_##type{ \
        NODE_##type* head; \
        stack_functions_##type funcs; \
    }STACK_##type; \
    \
    void push_##type(struct stack_##type* stack, type elem) { \
        NODE_##type* node = (NODE_##type*)malloc(sizeof(NODE_##type)); \
        if(node == NULL) throw_error("Not enough space"); \
        \
        node -> val = elem; \
        node -> next = stack -> head; \
        stack -> head = node; \
    } \
    type pop_##type(struct stack_##type* stack) { \
        if(stack -> head == NULL) throw_error("Stack is empty"); \
        NODE_##type* aux = stack -> head; \
        type elem = aux -> val; \
        stack -> head = stack -> head -> next; \
        free(aux); \
        return elem; \
    } \
    int is_empty_##type(struct stack_##type* stack) { \
        return stack -> head == NULL; \
    } \
    void dealloc_##type(struct stack_##type* stack) { \
        while(!is_empty_##type(stack)) pop_##type(stack); \
    } \
    \
    stack_functions_##type funcs_##type = { \
        &is_empty_##type, \
        &push_##type, \
        &pop_##type, \
        &dealloc_##type \
    }; \
    STACK_##type init_##type() { \
        STACK_##type stack; \
        stack.head = NULL; \
        stack.funcs = funcs_##type; \
        return stack; \
    }


#define Stack(type) \
    STACK_##type

#define new_stack(type) \
    init_##type()

#define is_empty(collection) \
    collection.funcs.is_empty(&collection)

#define push(collection, elem) \
    collection.funcs.push(&collection, elem)

#define pop(collection) \
    collection.funcs.pop(&collection)

#define dealloc(collection) \
    collection.funcs.dealloc(&collection)

#endif /* STIVA_H */