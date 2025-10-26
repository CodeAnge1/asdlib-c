#include <stdlib.h>
#include "asdlib/singly_linked_list.h"

ListErrorCode listInit(LinkedList* list) {
	ListErrorCode err = LIST_NULL_POINTER;
	if (list) {
		err = LIST_OK;
		list->head = NULL;
		list->size = 0;
	}
	return err;
}

ListErrorCode listFreeNode(Node** node, void (*freeData)(BaseType)) {
	ListErrorCode err = LIST_OK;
	if (!node || !*node) {
		err = LIST_NULL_POINTER;
	} else {
		if (freeData) freeData((*node)->data);
		free(*node);
		*node = NULL;
	}
	return err;
}

ListErrorCode listClear(LinkedList* list, void (*freeData)(BaseType)) {
	ListErrorCode err = list ? LIST_OK : LIST_NULL_POINTER;
	if (list) {
		Node* next;
		Node* current = list->head;
		while (current != NULL) {
			next = current->next;
			listFreeNode(&current, freeData);
			current = next;
		}
		list->head = NULL;
		list->size = 0;
	}
	return err;
}

ListErrorCode listPushFront(LinkedList* list, BaseType data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	ListErrorCode err = list ? LIST_OK : LIST_NULL_POINTER;
	err = newNode ? err : LIST_MEMORY_ALLOCATION_ERROR;
	if (err == LIST_OK) {
		newNode->data = data;
		newNode->next = list->head;
		list->head = newNode;
		if (list->size == 0) list->tail = newNode;
		++list->size;
	}
	return err;
}

ListErrorCode listPushBack(LinkedList* list, BaseType data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	ListErrorCode err = list ? LIST_OK : LIST_NULL_POINTER;
	err = newNode ? err : LIST_MEMORY_ALLOCATION_ERROR;
	if (err == LIST_OK) {
		newNode->data = data;
		newNode->next = NULL;
		if (list->size == 0) {
			list->head = newNode;
			list->tail = newNode;
		} else {
			list->tail->next = newNode;
			list->tail = newNode;
		}
		++list->size;
	}
	return err;
}

