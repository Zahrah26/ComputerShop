//Oushvina Seewoobudut -2314942
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales_Report.h"

// Function to load orders from the file into an array
void loadOrders(SalesOrder orders[], int *orderCount) {
    FILE *file = fopen("OrderManagement/Order.txt", "r");  // Ensure the file path is correct
    if (file == NULL) {
        printf("Could not open the orders file.\n");
        return;
    }

    *orderCount = 0;
    while (fscanf(file, "%d %s %s %f %f %s %s %d-%d-%d", &orders[*orderCount].orderID,
                  orders[*orderCount].customerName, orders[*orderCount].product,
                  &orders[*orderCount].price, &orders[*orderCount].discount,
                  orders[*orderCount].paymentMethod, orders[*orderCount].status,
                  &orders[*orderCount].year, &orders[*orderCount].month, &orders[*orderCount].day) != EOF) {
        (*orderCount)++;
    }

    fclose(file);
}

// Function to generate the monthly sales report
void generateMonthlySalesReport(SalesOrder orders[], int orderCount, int year, int month) {
    float totalSales = 0.0;
    float totalDiscount = 0.0;
    float totalReturns = 0.0;
    float netRevenue = 0.0;
    int completedOrders = 0;
    int returnedOrders = 0;

    printf("MONTHLY SALES REPORT for %d-%02d:\n", year, month);
    printf("-------------------------------------------------\n");
    printf("%-10s %-20s %-20s %-10s %-10s %-10s %-10s\n", "OrderID", "Customer", "Product", "Price", "Discount", "Date", "Status");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < orderCount; i++) {
        if (orders[i].year == year && orders[i].month == month) {
            float finalPrice = orders[i].price - orders[i].discount;

            printf("%-10d %-20s %-20s %-10.2f %-10.2f %d-%02d-%02d %-10s\n",
                   orders[i].orderID, orders[i].customerName,
                   orders[i].product, orders[i].price,
                   orders[i].discount, orders[i].year,
                   orders[i].month, orders[i].day,
                   orders[i].status);

            totalSales += orders[i].price;
            totalDiscount += orders[i].discount;

            // Check if the order is completed or returned
            if (strcmp(orders[i].status, "Completed") == 0) {
                netRevenue += finalPrice;
                completedOrders++;
            }

            if (strcmp(orders[i].status, "Returned") == 0) {
                totalReturns += orders[i].price;
                netRevenue -= orders[i].price;
                returnedOrders++;
            }
        }
    }

    printf("-------------------------------------------------\n");
    printf("Total Completed Orders: %d\n", completedOrders);
    printf("Total Returned Orders: %d\n", returnedOrders);
    printf("Total Sales (Before Discounts): $%.2f\n", totalSales);
    printf("Total Discounts Given: $%.2f\n", totalDiscount);
    printf("Total Returns: $%.2f\n", totalReturns);
    printf("Net Revenue (Sales - Discounts - Returns): $%.2f\n", netRevenue);
    printf("-------------------------------------------------\n");
}

// Function to display the sales report menu and handle user input
void sales_report_menu() {
    int year, month;
    SalesOrder orders[100];  // Array to hold the orders
    int orderCount = 0;

    // Load the orders from the Order.txt file
    loadOrders(orders, &orderCount);

    int choice;
    while (1) {
        printf("\n--- Sales Report System ---\n");
        printf("1. Generate Monthly Sales Report\n");
        printf("2. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the year and month for the report (YYYY MM): ");
                scanf("%d %d", &year, &month);
                generateMonthlySalesReport(orders, orderCount, year, month);  // Generate report for the selected month
                break;
            case 2:
                return;  // Exit back to the main menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
