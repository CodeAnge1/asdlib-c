#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>
#include <stdbool.h>

typedef void* BaseType;

typedef int (*compareFunc)(const BaseType v1, const BaseType v2);
typedef void (*freeDataFunc)(BaseType data);
typedef void (*visitFunc)(BaseType data);

typedef struct Node {
	BaseType data;
	struct Node* left;
	struct Node* right;
} Node;

typedef struct {
	Node* root;
	size_t size;
	compareFunc compare;
	freeDataFunc freeData;
} BinaryTree;

typedef enum {
	BIN_TREE_OK,
	BIN_TREE_EMPTY,
	BIN_TREE_NODE_ALLOC_ERR,
	BIN_TREE_NULL_POINTER,
	BIN_TREE_INVALID_ARGUMENT,
	BIN_TREE_NODE_NOT_FOUND,
	BIN_TREE_LEFT_NODE_EXISTS,
	BIN_TREE_RIGHT_NODE_EXISTS
} BinaryTreeError;

BinaryTreeError binaryTreeInit(BinaryTree* tree, 
							   compareFunc cmp, 
							   freeDataFunc freeData);
BinaryTreeError binaryTreeDestroy(BinaryTree* tree);

BinaryTreeError binaryTreeAddLeftChild(BinaryTree* tree, Node* parent, BaseType data);
BinaryTreeError binaryTreeAddRightChild(BinaryTree* tree, Node* parent, BaseType data);

BinaryTreeError binaryTreeRemoveLeftSubtree(BinaryTree* tree, Node* parent);
BinaryTreeError binaryTreeRemoveRightSubtree(BinaryTree* tree, Node* parent);

BinaryTreeError binaryTreeInorderTraversal(BinaryTree* tree, visitFunc visit);
BinaryTreeError binaryTreePreorderTraversal(BinaryTree* tree, visitFunc visit);
BinaryTreeError binaryTreePostorderTraversal(BinaryTree* tree, visitFunc visit);

size_t binaryTreeSize(BinaryTree* tree);

bool binaryTreeIsLeaf(Node* node);
bool binaryTreeIsEmpty(BinaryTree* tree);

#endif
