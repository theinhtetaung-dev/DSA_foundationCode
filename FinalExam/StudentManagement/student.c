#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

#define FILE_NAME "students.txt"

// --- Helper Functions ---

// Clears unwanted characters from the input buffer to prevent program skipping
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Ensures the user enters a valid whole number
int getValidInt(const char *prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clearBuffer();
            return value;
        }
        printf("Invalid input. Please enter a whole number.\n");
        clearBuffer();
    }
}

// Ensures the user enters a valid GPA between 0.0 and 4.0
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
            printf("Invalid input. Please enter a decimal number.\n");
        }
        clearBuffer();
    }
}

// Safely reads a string (including spaces) and removes the newline character
void getSafeString(const char *prompt, char *str, int size) {
    printf("%s", prompt);
    if (fgets(str, size, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }
}

// --- File Operations ---

// Reads pipe-delimited (|) data from the file into the students array
void loadFromFile(Student students[], int *count) {
    FILE *fp = fopen(FILE_NAME, "r");
    *count = 0;
    if (fp == NULL) return; // If file is missing, start with empty database

    char line[200];
    while (*count < MAX && fgets(line, sizeof(line), fp)) {
        // strtok separates the line into chunks based on "|"
        char *id_str = strtok(line, "|");
        char *name_str = strtok(NULL, "|");
        char *age_str = strtok(NULL, "|");
        char *gpa_str = strtok(NULL, "|");

        if (id_str && name_str && age_str && gpa_str) {
            students[*count].id = atoi(id_str);
            strncpy(students[*count].name, name_str, 49);
            students[*count].name[49] = '\0';
            students[*count].age = atoi(age_str);
            students[*count].gpa = atof(gpa_str);
            (*count)++;
        }
    }
    fclose(fp);
}

// Writes the current student records to the file using pipe delimiters
void saveToFile(Student students[], int count) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        // Pipes allow us to store names that have spaces inside them
        fprintf(fp, "%d|%s|%d|%.2f\n",
                students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
    fclose(fp);
}

// --- Sorting Implementations (DSA Algorithms) ---

// 1. Bubble Sort: Swaps adjacent students if they are out of order
void bubbleSort(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].id > students[j + 1].id) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// 2. Selection Sort: Finds the minimum element and moves it to the sorted part
void selectionSort(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (students[j].id < students[min_idx].id) min_idx = j;
        }
        Student temp = students[min_idx];
        students[min_idx] = students[i];
        students[i] = temp;
    }
}

// 3. Insertion Sort: Inserts each student into its correct sorted position
void insertionSort(Student students[], int count) {
    for (int i = 1; i < count; i++) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].id > key.id) {
            students[j + 1] = students[j];
            j = j - 1;
        }
        students[j + 1] = key;
    }
}

// 4. Quick Sort: Partitions the data around a pivot for faster sorting
int partition(Student students[], int low, int high) {
    int pivot = students[high].id;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (students[j].id < pivot) {
            i++;
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
        }
    }
    Student temp = students[i + 1];
    students[i + 1] = students[high];
    students[high] = temp;
    return (i + 1);
}

void quick_sort(Student students[], int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quick_sort(students, low, pi - 1);
        quick_sort(students, pi + 1, high);
    }
}

// 5. Merge Sort: Splits the data into halves and merges them back efficiently
void merge(Student students[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Student *L = (Student *)malloc(n1 * sizeof(Student));
    Student *R = (Student *)malloc(n2 * sizeof(Student));
    for (int i = 0; i < n1; i++) L[i] = students[l + i];
    for (int j = 0; j < n2; j++) R[j] = students[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].id <= R[j].id) students[k++] = L[i++];
        else students[k++] = R[j++];
    }
    while (i < n1) students[k++] = L[i++];
    while (j < n2) students[k++] = R[j++];
    free(L); free(R);
}

void merge_sort(Student students[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(students, l, m);
        merge_sort(students, m + 1, r);
        merge(students, l, m, r);
    }
}

// --- Sorting Wrapper Functions ---

void sortByID(Student students[], int count) {
    if (count <= 1) return;
    bubbleSort(students, count); // Using Bubble Sort as the primary example
    printf("Sorted by ID successfully using Bubble Sort!\n");
}

int compareByName(const void *a, const void *b) {
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

void sortByName(Student students[], int count) {
    if (count <= 1) return;
    qsort(students, count, sizeof(Student), compareByName);
    printf("Sorted by Name successfully (Alphabetical)!\n");
}

int compareByGPA(const void *a, const void *b) {
    float gpaA = ((Student *)a)->gpa;
    float gpaB = ((Student *)b)->gpa;
    if (gpaA < gpaB) return 1;
    if (gpaA > gpaB) return -1;
    return 0;
}

void sortByGPA(Student students[], int count) {
    if (count <= 1) return;
    qsort(students, count, sizeof(Student), compareByGPA);
    printf("Sorted by GPA successfully (Highest First)!\n");
}

// --- Core Operations ---

void addStudent(Student students[], int *count) {
    if (*count >= MAX) {
        printf("Database is full! Cannot add more students.\n");
        return;
    }
    int id = getValidInt("Enter ID: ");
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            printf("Error: This ID is already taken.\n");
            return;
        }
    }
    students[*count].id = id;
    getSafeString("Enter Name (spaces allowed): ", students[*count].name, 50);
    students[*count].age = getValidInt("Enter Age: ");
    students[*count].gpa = getValidFloat("Enter GPA (0.0 - 4.0): ");
    (*count)++;
    printf("Student record added successfully!\n");
}

void displayStudents(Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records found.\n");
        return;
    }
    printf("\n%-10s %-25s %-5s %-5s\n", "ID", "Name", "Age", "GPA");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10d %-25s %-5d %-5.2f\n",
               students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

void searchStudent(Student students[], int count) {
    if (count == 0) return;
    int id = getValidInt("Enter ID to search: ");
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\n--- Student Found ---\n");
            printf("Name: %s, Age: %d, GPA: %.2f\n",
                   students[i].name, students[i].age, students[i].gpa);
            return;
        }
    }
    printf("Student not found.\n");
}

void updateStudent(Student students[], int count) {
    if (count == 0) return;
    int id = getValidInt("Enter ID to update: ");
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Current Name: %s\n", students[i].name);
            getSafeString("Enter New Name: ", students[i].name, 50);
            students[i].age = getValidInt("Enter New Age: ");
            students[i].gpa = getValidFloat("Enter New GPA: ");
            printf("Update complete!\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteStudent(Student students[], int *count) {
    if (*count == 0) return;
    int id = getValidInt("Enter ID to delete: ");
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            // Shift all subsequent students to fill the gap left by deletion
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Student record deleted.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void clearStudents(Student students[], int *count) {
    char confirm = 'n';
    printf("WARNING: Are you sure you want to delete ALL data? (y/n): ");
    scanf(" %c", &confirm);
    clearBuffer();
    if (confirm == 'y' || confirm == 'Y') {
        *count = 0;
        printf("All data cleared successfully.\n");
    } else {
        printf("Cancelled.\n");
    }
}
