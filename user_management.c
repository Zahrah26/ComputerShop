#include <stdio.h>
#include <string.h>
#include "user_management.h"

#define FILENAME "user.txt"
#define PASSWORD "staff123"  // Define the staff password

void addUser() {
    User u;
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter user ID: ");
    scanf("%d", &u.id);
    printf("Enter user name: ");
    scanf("%s", u.name);
    printf("Enter user email: ");
    scanf("%s", u.email);
    printf("Enter user phone: ");
    scanf("%s", u.phone);

    fprintf(file, "%d %s %s %s\n", u.id, u.name, u.email, u.phone);
    fclose(file);

    printf("User added successfully.\n");
}

void viewUsers() {
    User u;
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nID\tName\t\t\tEmail\t\t\tPhone\n");
    printf("-----------------------------------------------\n");
    while (fscanf(file, "%d %s %s %s", &u.id, u.name, u.email, u.phone) != EOF) {
        printf("%d\t%s\t%s\t\t\t%s\n", u.id, u.name, u.email, u.phone);
    }
    fclose(file);
}

void updateUser() {
    User u;
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int id, found = 0;
    printf("Enter user ID to update: ");
    scanf("%d", &id);

    FILE *tempFile = fopen("temp.txt", "w");

    while (fscanf(file, "%d %s %s %s", &u.id, u.name, u.email, u.phone) != EOF) {
        if (u.id == id) {
            printf("Enter new user name: ");
            scanf("%s", u.name);
            printf("Enter new user email: ");
            scanf("%s", u.email);
            printf("Enter new user phone: ");
            scanf("%s", u.phone);
            found = 1;
        }
        fprintf(tempFile, "%d %s %s %s\n", u.id, u.name, u.email, u.phone);
    }
    
    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("User updated successfully.\n");
    } else {
        printf("User not found.\n");
    }
}

void deleteUser() {
    User u;
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int id, found = 0;
    printf("Enter user ID to delete: ");
    scanf("%d", &id);

    FILE *tempFile = fopen("temp.txt", "w");

    while (fscanf(file, "%d %s %s %s", &u.id, u.name, u.email, u.phone) != EOF) {
        if (u.id != id) {
            fprintf(tempFile, "%d %s %s %s\n", u.id, u.name, u.email, u.phone);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("User deleted successfully.\n");
    } else {
        printf("User not found.\n");
    }
}

int verifyPassword() {
    char password[50];
    printf("Enter staff password: ");
    scanf("%s", password);
    if (strcmp(password, PASSWORD) == 0) {
        return 1;  // Password is correct
    } else {
        return 0;  // Password is incorrect
    }
}

void staffMenu() {
    if (!verifyPassword()) {
        printf("Incorrect password. Access denied.\n");
        return;
    }

    int choice;
    while (1) {
        printf("\nStaff Menu\n");
        printf("1. Add User\n");
        printf("2. View Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                viewUsers();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                return;  // Exit to main menu
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
