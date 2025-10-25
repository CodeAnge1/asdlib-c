#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
	LIST_OK,
	LIST_EMPTY,
	LIST_INDEX_OUT_OF_BOUNDS,
	LIST_MEMORY_ALLOCATION_ERROR,
	LIST_NULL_POINTER,
	LIST_INVALID_ARGUMENT,
	LIST_ELEMENT_NOT_FOUND
} ListErrorCode;

typedef void* BaseType;

typedef struct Node {
	BaseType data;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
	Node* tail;
	size_t size;
} LinkedList;

ListErrorCode listInit(LinkedList* list);
ListErrorCode listFreeNode(Node** node, void (*freeData)(BaseType));
ListErrorCode listClear(LinkedList* list, void (*freeData)(BaseType));

ListErrorCode listPushFront(LinkedList* list, BaseType data);
ListErrorCode listPushBack(LinkedList* list, BaseType data);
ListErrorCode listInsertAt(LinkedList* list, size_t index, BaseType data);

ListErrorCode listPopFront(LinkedList* list, BaseType* data, void (*freeData)(BaseType));
ListErrorCode listPopBack(LinkedList* list, BaseType* data, void (*freeData)(BaseType));
ListErrorCode listPopAt(LinkedList* list, size_t index, BaseType* data, void (*freeData)(BaseType));

ListErrorCode listPeekFront(LinkedList* list, BaseType* data);
ListErrorCode listPeekBack(LinkedList* list, BaseType* data);
ListErrorCode listPeekAt(LinkedList* list, size_t index, BaseType* data);

size_t listGetSize(LinkedList* list);

bool listIsEmpty(LinkedList* list);

#endif