ListErrorCode listInsertAt(LinkedList* list, size_t index, BaseType data) {
	ListErrorCode err = LIST_OK;
	if (!list) {
		err = LIST_NULL_POINTER;
	} else if (index > list->size) {
		err = LIST_INDEX_OUT_OF_BOUNDS;
	} else if (index == 0) {
		err = listPushFront(list, data);
	} else if (index == list->size) {
		err = listPushBack(list, data);
	} else {
		Node* newNode = (Node*)malloc(sizeof(Node));
		err = newNode ? err : LIST_MEMORY_ALLOCATION_ERROR;
		if (newNode) {
			newNode->data = data;
			Node* current = list->head;
			for (size_t iter = 0; iter < index - 1; ++iter) {
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
			++list->size;
		}
	}
	return err;
}

ListErrorCode listPopFront(LinkedList* list, BaseType* data, void (*freeData)(BaseType)) {
	ListErrorCode err = LIST_OK;
	if (!list) {
		err = LIST_NULL_POINTER;
	} else if (list->size == 0) {
		err = LIST_EMPTY;
	} else {
		Node* current = list->head;
		list->head = current->next;
		if (list->size == 1) list->tail = NULL;
		if (data) {
			*data = current->data;
			err = listFreeNode(&current, NULL);
		} else {
			err = listFreeNode(&current, freeData);
		}
		--list->size;
	}
	return err;
}

ListErrorCode listPopBack(LinkedList* list, BaseType* data, void (*freeData)(BaseType)) {
	ListErrorCode err = LIST_OK;
	if (!list) {
		err = LIST_NULL_POINTER;
	} else if (list->size == 0) {
		err = LIST_EMPTY;
	} else {
		Node* current = list->head;
		Node* prev = NULL;
		while (current && current->next) {
			prev = current;
			current = current->next;
		}
		if (prev) prev->next = NULL;
		if (list->size == 1) list->head = NULL;
		list->tail = prev;
		if (data) {
			*data = current->data;
			err = listFreeNode(&current, NULL);
		} else {
			err = listFreeNode(&current, freeData);
		}
		--list->size;
	}
	return err;
}

ListErrorCode listPopAt(LinkedList* list, size_t index, BaseType* data, void (*freeData)(BaseType)) {
	ListErrorCode err = LIST_OK;
	if (!list) {
		err = LIST_NULL_POINTER;
	} else if (index >= list->size) {
		err = LIST_INDEX_OUT_OF_BOUNDS;
	} else if (index == 0) {
		err = listPopFront(list, data, freeData);
	} else if (index == list->size - 1) {
		err = listPopBack(list, data, freeData);
	} else {
		Node* current = list->head;
		for (size_t iter = 0; iter < index - 1; ++iter) {
			current = current->next;
		}
		Node* nextNode = current->next;
		current->next = nextNode->next;
		if (data) {
			*data = nextNode->data;
			err = listFreeNode(&nextNode, NULL);
		} else {
			err = listFreeNode(&nextNode, freeData);
		}
		--list->size;
	}
	return err;
}

// ListErrorCode listRemoveFront(LinkedList* list, void (*freeData)(BaseType)) {
//     ListErrorCode err = LIST_OK;
//     if (!list) {
//         err = LIST_NULL_POINTER;
//     } else if (list->size == 0) {
//         err = LIST_EMPTY;
//     } else {
//         Node* current = list->head;
//         list->head = current->next;
//         if (list->size == 1) list->tail = NULL;
//         err = listFreeNode(&current, freeData);
//         --list->size;
//     }
//     return err;
// }

// ListErrorCode listRemoveBack(LinkedList* list, void (*freeData)(BaseType)) {
//     ListErrorCode err = LIST_OK;
//     if (!list) {
//         err = LIST_NULL_POINTER;
//     } else if (list->size == 0) {
//         err = LIST_EMPTY;
//     } else {
//         Node* current = list->head;
//         Node* prev = NULL;
//         while (current && current->next) {
//             prev = current;
//             current = current->next;
//         }
//         if (prev) prev->next = NULL;
//         if (list->size == 1) list->head = NULL;
//         list->tail = prev;
//         err = listFreeNode(&current, freeData);
//         --list->size;
//     }
//     return err;
// }

// ListErrorCode listRemoveAt(LinkedList* list, size_t index, void (*freeData)(BaseType)) {
//     ListErrorCode err = LIST_OK;
//     if (!list) {
//         err = LIST_NULL_POINTER;
//     } else if (index >= list->size) {
//         err = LIST_INDEX_OUT_OF_BOUNDS;
//     } else if (index == 0) {
//         err = listRemoveFront(list, freeData);
//     } else if (index == list->size - 1) {
//         err = listRemoveBack(list, freeData);
//     } else {
//         Node* current = list->head;
//         for (size_t iter = 0; iter < index - 1; ++iter) {
//             current = current->next;
//         }
//         Node* nextNode = current->next;
//         current->next = nextNode->next;
//         err = listFreeNode(&nextNode, freeData);
//         --list->size;
//     }
//     return err;
// }

ListErrorCode listPeekFront(LinkedList* list, BaseType* data) {
	ListErrorCode err = LIST_OK;
	if (!list || !data) {
		err = LIST_NULL_POINTER;
	} else if (list->size == 0) {
		err = LIST_EMPTY;
	} else {
		*data = list->head->data;
	}
	return err;
}

ListErrorCode listPeekBack(LinkedList* list, BaseType* data) {
	ListErrorCode err = LIST_OK;
	if (!list || !data) {
		err = LIST_NULL_POINTER;
	} else if (list->size == 0) {
		err = LIST_EMPTY;
	} else {
		*data = list->tail->data;
	}
	return err;
}

ListErrorCode listPeekAt(LinkedList* list, size_t index, BaseType* data) {
	ListErrorCode err = LIST_OK;
	if (!list || !data) {
		err = LIST_NULL_POINTER;
	} else if (index >= list->size) {
		err = LIST_INDEX_OUT_OF_BOUNDS;
	} else if (index == 0) {
		err = listPeekFront(list, data);
	} else if (index == list->size - 1) {
		err = listPeekBack(list, data);
	} else {
		Node* current = list->head;
		for (size_t iter = 0; iter < index; ++iter) {
			current = current->next;
		}
		*data = current->data;
	}
	return err;
}

size_t listGetSize(LinkedList* list) {
	return list ? list->size : 0;
}

bool listIsEmpty(LinkedList* list) {
	return list ? (list->size == 0) : true;
}
