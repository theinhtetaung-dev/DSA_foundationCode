#include "btree.h"
#include <stdio.h>
#include <malloc.h>

int get_max(int a, int b) {
    return (a > b) ? a : b;
}

struct node* create_bst(struct node* root, int val) {
    if (root == NULL) {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        new_node->data = val;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if (val < root->data)
        root->left = create_bst(root->left, val);
    else if (val > root->data)
        root->right = create_bst(root->right, val);
    return root;
}

void preorderTraversal(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void inorderTraversal(struct node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void postorderTraversal(struct node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

int findHeight(struct node* root) {
    if (root == NULL)
        return 0;
    return 1 + get_max(findHeight(root->left), findHeight(root->right));
}

int nodeHeight(struct node* root, int val) {
    if (root == NULL)
        return -1;
    if (root->data == val)
        return findHeight(root);
    if (val < root->data)
        return nodeHeight(root->left, val);
    else
        return nodeHeight(root->right, val);
}

int countInternalNodes(struct node* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
}

int countExternalNodes(struct node* root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return countExternalNodes(root->left) + countExternalNodes(root->right);
}

int exists(struct node* root, int val) {
    if (root == NULL)
        return 0;
    if (root->data == val)
        return 1;
    if (val < root->data)
        return exists(root->left, val);
    else
        return exists(root->right, val);
}
