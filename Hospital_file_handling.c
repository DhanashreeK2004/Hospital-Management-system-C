#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

void addPatient() {
    FILE *fp = fopen("hospital.txt", "a");
    struct Patient p;

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Disease: ");
    scanf(" %[^\n]", p.disease);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
    printf("Patient added successfully!\n");
}

void viewPatients() {
    FILE *fp = fopen("hospital.txt", "r");
    struct Patient p;

    printf("\nAll Patients:\n");
    printf("ID\tName\t\tAge\tDisease\n");
    printf("----------------------------------------\n");

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("%d\t%-15s\t%d\t%s\n", p.id, p.name, p.age, p.disease);
    }

    fclose(fp);
}

void searchPatient() {
    FILE *fp = fopen("hospital.txt", "r");
    struct Patient p;
    int searchId, found = 0;

    printf("Enter Patient ID to search: ");
    scanf("%d", &searchId);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == searchId) {
            printf("\nPatient Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\n", p.id, p.name, p.age, p.disease);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Patient with ID %d not found.\n", searchId);

    fclose(fp);
}

void deletePatient() {
    FILE *fp = fopen("hospital.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Patient p;
    int delId, found = 0;

    printf("Enter Patient ID to delete: ");
    scanf("%d", &delId);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id != delId) {
            fwrite(&p, sizeof(p), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("hospital.txt");
    rename("temp.txt", "hospital.txt");

    if (found)
        printf("Patient with ID %d deleted successfully.\n", delId);
    else
        printf("Patient with ID %d not found.\n", delId);
}

int main() {
    int choice;

    do {
        printf("\n===== Hospital Management System =====\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 5);

    return 0;
}