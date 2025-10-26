#include "asdlib/stack.h"

StackErrorCode stackCollateError(ListErrorCode err) {
	switch (err) {
		case LIST_OK:						return STACK_OK;
		case LIST_EMPTY:					return STACK_EMPTY;
		case LIST_NULL_POINTER:				return STACK_NULL_POINTER;
		case LIST_MEMORY_ALLOCATION_ERROR:	return STACK_MEMORY_ALLOCATION_ERROR;
		default:							return STACK_INVALID_ARGUMENT;
	}
}

StackErrorCode stackInit(Stack* stack) {
	ListErrorCode err = listInit(stack);
	return stackCollateError(err);
}

StackErrorCode stackClear(Stack* stack, void (*freeData)(BaseType)) {
	ListErrorCode err = listClear(stack, freeData);
	return stackCollateError(err);
}

StackErrorCode stackPush(Stack* stack, BaseType data) {
	ListErrorCode err = listPushFront(stack, data);
	return stackCollateError(err);
}

StackErrorCode stackPop(Stack* stack, BaseType* data) {
	return data ? stackCollateError(listPopFront(stack, data, NULL)) : STACK_NULL_POINTER;
}

StackErrorCode stackPeek(Stack* stack, BaseType* data) {
	ListErrorCode err = listPeekFront(stack, data);
	return stackCollateError(err);
}

size_t stackSize(const Stack* stack) {
	return stack ? stack->size : 0;
}

bool stackIsEmpty(const Stack* stack) {
	return stack ? (stack->size == 0) : true;
}
