#ifndef PAYMENT_H
#define PAYMENT_H

#define MAX_ITEMS 100  // Maximum number of items in inventory

// Structure for inventory item
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Item;

// Structure for payment information
typedef struct {
    char customerName[50];
    char paymentMethod1[20];  // First payment method (e.g., cash/card)
    char paymentMethod2[20];  // Second payment method (optional, for split payments)
    float amountPaid1;  // Amount paid via first payment method
    float amountPaid2;  // Amount paid via second payment method (optional)
    float totalAmount;
    float discountRate;  // Discount applied to the total
} Payment;

// Structure for a transaction
typedef struct {
    int transactionId;
    Item items[MAX_ITEMS];
    int itemCount;
    Payment payment;
} Transaction;

// Function declarations
float calculate_total(Item items[], int itemCount);
float apply_discount(float total, float discountRate);
void process_payment(Transaction *transaction);
void update_inventory(Item inventory[], int inventoryCount, Transaction transaction);
void display_invoice(Transaction transaction);
void save_transaction_to_file(Transaction transaction);
void payment_processing_system(); 

#endif // PAYMENT_H
