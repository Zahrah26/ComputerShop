// Oushvina Seewoobudut - 2314942
#ifndef ORDER_MANAGEMENT_H
#define ORDER_MANAGEMENT_H

// Date structure to store order date
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Order structure containing order details
typedef struct {
    int customerId;
    char productName[50];
    float price;
    float discount;
    int warrantyYears;
    char paymentMethod[20];
    char status[20];  // "pre-order", "delivered", or "pending"
    Date orderDate;
} Order;

// Function prototypes for order management
void getDate(Date *date);
void addOrder();
void viewOrders();
void queryOrder(int customerId);
void deleteOrder(int customerId);
void updateOrderStatus(int customerId);
void order_management_menu();

#endif  // ORDER_MANAGEMENT_H
