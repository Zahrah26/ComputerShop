#ifndef ORDER_MANAGEMENT_H
#define ORDER_MANAGEMENT_H

typedef struct {
    int day;
    int month;
    int year;
} Date;

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

// Function Prototypes
void getDate(Date *date);
void addOrder();
void viewOrders();
void queryOrder(int customerId);
void deleteOrder(int customerId);
void updateOrderStatus(int customerId);
void order_management_menu();

#endif  // ORDER_MANAGEMENT_H
