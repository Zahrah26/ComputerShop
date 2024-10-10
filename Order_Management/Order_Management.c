#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Order_Management.h"

#define FILE_NAME "Order.txt"

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
    printf("Enter Order ID: ");
    scanf("%d", &newOrder.orderId);
    printf("Enter Customer Name: ");
    scanf("%s", newOrder.customerName);
    printf("Enter Product: ");
    scanf("%s", newOrder.product);
    printf("Enter Price: ");
    scanf("%f", &newOrder.price);
    printf("Enter Discount: ");
    scanf("%f", &newOrder.discount);
    printf("Enter Payment Method: ");
    scanf("%s", newOrder.paymentMethod);
    printf("Enter Status: ");
    scanf("%s", newOrder.status);

    getDate(&newOrder.orderDate);

    fprintf(file, "%d %s %s %.2f %.2f %s %s %02d-%02d-%04d\n", newOrder.orderId, newOrder.customerName, newOrder.product, 
            newOrder.price, newOrder.discount, newOrder.paymentMethod, newOrder.status,
            newOrder.orderDate.day, newOrder.orderDate.month, newOrder.orderDate.year);

    fclose(file);
    printf("Order added successfully.\n");
}

// View all orders
void viewOrders() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No orders found!\n");
        return;
    }

    Order order;
    printf("Order ID\tCustomer Name\tProduct\t\tPrice\tDiscount\tPayment\tStatus\t\tDate\n");
    printf("--------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d %s %s %f %f %s %s %d-%d-%d", &order.orderId, order.customerName, order.product, 
                  &order.price, &order.discount, order.paymentMethod, order.status, 
                  &order.orderDate.day, &order.orderDate.month, &order.orderDate.year) != EOF) {
        printf("%d\t\t%s\t\t%s\t\t%.2f\t%.2f\t%s\t%s\t%02d-%02d-%04d\n", 
               order.orderId, order.customerName, order.product, 
               order.price, order.discount, order.paymentMethod, order.status,
               order.orderDate.day, order.orderDate.month, order.orderDate.year);
    }

    fclose(file);
}

// Query order by ID
void queryOrder(int id) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    int found = 0;

    while (fscanf(file, "%d %s %s %f %f %s %s %d-%d-%d", &order.orderId, order.customerName, order.product, 
                  &order.price, &order.discount, order.paymentMethod, order.status, 
                  &order.orderDate.day, &order.orderDate.month, &order.orderDate.year) != EOF) {
        if (order.orderId == id) {
            printf("\nOrder Found:\n");
            printf("Order ID: %d\n", order.orderId);
            printf("Customer Name: %s\n", order.customerName);
            printf("Product: %s\n", order.product);
            printf("Price: %.2f\n", order.price);
            printf("Discount: %.2f\n", order.discount);
            printf("Payment Method: %s\n", order.paymentMethod);
            printf("Status: %s\n", order.status);
            printf("Date: %02d-%02d-%04d\n", order.orderDate.day, order.orderDate.month, order.orderDate.year);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Order with ID %d not found.\n", id);
    }
}

// Delete order by ID
void deleteOrder(int id) {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    int found = 0;

    while (fscanf(file, "%d %s %s %f %f %s %s %d-%d-%d", &order.orderId, order.customerName, order.product, 
                  &order.price, &order.discount, order.paymentMethod, order.status, 
                  &order.orderDate.day, &order.orderDate.month, &order.orderDate.year) != EOF) {
        if (order.orderId != id) {
            fprintf(tempFile, "%d %s %s %.2f %.2f %s %s %02d-%02d-%04d\n", order.orderId, order.customerName, order.product, 
                    order.price, order.discount, order.paymentMethod, order.status,
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
        printf("Order with ID %d deleted successfully.\n", id);
    } else {
        printf("Order with ID %d not found.\n", id);
    }
}

// Update order by ID
void updateOrder(int id) {
    FILE *file = fopen(FILE_NAME, "r+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    int found = 0;

    while (fscanf(file, "%d %s %s %f %f %s %s %d-%d-%d", &order.orderId, order.customerName, order.product, 
                  &order.price, &order.discount, order.paymentMethod, order.status, 
                  &order.orderDate.day, &order.orderDate.month, &order.orderDate.year) != EOF) {
        if (order.orderId == id) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Order with ID %d not found.\n", id);
        fclose(file);
        return;
    }

    fseek(file, -(long)sizeof(order), SEEK_CUR);

    printf("Enter new Customer Name: ");
    scanf("%s", order.customerName);
    printf("Enter new Product: ");
    scanf("%s", order.product);
    printf("Enter new Price: ");
    scanf("%f", &order.price);
    printf("Enter new Discount: ");
    scanf("%f", &order.discount);
    printf("Enter new Payment Method: ");
    scanf("%s", order.paymentMethod);
    printf("Enter new Status: ");
    scanf("%s", order.status);
    printf("Enter new Order Date (dd mm yyyy): ");
    scanf("%d %d %d", &order.orderDate.day, &order.orderDate.month, &order.orderDate.year);

    fprintf(file, "%d %s %s %.2f %.2f %s %s %02d-%02d-%04d\n", order.orderId, order.customerName, order.product, 
            order.price, order.discount, order.paymentMethod, order.status,
            order.orderDate.day, order.orderDate.month, order.orderDate.year);

    fclose(file);
    printf("Order with ID %d updated successfully.\n");
}

// Menu for Order Management
void order_management_menu() {
    int choice, orderId;

    while (1) {
        printf("\n--- Order Management System ---\n");
        printf("1. Add Order\n");
        printf("2. View All Orders\n");
        printf("3. Query Order by ID\n");
        printf("4. Delete Order by ID\n");
        printf("5. Update Order by ID\n");
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
                printf("Enter Order ID to query: ");
                scanf("%d", &orderId);
                queryOrder(orderId);
                break;
            case 4:
                printf("Enter Order ID to delete: ");
                scanf("%d", &orderId);
                deleteOrder(orderId);
                break;
            case 5:
                printf("Enter Order ID to update: ");
                scanf("%d", &orderId);
                updateOrder(orderId);
                break;
            case 6:
                return;  // Exit to the main menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
