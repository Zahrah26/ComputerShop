#ifndef PAYMENT_H
#define PAYMENT_H

typedef struct {
    int id;
    char product[50];
    float price;
    float discount;
    int totalPurchases;
} PaymentUser;

typedef struct {
    float totalAmount;
    char paymentMethod1[10];
    char paymentMethod2[10];
    float amountPaid1;
    float amountPaid2;
    float remainingAmount;
} Payment;

int get_user_record(int customerId, char productName[], PaymentUser *userRecord);
void apply_additional_discount(PaymentUser *userRecord);
void process_payment(PaymentUser userRecord, Payment *payment);
void save_transaction_to_file(PaymentUser userRecord, Payment payment);
void payment_processing_system();

#endif
