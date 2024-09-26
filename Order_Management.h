#ifndef ORDER_MANAGEMENT_H
#define ORDER_MANAGEMENT_H

typedef struct {
    int orderID;
    char name[50];         // Customer's name
    char productName[50];   // Added field for product name
    int customerID;
    char orderDate[20];
    float totalAmount;
    float discount;        // Field for discount
    char paymentMethod[20]; // Field for payment method (e.g., "Credit", "Cash", etc.)
    char status[20];
} Order;

void create_order(Order *order);
void update_order(int orderID, Order *newOrder);
void delete_order(int orderID, char *output);
void query_order(int orderID, char *output);
void list_orders(char *output);
void save_orders_to_file(const char *filename);
void load_orders_from_file(const char *filename);

#endif
