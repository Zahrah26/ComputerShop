#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales_Report.h"

void loadOrders(Order orders[], int *orderCount) {
    FILE *file = fopen("Order.txt", "r");  
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

void generateMonthlySalesReport(Order orders[], int orderCount, int year, int month) {
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
