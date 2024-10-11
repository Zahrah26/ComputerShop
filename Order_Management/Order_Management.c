#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Order_Management.h"

#define FILE_NAME "Order_Management/Order.txt"

// Function to input order date
void getDate(Date *date) {
    printf("Enter Order Date (dd mm yyyy): ");
    scanf("%d %d %d", &date->day, &date->month, &date->year);
}

// Add a new order
void addOrder() {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order newOrder;
    printf("Enter Customer ID: ");
    scanf("%d", &newOrder.customerId);
    printf("Enter Product Name: ");
    scanf("%s", newOrder.productName);
    printf("Enter Price: ");
    scanf("%f", &newOrder.price);
    printf("Enter Discount: ");
    scanf("%f", &newOrder.discount);
    printf("Enter Warranty (in years): ");
    scanf("%d", &newOrder.warrantyYears);
    printf("Enter Payment Method (cash/card): ");
    scanf("%s", newOrder.paymentMethod);
    printf("Enter Status (pre-order/delivered/pending): ");
    scanf("%s", newOrder.status);

    // Store order date
    getDate(&newOrder.orderDate);

    // Save the order to the file with proper alignment
    fprintf(file, "%-10d %-20s %-10.2f %-10.2f %-10d %-10s %-10s %02d-%02d-%04d\n", 
            newOrder.customerId, newOrder.productName, newOrder.price, newOrder.discount, 
            newOrder.warrantyYears, newOrder.paymentMethod, newOrder.status, 
            newOrder.orderDate.day, newOrder.orderDate.month, newOrder.orderDate.year);

    fclose(file);
    printf("Order added successfully!\n");
}

// View all orders
void viewOrders() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No orders found!\n");
        return;
    }

    Order order;
    printf("%-10s %-20s %-10s %-10s %-10s %-10s %-10s %-12s\n", "Customer ID", "Product Name", "Price", "Discount", "Warranty", "Payment", "Status", "Date");
    printf("--------------------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d %s %f %f %d %s %s %d-%d-%d", &order.customerId, order.productName, 
                  &order.price, &order.discount, &order.warrantyYears, order.paymentMethod, 
                  order.status, &order.orderDate.day, &order.orderDate.month, &order.orderDate.year) != EOF) {
        printf("%-10d %-20s %-10.2f %-10.2f %-10d %-10s %-10s %02d-%02d-%04d\n", 
               order.customerId, order.productName, order.price, order.discount, 
               order.warrantyYears, order.paymentMethod, order.status, 
               order.orderDate.day, order.orderDate.month, order.orderDate.year);
    }

    fclose(file);
}

// Query order by customer ID
void queryOrder(int customerId) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    int found = 0;

    while (fscanf(file, "%d %s %f %f %d %s %s %d-%d-%d", &order.customerId, order.productName, 
                  &order.price, &order.discount, &order.warrantyYears, order.paymentMethod, 
                  order.status, &order.orderDate.day, &order.orderDate.month, &order.orderDate.year) != EOF) {
        if (order.customerId == customerId) {
            printf("\nOrder Found:\n");
            printf("Customer ID: %d\n", order.customerId);
            printf("Product: %s\n", order.productName);
            printf("Price: %.2f\n", order.price);
            printf("Discount: %.2f\n", order.discount);
            printf("Warranty: %d years\n", order.warrantyYears);
            printf("Payment Method: %s\n", order.paymentMethod);
            printf("Status: %s\n", order.status);
            printf("Order Date: %02d-%02d-%04d\n", order.orderDate.day, order.orderDate.month, order.orderDate.year);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("No order found for Customer ID %d.\n", customerId);
    }
}

// Delete order by customer ID
void deleteOrder(int customerId) {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    int found = 0;

    while (fscanf(file, "%d %s %f %f %d %s %s %d-%d-%d", &order.customerId, order.productName, 
                  &order.price, &order.discount, &order.warrantyYears, order.paymentMethod, 
                  order.status, &order.orderDate.day, &order.orderDate.month, &order.orderDate.year) != EOF) {
        if (order.customerId != customerId) {
            fprintf(tempFile, "%-10d %-20s %-10.2f %-10.2f %-10d %-10s %-10s %02d-%02d-%04d\n", 
                    order.customerId, order.productName, order.price, order.discount, 
                    order.warrantyYears, order.paymentMethod, order.status, 
                    order.orderDate.day, order.orderDate.month, order.orderDate.year);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("Order for Customer ID %d deleted successfully.\n", customerId);
    } else {
        printf("No order found for Customer ID %d.\n", customerId);
    }
}

// Update order status by customer ID
void updateOrderStatus(int customerId) {
    FILE *file = fopen(FILE_NAME, "r+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    int found = 0;

    while (fscanf(file, "%d %s %f %f %d %s %s %d-%d-%d", &order.customerId, order.productName, 
                  &order.price, &order.discount, &order.warrantyYears, order.paymentMethod, 
                  order.status, &order.orderDate.day, &order.orderDate.month, &order.orderDate.year) != EOF) {
        if (order.customerId == customerId) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No order found for Customer ID %d.\n", customerId);
        fclose(file);
        return;
    }

    fseek(file, -(long)sizeof(order), SEEK_CUR);

    printf("Enter new status (pre-order/delivered/pending): ");
    scanf("%s", order.status);

    fprintf(file, "%-10d %-20s %-10.2f %-10.2f %-10d %-10s %-10s %02d-%02d-%04d\n", 
            order.customerId, order.productName, order.price, order.discount, 
            order.warrantyYears, order.paymentMethod, order.status, 
            order.orderDate.day, order.orderDate.month, order.orderDate.year);

    fclose(file);
    printf("Order status updated successfully.\n");
}

// Order Management Menu
void order_management_menu() {
    int choice, customerId;

    while (1) {
        printf("\n--- Order Management System ---\n");
        printf("1. Add Order\n");
        printf("2. View All Orders\n");
        printf("3. Query Order by Customer ID\n");
        printf("4. Delete Order by Customer ID\n");
        printf("5. Update Order Status by Customer ID\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addOrder();
                break;
            case 2:
                viewOrders();
                break;
            case 3:
                printf("Enter Customer ID to query: ");
                scanf("%d", &customerId);
                queryOrder(customerId);
                break;
            case 4:
                printf("Enter Customer ID to delete: ");
                scanf("%d", &customerId);
                deleteOrder(customerId);
                break;
            case 5:
                printf("Enter Customer ID to update status: ");
                scanf("%d", &customerId);
                updateOrderStatus(customerId);
                break;
            case 6:
                return;  // Exit to the main menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
