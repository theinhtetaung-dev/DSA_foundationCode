#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mark.h"

// Note: We include mark.c here to compile everything together as a single unit
// for simplicity, similar to the previous project preference.
#include "mark.c"

int main() {
    Node* root = NULL;
    int choice;
    float gpa;
    Student s;

    // The system now runs entirely in memory without file persistence
    printf("System initialized (Memory-only mode)\n");

    do {
        printf("\n=========================================\n");
        printf("   MARK MANAGEMENT SYSTEM (BST BASED)\n");
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
                    // GPA stays the same as it's the BST key.
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
