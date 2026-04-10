#ifndef STUDENT_H
#define STUDENT_H

// This file defines the layout of the student data and
// lists the functions available in the system.

#define MAX 100

// The structure that defines what information we store for each student.
typedef struct {
    int id;
    char name[50];
    int age;
    float gpa;
} Student;

// --- File Handling Functions ---
// These manage reading from and writing to the text file.
void loadFromFile(Student students[], int *count);
void saveToFile(Student students[], int count);

// --- Core Student Management Functions ---
// These are the main actions a user can take in the menu.
void addStudent(Student students[], int *count);
void displayStudents(Student students[], int count);
void searchStudent(Student students[], int count);
void updateStudent(Student students[], int count);
void deleteStudent(Student students[], int *count);
void clearStudents(Student students[], int *count);

// --- Sorting Wrapper Functions ---
// These make it easy to call the different sorting types from the menu.
void sortByID(Student students[], int count);
void sortByName(Student students[], int count);
void sortByGPA(Student students[], int count);

// --- Individual Algorithm Implementations ---
// These are the low-level DSA algorithms applied to the student data.
void bubbleSort(Student students[], int count);
void selectionSort(Student students[], int count);
void insertionSort(Student students[], int count);
void quick_sort(Student students[], int low, int high);
void merge_sort(Student students[], int left, int right);

// --- Helper Functions ---
// These handle technical details like input validation and buffer cleanup.
void clearBuffer();
int getValidInt(const char *prompt);
float getValidFloat(const char *prompt);
void getSafeString(const char *prompt, char *str, int size);

#endif
