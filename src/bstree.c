#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"


bstree *bstree_create(char *key, int value)
{
    bstree *tree = (bstree *)malloc(sizeof(bstree));
    if (tree) {
	tree->key = key;	
	tree->value = value;
        tree->left = NULL;
        tree->right = NULL;
    }
    return tree;
}

void bstree_add(bstree *tree, char *key, int value) {
    if (!tree) {
        return;
    }

    bstree *parent = tree, *node = tree;

    while (node) {
        parent = node;
        int tmp = strcmp(key, parent->key);
        if (tmp < 0) {
            node = parent->left;
        } else if (tmp > 0) {
            node = parent->right;
        } else {
            return;
        }
    }

    bstree *newNode = bstree_create(key, value);
    int tmp = strcmp(key, parent->key);
    if (tmp < 0) {
        parent->left = newNode;
    } else if (tmp > 0) {
        parent->right = newNode;
    }
}

bstree *bstree_lookup(bstree *tree, char *key) {
    while (tree) {
        int tmp = strcmp(key, tree->key);
        if (tmp < 0) {
            return bstree_lookup(tree->left, key);
        } else if (tmp > 0) {
            tree = bstree_lookup(tree->right, key);
        } else if (tmp == 0) {
            return tree;
        }
    }
    return NULL;
}
bstree *bstree_min(bstree *tree)
{
    if (!tree)
        return NULL;

    while (tree->left)
        tree = tree->left;
    return tree;
}

bstree *bstree_max(bstree *tree)
{
    if (!tree)
        return NULL;
    while (tree->right)
        tree = tree->right;
    return tree;
}
