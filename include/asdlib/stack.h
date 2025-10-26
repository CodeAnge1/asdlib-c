#ifndef STACK_H
#define STACK_H

#include "asdlib/singly_linked_list.h"

typedef enum {
	STACK_OK,
	STACK_EMPTY,
	STACK_NULL_POINTER,
	STACK_MEMORY_ALLOCATION_ERROR,
	STACK_INVALID_ARGUMENT
} StackErrorCode;

StackErrorCode stackCollateError(ListErrorCode err);

typedef LinkedList Stack;

StackErrorCode stackInit(Stack* stack);
StackErrorCode stackClear(Stack* stack, void (*freeData)(BaseType));

StackErrorCode stackPush(Stack* stack, BaseType data);
StackErrorCode stackPop(Stack* stack, BaseType* data);
StackErrorCode stackPeek(Stack* stack, BaseType* data);

size_t stackSize(const Stack* stack);
bool stackIsEmpty(const Stack* stack);

#endif