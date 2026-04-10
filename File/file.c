#include <stdio.h>
#include <stdlib.h>

void writeFile() {
    FILE *fp = fopen("t.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    char str[100];
    printf("Enter text to write: ");
    getchar(); // consume newline from menu selection
    fgets(str, sizeof(str), stdin);
    fprintf(fp, "%s", str);
    fclose(fp);
    printf("File written successfully.\n");
}

void readFile() {
    FILE *fp = fopen("t.txt", "r");
    if (fp == NULL) {
        printf("Error opening file or file does not exist!\n");
        return;
    }
    char ch;
    printf("\n--- File Content ---\n");
    while ((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    printf("--------------------\n");
    fclose(fp);
}

void appendFile() {
    FILE *fp = fopen("t.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for appending!\n");
        return;
    }
    char str[100];
    printf("Enter text to append: ");
    getchar(); // consume newline
    fgets(str, sizeof(str), stdin);
    fprintf(fp, "%s", str);
    fclose(fp);
    printf("Text appended successfully.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n--- File Operations Menu ---\n");
        printf("1. Write to File (Overwrite)\n");
        printf("2. Read from File\n");
        printf("3. Append to File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                writeFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                appendFile();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
