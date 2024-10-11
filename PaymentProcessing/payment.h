#ifndef PAYMENT_H
#define PAYMENT_H

// Struct for storing payment user information
typedef struct {
    int id;
    char product[50];
    float price;
    float discount;
    int totalPurchases;
} PaymentUser;

// Struct for storing payment details
typedef struct {
    float totalAmount;
    float discountAmount;
    char paymentMethod1[10];
    char paymentMethod2[10];
    float amountPaid1;
    float amountPaid2;
    float remainingAmount;
} Payment;

// Function declarations
int get_user_record(int customerId, char productName[], PaymentUser *userRecord);
void apply_additional_discount(PaymentUser *userRecord);
void process_payment(PaymentUser userRecord, Payment *payment);
void save_transaction_to_file(PaymentUser userRecord, Payment payment);
void display_invoice(PaymentUser userRecord, Payment payment);
void view_transactions();
void payment_processing_system();

#endif // PAYMENT_H
