#include <stdlib.h>

#include "asdlib/binary_tree.h"

static BinaryTreeNode* _createBinaryTreeNode(BaseType data) {
	BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
	if (node) {
		node->left = NULL;
		node->right = NULL;
		node->data = data;
	}
	return node;
}

static void _destroySubtree(size_t* size, BinaryTreeNode* node, freeDataFunc freeData) {
    if (node == NULL) return;
    _destroySubtree(size, node->left, freeData);
    _destroySubtree(size, node->right, freeData);
    if (freeData) freeData(node->data);
	--(*size);
    free(node);
}

static void _inorderRecursive(BinaryTreeNode* node, visitFunc visit) {
	if (node->left) _inorderRecursive(node->left, visit);
	visit(node->data);
	if (node->right) _inorderRecursive(node->right, visit);
}

static void _preorderRecursive(BinaryTreeNode* node, visitFunc visit) {
	visit(node->data);
	if (node->left) _preorderRecursive(node->left, visit);
	if (node->right) _preorderRecursive(node->right, visit);
}

static void _postorderRecursive(BinaryTreeNode* node, visitFunc visit) {
	if (node->left) _postorderRecursive(node->left, visit);
	if (node->right) _postorderRecursive(node->right, visit);
	visit(node->data);
}

BinaryTreeError binaryTreeInit(BinaryTree* tree, 
							   compareFunc cmp, 
							   freeDataFunc freeData) {
	BinaryTreeError err = BIN_TREE_OK;
	if (!tree) {
		err = BIN_TREE_NULL_POINTER;
	} else {
		tree->root = NULL;
		tree->size = 0;
		tree->compare = cmp;
		tree->freeData = freeData;
	}
	return err;
}

BinaryTreeError binaryTreeDestroy(BinaryTree* tree) {
	BinaryTreeError err = tree ? BIN_TREE_OK : BIN_TREE_NULL_POINTER;
	if (err == BIN_TREE_OK) {
        _destroySubtree(&tree->size, tree->root, tree->freeData);
        tree->root = NULL;
    }
    return err;
}

BinaryTreeError binaryTreeAddLeftChild(BinaryTree* tree, BinaryTreeNode* parent, BaseType data) {
	BinaryTreeError err = parent ? BIN_TREE_OK : BIN_TREE_NULL_POINTER;
	if (err == BIN_TREE_OK) {
		BinaryTreeNode* node = _createBinaryTreeNode(data);
		if (node) {
			if (parent->left) {
				err = BIN_TREE_LEFT_NODE_EXISTS;
			} else {
				++tree->size;
				parent->left = node;
			}
		} else {
			err = BIN_TREE_NODE_ALLOC_ERR;
		}
	}
	return err;
}

BinaryTreeError binaryTreeAddRightChild(BinaryTree* tree, BinaryTreeNode* parent, BaseType data) {
	BinaryTreeError err = parent ? BIN_TREE_OK : BIN_TREE_NULL_POINTER;
	if (err == BIN_TREE_OK) {
		BinaryTreeNode* node = _createBinaryTreeNode(data);
		if (node) {
			if (parent->right) {
				err = BIN_TREE_RIGHT_NODE_EXISTS;
			} else {
				++tree->size;
				parent->right = node;
			}
		} else {
			err = BIN_TREE_NODE_ALLOC_ERR;
		}
	}
	return err;
}

BinaryTreeError binaryTreeRemoveLeftSubtree(BinaryTree* tree, BinaryTreeNode* parent) {
	BinaryTreeError err = tree && parent ? BIN_TREE_OK : BIN_TREE_NULL_POINTER;
	if (err == BIN_TREE_OK) {
        _destroySubtree(&tree->size, parent->left, tree->freeData);
        parent->left = NULL;
    }
    return err;
}

BinaryTreeError binaryTreeRemoveRightSubtree(BinaryTree* tree, BinaryTreeNode* parent) {
	BinaryTreeError err = tree && parent ? BIN_TREE_OK : BIN_TREE_NULL_POINTER;
	if (err == BIN_TREE_OK) {
        _destroySubtree(&tree->size, parent->right, tree->freeData);
        parent->right = NULL;
    }
    return err;
}

BinaryTreeError binaryTreeInorderTraversal(BinaryTree* tree, visitFunc visit) {
	BinaryTreeError err = tree && visit ? BIN_TREE_OK : BIN_TREE_NULL_POINTER;
	if (tree && tree->root) {
		_inorderRecursive(tree->root, visit);
	}
	return err;
}

BinaryTreeError binaryTreePreorderTraversal(BinaryTree* tree, visitFunc visit) {
	BinaryTreeError err = tree && visit ? BIN_TREE_OK : BIN_TREE_NULL_POINTER;
	if (tree && tree->root) {
		_preorderRecursive(tree->root, visit);
	}
	return err;
}

BinaryTreeError binaryTreePostorderTraversal(BinaryTree* tree, visitFunc visit) {
	BinaryTreeError err = tree && visit ? BIN_TREE_OK : BIN_TREE_NULL_POINTER;
	if (tree && tree->root) {
		_postorderRecursive(tree->root, visit);
	}
	return err;
}

size_t binaryTreeSize(BinaryTree* tree) {
	return tree ? tree->size : 0;
}

bool binaryTreeIsLeaf(BinaryTreeNode* node) {
	return node ? (!node->left && !node->right) : false;
}

bool binaryTreeIsEmpty(BinaryTree* tree) {
	return tree ? tree->size == 0 : true;
}
