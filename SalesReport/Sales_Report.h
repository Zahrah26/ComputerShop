#ifndef SALES_REPORT_H
#define SALES_REPORT_H

// Define a new SalesOrder struct, not depending on Order_Management.h
typedef struct {
    int orderID;
    char customerName[100];
    char product[100];
    float price;
    float discount;
    char paymentMethod[20];
    char status[20];  // Status: "Completed", "Pending", "Returned"
    int year;
    int month;
    int day;
} SalesOrder;

void loadOrders(SalesOrder orders[], int *orderCount);
void generateMonthlySalesReport(SalesOrder orders[], int orderCount, int year, int month);
void sales_report_menu();  // Add the sales report menu declaration

#endif
