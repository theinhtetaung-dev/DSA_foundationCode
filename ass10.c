#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "records.txt"

struct Person
{
        char name[50];
        int age;
};

void addRecords();
void displayRecords();
void searchRecord();

int main()
{
        int choice;

        while (1)
        {
                printf("\nMenu:\n");
                printf("1. Add records\n");
                printf("2. Display all records\n");
                printf("3. Search for a record by name\n");
                printf("4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                getchar();

                switch (choice)
                {
                case 1:
                        addRecords();
                        break;
                case 2:
                        displayRecords();
                        break;
                case 3:
                        searchRecord();
                        break;
                case 4:
                        printf("Exiting the program.\n");
                        exit(0);
                default:
                        printf("Invalid choice!\n");
                }
        }

        return 0;
}

void addRecords()
{
        FILE *file = fopen(FILE_NAME, "a");
        struct Person p;

        if (file == NULL)
        {
                printf("Error opening file!\n");
                return;
        }

        while (1)
        {
                printf("Enter name (or type 'exit' to stop): ");
                fgets(p.name, sizeof(p.name), stdin);

                p.name[strcspn(p.name, "\n")] = 0;

                if (strcmp(p.name, "exit") == 0)
                {
                        break;
                }

                printf("Enter age: ");
                scanf("%d", &p.age);
                getchar();

                fprintf(file, "%s,%d\n", p.name, p.age);
        }

        fclose(file);
}

void displayRecords()
{
        FILE *file = fopen(FILE_NAME, "r");
        char line[100];

        if (file == NULL)
        {
                printf("No records found.\n");
                return;
        }

        printf("\nRecords in the file:\n");

        while (fgets(line, sizeof(line), file))
        {
                printf("%s", line);
        }

        fclose(file);
}

void searchRecord()
{
        FILE *file = fopen(FILE_NAME, "r");
        char line[100], name[50];

        if (file == NULL)
        {
                printf("No records found.\n");
                return;
        }

        printf("Enter name to search: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        int found = 0;

        while (fgets(line, sizeof(line), file))
        {
                char fileName[50];
                int age;

                sscanf(line, "%[^,],%d", fileName, &age);

                if (strcmp(fileName, name) == 0)
                {
                        printf("Found record: Name: %s, Age: %d\n", fileName, age);
                        found = 1;
                }
        }

        if (!found)
        {
                printf("No record found for %s\n", name);
        }

        fclose(file);
}