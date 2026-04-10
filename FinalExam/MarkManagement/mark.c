#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mark.h"

// --- Helper Functions ---

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidInt(const char *prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clearBuffer();
            return value;
        }
        printf("Invalid input. Enter a whole number.\n");
        clearBuffer();
    }
}

float getValidFloat(const char *prompt) {
    float value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &value) == 1) {
            if (value >= 0.0f && value <= 4.0f) {
                clearBuffer();
                return value;
            }
            printf("GPA must be between 0.0 and 4.0.\n");
        } else {
            printf("Invalid input. Enter a decimal number.\n");
        }
        clearBuffer();
    }
}

void getSafeString(const char *prompt, char *str, int size) {
    printf("%s", prompt);
    if (fgets(str, size, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }
}

// --- BST Core Operations ---

Node* createNode(Student s) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insertion based on GPA (Binary Search Tree property)
Node* insertNode(Node* root, Student s) {
    if (root == NULL) return createNode(s);

    if (s.gpa < root->data.gpa) {
        root->left = insertNode(root->left, s);
    } else {
        root->right = insertNode(root->right, s);
    }
    return root;
}

Node* searchByGPA(Node* root, float gpa) {
    if (root == NULL || root->data.gpa == gpa) return root;

    if (gpa < root->data.gpa) return searchByGPA(root->left, gpa);
    return searchByGPA(root->right, gpa);
}

Node* findMin(Node* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) root = root->left;
    return root;
}

Node* findMax(Node* root) {
    if (root == NULL) return NULL;
    while (root->right != NULL) root = root->right;
    return root;
}

Node* deleteNode(Node* root, float gpa) {
    if (root == NULL) return root;

    if (gpa < root->data.gpa) {
        root->left = deleteNode(root->left, gpa);
    } else if (gpa > root->data.gpa) {
        root->right = deleteNode(root->right, gpa);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.gpa);
    }
    return root;
}

void clearTree(Node* root) {
    if (root == NULL) return;
    clearTree(root->left);
    clearTree(root->right);
    free(root);
}

// --- Traversals ---

void preOrder(Node* root) {
    if (root == NULL) return;
    printf("ID: %d, Name: %s, GPA: %.2f\n", root->data.id, root->data.name, root->data.gpa);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("ID: %-5d | Name: %-20s | GPA: %.2f\n", root->data.id, root->data.name, root->data.gpa);
    inOrder(root->right);
}



void postOrder(Node* root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("ID: %d, Name: %s, GPA: %.2f\n", root->data.id, root->data.name, root->data.gpa);
}

// --- Tree Metrics ---

int getHeight(Node* root) {
    if (root == NULL) return 0;
    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);
    return (leftH > rightH ? leftH : rightH) + 1;
}

int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countInternalNodes(Node* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return 0;
    return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
}

int countExternalNodes(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countExternalNodes(root->left) + countExternalNodes(root->right);
}

