#include <stdio.h>
#include "student.h"
#include "student.c"

// This is the multi-file version of the entry point.
int main() {
    Student students[MAX];
    int count = 0;
    int choice;

    // Load original data from file
    loadFromFile(students, &count);

    do {
        printf("\n===== STUDENT MANAGEMENT (Multi-File) =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student Record\n");
        printf("5. Delete Student Record\n");
        printf("6. Clear All Data\n");
        printf("7. Sort Students by ID (Bubble)\n");
        printf("8. Sort Students by Name (Alphabetical)\n");
        printf("9. Sort Students by GPA (Highest First)\n");
        printf("10. Exit\n");
        
        choice = getValidInt("Enter your choice (1-10): ");

        switch (choice) {
            case 1: 
                addStudent(students, &count); 
                saveToFile(students, count); 
                break;
            case 2: 
                displayStudents(students, count); 
                break;
            case 3: 
                searchStudent(students, count); 
                break;
            case 4: 
                updateStudent(students, count); 
                saveToFile(students, count); 
                break;
            case 5: 
                deleteStudent(students, &count); 
                saveToFile(students, count); 
                break;
            case 6: 
                clearStudents(students, &count); 
                saveToFile(students, count); 
                break;
            case 7: 
                sortByID(students, count); 
                saveToFile(students, count); 
                break;
            case 8: 
                sortByName(students, count); 
                saveToFile(students, count); 
                break;
            case 9: 
                sortByGPA(students, count); 
                saveToFile(students, count); 
                break;
            case 10: 
                printf("Exiting multi-file version...\n");
                saveToFile(students, count); 
                break;
            default: 
                printf("Invalid choice.\n");
        }
    } while (choice != 10);

    return 0;
}
