#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student {
    int rollNo;
    char name[50];
    char course[50];
    float marks;
};

void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n====================================\n");
        printf("     STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using the system!\n");
                exit(0);

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addStudent() {
    struct Student s;
    FILE *fp;

    fp = fopen(FILE_NAME, "ab");

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("\nStudent added successfully!\n");
}

void viewStudents() {
    struct Student s;
    FILE *fp;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("\nRoll Number : %d", s.rollNo);
        printf("\nName        : %s", s.name);
        printf("\nCourse      : %s", s.course);
        printf("\nMarks       : %.2f\n", s.marks);
        printf("-------------------------------------\n");
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    FILE *fp;
    int rollNo;
    int found = 0;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == rollNo) {
            printf("\nStudent Found!\n");
            printf("Roll Number : %d\n", s.rollNo);
            printf("Name        : %s\n", s.name);
            printf("Course      : %s\n", s.course);
            printf("Marks       : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nStudent not found.\n");
    }
}

void updateStudent() {
    struct Student s;
    FILE *fp;
    int rollNo;
    int found = 0;

    fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\nEnter Roll Number to update: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == rollNo) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(struct Student), SEEK_CUR);
            fwrite(&s, sizeof(struct Student), 1, fp);

            found = 1;
            printf("\nStudent updated successfully!\n");
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nStudent not found.\n");
    }
}

void deleteStudent() {
    struct Student s;
    FILE *fp;
    FILE *temp;
    int rollNo;
    int found = 0;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if (temp == NULL) {
        fclose(fp);
        printf("\nUnable to create temporary file.\n");
        return;
    }

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == rollNo) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("\nStudent deleted successfully!\n");
    } else {
        printf("\nStudent not found.\n");
    }
}
