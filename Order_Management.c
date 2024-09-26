#include <stdio.h>
#include <string.h>
#include "Order_Management.h"

#define MAX_ORDERS 100
Order orders[MAX_ORDERS];
int orderCount = 0;

const char *filename = "Order.txt";

// Create a new order
void create_order(Order *order) {
    if (orderCount < MAX_ORDERS) {
        orders[orderCount] = *order;
        orderCount++;
        save_orders_to_file(filename);
        printf("Order created successfully!\n");
    } else {
        printf("Order limit reached.\n");
    }
}

// Update an existing order by orderID
void update_order(int orderID, Order *newOrder) {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderID == orderID) {
            orders[i] = *newOrder;
            save_orders_to_file(filename);
            printf("Order updated successfully.\n");
            return;
        }
    }
    printf("Order not found.\n");
}

// Delete an order by orderID
void delete_order(int orderID, char *output) {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderID == orderID) {
            for (int j = i; j < orderCount - 1; j++) {
                orders[j] = orders[j + 1];
            }
            orderCount--;
            save_orders_to_file(filename);
            sprintf(output, "Order deleted successfully.\n");
            return;
        }
    }
    sprintf(output, "Order not found.\n");
}

// Query an order by orderID
void query_order(int orderID, char *output) {
    for (int i = 0; i < orderCount; i++) {
        if (orders[i].orderID == orderID) {
            sprintf(output, "OrderID: %d\n", orders[i].orderID);
            sprintf(output + strlen(output), "Name: %s\n", orders[i].name);
            sprintf(output + strlen(output), "Product: %s\n", orders[i].productName);
            sprintf(output + strlen(output), "CustomerID: %d\n", orders[i].customerID);
            sprintf(output + strlen(output), "OrderDate: %s\n", orders[i].orderDate);
            sprintf(output + strlen(output), "TotalAmount: %.2f\n", orders[i].totalAmount);
            sprintf(output + strlen(output), "Discount: %.2f\n", orders[i].discount);
            sprintf(output + strlen(output), "PaymentMethod: %s\n", orders[i].paymentMethod);
            sprintf(output + strlen(output), "Status: %s\n", orders[i].status);
            return;
        }
    }
    sprintf(output, "Order not found.\n");
}

// List all orders
void list_orders(char *output) {
    if (orderCount == 0) {
        sprintf(output, "No orders available.\n");
        return;
    }

    sprintf(output, "Listing all orders:\n");
    for (int i = 0; i < orderCount; i++) {
        sprintf(output + strlen(output), "-------------------------\n");
        sprintf(output + strlen(output), "OrderID: %d\n", orders[i].orderID);
        sprintf(output + strlen(output), "Name: %s\n", orders[i].name);
        sprintf(output + strlen(output), "Product: %s\n", orders[i].productName);
        sprintf(output + strlen(output), "CustomerID: %d\n", orders[i].customerID);
        sprintf(output + strlen(output), "OrderDate: %s\n", orders[i].orderDate);
        sprintf(output + strlen(output), "TotalAmount: %.2f\n", orders[i].totalAmount);
        sprintf(output + strlen(output), "Discount: %.2f\n", orders[i].discount);
        sprintf(output + strlen(output), "PaymentMethod: %s\n", orders[i].paymentMethod);
        sprintf(output + strlen(output), "Status: %s\n", orders[i].status);
    }
}

// Save orders to a text file
void save_orders_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < orderCount; i++) {
        fprintf(file, "%03d %s %s %d %s %.2f %.2f %s %s\n", orders[i].orderID, orders[i].name, orders[i].productName,
                orders[i].customerID, orders[i].orderDate, orders[i].totalAmount, orders[i].discount, 
                orders[i].paymentMethod, orders[i].status);
    }

    fclose(file);
}

// Load orders from the provided text file
void load_orders_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    orderCount = 0;  // Reset order count before loading
    while (fscanf(file, "%d %s %s %d %s %f %f %s %s", &orders[orderCount].orderID, orders[orderCount].name,
                  orders[orderCount].productName, &orders[orderCount].customerID, orders[orderCount].orderDate, 
                  &orders[orderCount].totalAmount, &orders[orderCount].discount, 
                  orders[orderCount].paymentMethod, orders[orderCount].status) == 9) {
        orderCount++;
    }

    fclose(file);
}
