#ifndef QUEUE_H
#define QUEUE_H

#include "asdlib/singly_linked_list.h"

typedef enum {
	QUEUE_OK,
	QUEUE_EMPTY,
	QUEUE_NULL_POINTER,
	QUEUE_MEMORY_ALLOCATION_ERROR,
	QUEUE_INVALID_ARGUMENT
} QueueErrorCode;

QueueErrorCode queueCollateError(ListErrorCode err);

typedef LinkedList Queue;

QueueErrorCode queueInit(Queue* queue);
QueueErrorCode queueClear(Queue* queue, void (*freeData)(BaseType));

QueueErrorCode queueEnqueue(Queue* queue, BaseType data);
QueueErrorCode queueDequeue(Queue* queue, BaseType* data);
QueueErrorCode queuePeek(Queue* queue, BaseType* data);

size_t queueSize(const Queue* queue);
bool queueIsEmpty(const Queue* queue);

#endif