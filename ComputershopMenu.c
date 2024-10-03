//Shop Menu
#include <stdio.h>
#include <string.h>

#include "Product_Management/product_management.h"
#include "User_Management/user_management.h"

#include "PaymentProcessing/payment.h"
#include "AfterSalesService/after_sales_service.h"

// Function to display the main menu
void display_main_menu() {
    printf("\nMain System Menu\n");
    printf("1. Product\n");
    printf("2. User\n");
    printf("3. Payment Processing System\n");
    printf("4. After-Sales Service System\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    int running = 1;

    while (running) {
        display_main_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                productStaffMenu();
                break;
            case 2:
                UserMenu();
                break;
            case 3:
                payment_processing_system();
                break;
            case 4:
                after_sales_service_system();
                break;
            case 5:
                running = 0;
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
