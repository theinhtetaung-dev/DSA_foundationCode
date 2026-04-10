#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define FILE_NAME "students.txt"

// --- Student Structure ---
// This structure holds the record for a single student.
typedef struct {
    int id;
    char name[50];
    int age;
    float gpa;
} Student;

// --- Function Prototypes ---
// Prototypes tell the compiler about function names and parameters before they are used.
void loadFromFile(Student students[], int *count);
void saveToFile(Student students[], int count);
void addStudent(Student students[], int *count);
void displayStudents(Student students[], int count);
void searchStudent(Student students[], int count);
void updateStudent(Student students[], int count);
void deleteStudent(Student students[], int *count);
void clearStudents(Student students[], int *count);

// ID Sorting Algorithms (5 Different DSA Algorithms)
void bubbleSort(Student students[], int count);
void selectionSort(Student students[], int count);
void insertionSort(Student students[], int count);
void quick_sort(Student students[], int low, int high);
void merge_sort(Student students[], int l, int r);

// Sorting Wrappers (Easy-to-use functions for the menu)
void sortByID(Student students[], int count);
void sortByName(Student students[], int count);
void sortByGPA(Student students[], int count);

// Helper Functions (For safe input and buffer management)
void clearBuffer();
int getValidInt(const char *prompt);
float getValidFloat(const char *prompt);
void getSafeString(const char *prompt, char *str, int size);

// --- Main Function ---
// The entry point of the program. It displays the menu and handles user choices.
int main() {
    Student students[MAX]; // Array to store up to 100 students
    int count = 0;         // Current number of students in the array
    int choice;

    // Load existing data from file at program startup
    loadFromFile(students, &count);

    do {
        printf("\n=====================================\n");
        printf("   STUDENT MANAGEMENT SYSTEM\n");
        printf("=====================================\n");
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
        printf("-------------------------------------\n");
        
        choice = getValidInt("Enter your choice (1-10): ");

        switch (choice) {
            case 1:
                addStudent(students, &count);
                saveToFile(students, count); // Save immediately after adding
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                updateStudent(students, count);
                saveToFile(students, count); // Save after update
                break;
            case 5:
                deleteStudent(students, &count);
                saveToFile(students, count); // Save after deletion
                break;
            case 6:
                clearStudents(students, &count);
                saveToFile(students, count); // Save empty state
                break;
            case 7:
                sortByID(students, count);
                saveToFile(students, count); // Save sorted order
                break;
            case 8:
                sortByName(students, count);
                saveToFile(students, count); // Save sorted order
                break;
            case 9:
                sortByGPA(students, count);
                saveToFile(students, count); // Save sorted order
                break;
            case 10:
                printf("Saving data and exiting...\n");
                saveToFile(students, count);
                break;
            default:
                printf("Invalid choice! Please select 1-10.\n");
        }
    } while (choice != 10);

    return 0;
}

// --- Implementation of Helper Functions ---

// Clears the leftover characters in the input buffer to prevent input skipping
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Repeatedly asks user for input until a valid integer is entered
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

// Repeatedly asks for a valid GPA between 0.0 and 4.0
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

// Gets a string including spaces and removes the trailing newline
void getSafeString(const char *prompt, char *str, int size) {
    printf("%s", prompt);
    if (fgets(str, size, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }
}

// --- Implementation of File Operations ---

// Reads pipe-delimited (|) data from students.txt into the student array
void loadFromFile(Student students[], int *count) {
    FILE *fp = fopen(FILE_NAME, "r");
    *count = 0;
    if (fp == NULL) return; // File might not exist yet

    char line[200];
    while (*count < MAX && fgets(line, sizeof(line), fp)) {
        // strtok breaks the line into pieces using the "|" delimiter
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

// Writes the student array to students.txt using the "|" delimiter
void saveToFile(Student students[], int count) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error: Could not open file for saving.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        // Using | helps to store names that contain spaces
        fprintf(fp, "%d|%s|%d|%.2f\n",
                students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
    fclose(fp);
}

// --- Implementation of Sorting Algorithms (DSA) ---

// 1. Bubble Sort: Repeatedly swaps adjacent elements if they are in the wrong order.
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

// 2. Selection Sort: Repeatedly finds the smallest element and moves it to the front.
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

// 3. Insertion Sort: Builds the sorted array one element at a time by inserting in the correct spot.
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

// 4. Quick Sort: A Divide and Conquer algorithm using a 'pivot' element.
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

// 5. Merge Sort: Recursively divides the array into halves and merges them back in order.
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

// --- Implementation of Sorting Wrappers ---

void sortByID(Student students[], int count) {
    if (count <= 1) return;
    bubbleSort(students, count); // Bubble sort is used as the default example
    printf("Sorted by ID successfully using Bubble Sort!\n");
}

int compareByName(const void *a, const void *b) {
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

void sortByName(Student students[], int count) {
    if (count <= 1) return;
    qsort(students, count, sizeof(Student), compareByName);
    printf("Sorted by Name successfully!\n");
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
    printf("Sorted by GPA (High to Low) successfully!\n");
}

// --- Implementation of Core Operations ---

void addStudent(Student students[], int *count) {
    if (*count >= MAX) {
        printf("Database full! Cannot add more.\n");
        return;
    }
    int id = getValidInt("Enter ID: ");
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            printf("Error: A student with this ID already exists.\n");
            return;
        }
    }
    students[*count].id = id;
    getSafeString("Enter Name (spaces allowed): ", students[*count].name, 50);
    students[*count].age = getValidInt("Enter Age: ");
    students[*count].gpa = getValidFloat("Enter GPA (0.0 - 4.0): ");
    (*count)++;
    printf("Student record added!\n");
}

void displayStudents(Student students[], int count) {
    if (count == 0) {
        printf("\nNo students in the database.\n");
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
            printf("\n--- Found Student ---\n");
            printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n",
                   students[i].id, students[i].name, students[i].age, students[i].gpa);
            return;
        }
    }
    printf("No student found with ID %d.\n", id);
}

void updateStudent(Student students[], int count) {
    if (count == 0) return;
    int id = getValidInt("Enter ID to update: ");
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Updating for: %s\n", students[i].name);
            getSafeString("Enter New Name: ", students[i].name, 50);
            students[i].age = getValidInt("Enter New Age: ");
            students[i].gpa = getValidFloat("Enter New GPA: ");
            printf("Record updated successfully!\n");
            return;
        }
    }
    printf("ID not found.\n");
}

void deleteStudent(Student students[], int *count) {
    if (*count == 0) return;
    int id = getValidInt("Enter ID to delete: ");
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            // Shift remaining elements to fill the gap
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Student record deleted.\n");
            return;
        }
    }
    printf("ID not found.\n");
}

void clearStudents(Student students[], int *count) {
    char confirm = 'n';
    printf("WARNING: Are you sure you want to delete ALL data? (y/n): ");
    scanf(" %c", &confirm);
    clearBuffer();
    if (confirm == 'y' || confirm == 'Y') {
        *count = 0;
        printf("Database has been cleared.\n");
    } else {
        printf("Operation cancelled.\n");
    }
}
