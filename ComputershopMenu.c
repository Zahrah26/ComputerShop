//Menu of the computer shop
#include <stdio.h>
#include "product_management.h"
#include "user_management.h"

int main() {
    int choice;
    printf("Welcome!\n");

    while (1) {
        printf("1. Product\n");
        printf("2. User\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                productStaffMenu();
                break;
            case 2:
                UserMenu();
            case 3:
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

