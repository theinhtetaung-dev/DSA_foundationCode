#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// STUDENT DATA AND BST NODE STRUCTURES
// ============================================================================

typedef struct {
    int id;
    char name[50];
    int age;
    float gpa;
} Student;

typedef struct Node {
    Student data;
    struct Node *left;
    struct Node *right;
} Node;

// ============================================================================
// BST CORE OPERATIONS IMPLEMENTATION
// ============================================================================

Node* createNode(Student s) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
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
        // Node to be deleted found
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor
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

// ============================================================================
// TRAVERSALS
// ============================================================================

void preOrder(Node* root) {
    if (root == NULL) return;
    printf("ID: %-5d | Name: %-20s | GPA: %.2f\n", root->data.id, root->data.name, root->data.gpa);
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
    printf("ID: %-5d | Name: %-20s | GPA: %.2f\n", root->data.id, root->data.name, root->data.gpa);
}

// ============================================================================
// TREE METRICS
// ============================================================================

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

// ============================================================================
// HELPER FUNCTIONS (INPUT VALIDATION)
// ============================================================================

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

// ============================================================================
// MAIN INTERFACE
// ============================================================================

int main() {
    Node* root = NULL;
    int choice;
    float gpa;
    Student s;

    printf("BST System Initialized (Single-File Mode)\n");

    do {
        printf("\n=========================================\n");
        printf("   MARK MANAGEMENT SYSTEM (BST SINGLE)\n");
        printf("=========================================\n");
        printf("1.  Add Student Record\n");
        printf("2.  Display Students (In-order - Sorted by GPA)\n");
        printf("3.  Display Students (Pre-order)\n");
        printf("4.  Display Students (Post-order)\n");
        printf("5.  Search Student by GPA\n");
        printf("6.  Find Top Student (Max GPA)\n");
        printf("7.  Find Lowest Scorer (Min GPA)\n");
        printf("8.  Show Tree Metrics (Height, Node counts)\n");
        printf("9.  Update Student Record\n");
        printf("10. Delete Student Record by GPA\n");
        printf("11. Clear All Data\n");
        printf("12. Exit\n");
        printf("-----------------------------------------\n");

        choice = getValidInt("Enter choice (1-12): ");

        switch (choice) {
            case 1:
                s.id = getValidInt("Enter ID: ");
                getSafeString("Enter Name: ", s.name, 50);
                s.age = getValidInt("Enter Age: ");
                s.gpa = getValidFloat("Enter GPA (0.0 - 4.0): ");
                root = insertNode(root, s);
                printf("Student added to binary tree.\n");
                break;
            case 2:
                printf("\n--- Students Sorted by GPA (In-order) ---\n");
                if (root == NULL) printf("Tree is empty.\n");
                else inOrder(root);
                break;
            case 3:
                printf("\n--- Pre-order Traversal ---\n");
                if (root == NULL) printf("Tree is empty.\n");
                else preOrder(root);
                break;
            case 4:
                printf("\n--- Post-order Traversal ---\n");
                if (root == NULL) printf("Tree is empty.\n");
                else postOrder(root);
                break;
            case 5:
                gpa = getValidFloat("Enter GPA to search: ");
                Node* found = searchByGPA(root, gpa);
                if (found) {
                    printf("\nFound: ID: %d, Name: %s, GPA: %.2f\n", 
                           found->data.id, found->data.name, found->data.gpa);
                } else {
                    printf("No student found with GPA %.2f.\n", gpa);
                }
                break;
            case 6: {
                Node* maxNode = findMax(root);
                if (maxNode) printf("\nTop Student: %s (GPA: %.2f)\n", 
                                    maxNode->data.name, maxNode->data.gpa);
                else printf("Tree is empty.\n");
                break;
            }
            case 7: {
                Node* minNode = findMin(root);
                if (minNode) printf("\nLowest Scorer: %s (GPA: %.2f)\n", 
                                    minNode->data.name, minNode->data.gpa);
                else printf("Tree is empty.\n");
                break;
            }
            case 8:
                printf("\n--- Tree Metrics ---\n");
                printf("Tree Height (1-based): %d\n", getHeight(root));
                printf("Total Students:       %d\n", countNodes(root));
                printf("Internal Nodes:       %d\n", countInternalNodes(root));
                printf("External Nodes (Leaves): %d\n", countExternalNodes(root));
                break;
            case 9:
                gpa = getValidFloat("Enter GPA of student to update: ");
                Node* updateNode = searchByGPA(root, gpa);
                if (updateNode) {
                    printf("Updating for %s...\n", updateNode->data.name);
                    getSafeString("Enter New Name: ", updateNode->data.name, 50);
                    updateNode->data.age = getValidInt("Enter New Age: ");
                    printf("Update successful.\n");
                } else {
                    printf("Student not found.\n");
                }
                break;
            case 10:
                gpa = getValidFloat("Enter GPA to delete: ");
                if (searchByGPA(root, gpa)) {
                    root = deleteNode(root, gpa);
                    printf("Record deleted from tree.\n");
                } else {
                    printf("Student not found.\n");
                }
                break;
            case 11: {
                char confirm = 'n';
                printf("Are you sure? (y/n): ");
                scanf(" %c", &confirm);
                clearBuffer();
                if (confirm == 'y' || confirm == 'Y') {
                    clearTree(root);
                    root = NULL;
                    printf("All data cleared.\n");
                }
                break;
            }
            case 12:
                printf("Exiting Mark Management System...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 12);

    return 0;
}
