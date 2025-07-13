#include <stdio.h>
#include <string.h>

#define MAX 100

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

struct Patient patients[MAX];
int count = 0;

void addPatient() {
    if (count >= MAX) {
        printf("Patient list is full!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &patients[count].id);
    printf("Enter Name: ");
    scanf(" %[^\n]", patients[count].name);
    printf("Enter Age: ");
    scanf("%d", &patients[count].age);
    printf("Enter Disease: ");
    scanf(" %[^\n]", patients[count].disease);

    count++;
    printf("Patient added successfully!\n");
}

void viewPatients() {
    if (count == 0) {
        printf("No patient records found.\n");
        return;
    }

    printf("\nAll Patients:\n");
    printf("ID\tName\t\tAge\tDisease\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%d\t%-15s\t%d\t%s\n",
               patients[i].id,
               patients[i].name,
               patients[i].age,
               patients[i].disease);
    }
}

void searchPatient() {
    int id, found = 0;
    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            printf("\nPatient Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\n",
                   patients[i].id,
                   patients[i].name,
                   patients[i].age,
                   patients[i].disease);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Patient with ID %d not found.\n", id);
}

void deletePatient() {
    int id, index = -1;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }

    for (int i = index; i < count - 1; i++) {
        patients[i] = patients[i + 1];
    }

    count--;
    printf("Patient with ID %d deleted successfully.\n", id);
}

int main() {
    int choice;

    do {
        printf("\n===== Hospital Management System (In-Memory) =====\n");
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
            case 5: printf("Exiting program...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 5);

    return 0;
}s