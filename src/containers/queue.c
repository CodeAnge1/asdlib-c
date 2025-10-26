#include "asdlib/queue.h"

QueueErrorCode queueCollateError(ListErrorCode err) {
	switch (err) {
		case LIST_OK:						return QUEUE_OK;
		case LIST_EMPTY:					return QUEUE_EMPTY;
		case LIST_NULL_POINTER:				return QUEUE_NULL_POINTER;
		case LIST_MEMORY_ALLOCATION_ERROR:	return QUEUE_MEMORY_ALLOCATION_ERROR;
		default:							return QUEUE_INVALID_ARGUMENT;
	}
}

QueueErrorCode queueInit(Queue* queue) {
	ListErrorCode err = listInit(queue);
	return queueCollateError(err);
}

QueueErrorCode queueClear(Queue* queue, void (*freeData)(BaseType)) {
	ListErrorCode err = listClear(queue, freeData);
	return queueCollateError(err);
}

QueueErrorCode queueEnqueue(Queue* queue, BaseType data) {
	ListErrorCode err = listPushBack(queue, data);
	return queueCollateError(err);
}

QueueErrorCode queueDequeue(Queue* queue, BaseType* data) {
	return data ? queueCollateError(listPopFront(queue, data, NULL)) : QUEUE_NULL_POINTER;
}

QueueErrorCode queuePeek(Queue* queue, BaseType* data) {
	ListErrorCode err = listPeekFront(queue, data);
	return queueCollateError(err);
}

size_t queueSize(const Queue* queue) {
	return queue ? queue->size : 0;
}

bool queueIsEmpty(const Queue* queue) {
	return queue ? (queue->size == 0) : true;
}
