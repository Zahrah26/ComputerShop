
#include "PaymentProcessing/payment.h"
#include "AfterSalesService/after_sales_service.h"

#include <stdio.h>
#include <string.h>

// Function to display the main menu
void display_main_menu() {
    printf("\nMain System Menu\n");
    printf("1. Payment Processing System\n");
    printf("2. After-Sales Service System\n");
    printf("3. Exit\n");
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
                payment_processing_system();
                break;
            case 2:
                after_sales_service_system();
                break;
            case 3:
                running = 0;
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
