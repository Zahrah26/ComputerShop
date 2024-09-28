#include <stdio.h>
#include <stdlib.h>
#include "Order_Management.h"

int main() {
    int choice, orderId;

    while (1) {
        printf("\n--- Computer Shop Order Management ---\n");
        printf("1. Add Order\n");
        printf("2. View All Orders\n");
        printf("3. Query Order by ID\n");
        printf("4. Delete Order by ID\n");
        printf("5. Update Order by ID\n");
        printf("6. Exit\n");
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
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include "Sales_Report.h"

int main() {
    Order orders[100];  
    int orderCount = 0; 
    int year, month;

    loadOrders(orders, &orderCount);

    printf("Enter the year and month for the report (YYYY MM): ");
    scanf("%d %d", &year, &month);

    generateMonthlySalesReport(orders, orderCount, year, month);

    return 0;
}
