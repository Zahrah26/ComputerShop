#ifndef ORDER_MANAGEMENT_H
#define ORDER_MANAGEMENT_H

#define MAX_NAME_LENGTH 50
#define MAX_PRODUCT_LENGTH 50
#define MAX_PAYMENT_METHOD 20
#define MAX_STATUS 15

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int orderId;
    char customerName[MAX_NAME_LENGTH];
    char product[MAX_PRODUCT_LENGTH];
    float price;
    float discount;
    char paymentMethod[MAX_PAYMENT_METHOD];
    char status[MAX_STATUS]; 
    Date orderDate; 
} Order;

void addOrder();
void viewOrders();
void queryOrder(int id);
void deleteOrder(int id);
void updateOrder(int id);
void order_management_menu();  // Menu for handling orders

#endif
