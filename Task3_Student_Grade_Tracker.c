#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

typedef struct {
    int rollNo;
    char name[50];
    char course[30];
    float marks;
} Student;

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    do {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Program ended.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}

void addStudent() {
    Student s;
    FILE *fp = fopen(FILE_NAME, "ab");

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &s.rollNo);
    printf("Enter name: ");
    scanf(" %49[^\n]", s.name);
    printf("Enter course: ");
    scanf(" %29[^\n]", s.course);
    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("Student added successfully.\n");
}

void displayStudents() {
    Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    int found = 0;

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\n%-10s %-25s %-20s %-10s\n", "Roll No", "Name", "Course", "Marks");
    printf("-----------------------------------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("%-10d %-25s %-20s %-10.2f\n",
               s.rollNo, s.name, s.course, s.marks);
        found = 1;
    }

    fclose(fp);

    if (!found)
        printf("No records available.\n");
}

void searchStudent() {
    Student s;
    int roll, found = 0;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            printf("\nRoll No: %d\nName: %s\nCourse: %s\nMarks: %.2f\n",
                   s.rollNo, s.name, s.course, s.marks);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Student not found.\n");
}

void updateStudent() {
    Student s;
    int roll, found = 0;
    FILE *fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("Enter roll number to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            printf("Enter new name: ");
            scanf(" %49[^\n]", s.name);
            printf("Enter new course: ");
            scanf(" %29[^\n]", s.course);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            found = 1;
            printf("Student updated successfully.\n");
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Student not found.\n");
}

void deleteStudent() {
    Student s;
    int roll, found = 0;
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Unable to open file.\n");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}

