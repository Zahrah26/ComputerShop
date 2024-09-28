#ifndef SALES_REPORT_H
#define SALES_REPORT_H
#include "Order_Management.h"



typedef struct {
    int orderID;
    char customerName[100];
    char product[100];
    float price;
    float discount;
    char paymentMethod[20];
    char status[20]; // Status could be "Completed", "Pending", or "Returned"
    int year;
    int month;
    int day;
} Order;

void loadOrders(Order orders[], int *orderCount);
void generateMonthlySalesReport(Order orders[], int orderCount, int year, int month);

#endif 
