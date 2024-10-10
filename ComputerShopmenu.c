// Pixel Shop Menu
// Shreya Doorgachurn
// Zahrah Suffee
// Oushvina Seewoobudut

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Product_Management/product_management.h"
#include "User_Management/user_management.h"
#include "Order_Management/Order_Management.h"  // Include Order Management header
#include "SalesReport/Sales_Report.h"           // Include Sales Report header
#include "PaymentProcessing/payment.h"
#include "AfterSalesService/after_sales_service.h"

// Function to display the main menu
void display_main_menu() {
    printf("\nMain System Menu\n");
    printf("1. Product Management\n");
    printf("2. User Management\n");
    printf("3. Order Management\n");
    printf("4. Payment Processing System\n");
    printf("5. After-Sales Service System\n");
    printf("6. Sales Report\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

void clear_screen() {
    system("cls");  // For Windows, this clears the console screen
}

int main() {
    int choice;
    int running = 1;

    while (running) {
        clear_screen();  // Clear the screen before displaying the menu
        display_main_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clear_screen();  // Clear the screen before going to the next menu
                productStaffMenu();
                break;
            case 2:
                clear_screen();
                UserMenu();
                break;
            case 3:
                clear_screen();
                // Redirect to the Order Management menu
                order_management_menu();
                break;
            case 4:
                clear_screen();
                payment_processing_system();
                break;
            case 5:
                clear_screen();
                after_sales_service_system();
                break;
            case 6:
                clear_screen();
                // Redirect to the Sales Report menu
                sales_report_menu();
                break;
            case 7:
                running = 0;
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } return 0;
}