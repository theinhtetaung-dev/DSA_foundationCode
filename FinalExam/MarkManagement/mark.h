#ifndef MARK_H
#define MARK_H

// --- Student Data Structure ---
typedef struct {
    int id;
    char name[50];
    int age;
    float gpa;
} Student;

// --- BST Node Structure ---
typedef struct Node {
    Student data;
    struct Node *left;
    struct Node *right;
} Node;

// --- BST Core Operations ---
Node* insertNode(Node* root, Student s);
Node* searchByGPA(Node* root, float gpa);
Node* deleteNode(Node* root, float gpa);
Node* findMin(Node* root);
Node* findMax(Node* root);
void clearTree(Node* root);

// --- Traversals ---
void preOrder(Node* root);
void inOrder(Node* root);
void postOrder(Node* root);

// --- Tree Metrics ---
int getHeight(Node* root);
int countNodes(Node* root);
int countInternalNodes(Node* root);
int countExternalNodes(Node* root);

// --- Helper Functions ---
void clearBuffer();
int getValidInt(const char *prompt);
float getValidFloat(const char *prompt);
void getSafeString(const char *prompt, char *str, int size);

#endif
