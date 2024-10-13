#include "payment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "PaymentProcessing/transactions.txt"

// Function to retrieve user record from the order file
int get_user_record(int customerId, char productName[], PaymentUser *userRecord) {
    FILE *file = fopen("Order_Management/Order.txt", "r");
    if (file == NULL) {
        printf("Error opening order file.\n");
        return 0;
    }

    int id;
    char product[50];
    float price, discount;
    int totalPurchases;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        int parsed = sscanf(line, "%d %49s %f %f %d", &id, product, &price, &discount, &totalPurchases);
        product[strcspn(product, "\n")] = 0;  // Remove newline character

        if (parsed == 5 && id == customerId && strcmp(product, productName) == 0) {
            // Populate the user record struct with the data found
            userRecord->id = id;
            strcpy(userRecord->product, product);
            userRecord->price = price;
            userRecord->discount = discount;
            userRecord->totalPurchases = totalPurchases;
            fclose(file);  // Close the file after reading
            return 1;  // Return 1 if record is found
        }
    }

    fclose(file);
    return 0;  // Return 0 if no record is found
}

// Apply additional discount if the customer qualifies
void apply_additional_discount(PaymentUser *userRecord) {
    printf("Total number of purchases made by the customer: %d\n", userRecord->totalPurchases);
    if (userRecord->totalPurchases > 3) {
        printf("Customer qualifies for an additional 2%% loyalty discount!\n");
        userRecord->discount += 2;
    } else {
        printf("Customer does not qualify for the loyalty discount (requires more than 5 purchases).\n");
    }
    printf("Discount applied: %.2f%%\n", userRecord->discount);
}

// Process the payment based on the customer's choices
void process_payment(PaymentUser userRecord, Payment *payment) {
    // Calculate discount and total amount
    payment->discountAmount = userRecord.price * userRecord.discount / 100;
    payment->totalAmount = userRecord.price - payment->discountAmount;

    // Initialize amountPaid2 to 0 to ensure correct behavior for full payment
    payment->amountPaid2 = 0;

    printf("Original Price: %.2f\n", userRecord.price);
    printf("Discount: %.2f%% (Amount: %.2f)\n", userRecord.discount, payment->discountAmount);
    printf("Total Amount after discount: %.2f\n", payment->totalAmount);

    // Ask for payment method
    printf("Do you want to make full or part payment? (full/part): ");
    char paymentChoice[10];
    scanf("%9s", paymentChoice);  // Safeguard input size

    if (strcmp(paymentChoice, "full") == 0) {
        printf("Enter payment method (cash/card): ");
        scanf("%9s", payment->paymentMethod1);  // Safeguard input size
        payment->amountPaid1 = payment->totalAmount;
        payment->remainingAmount = 0;
    } else if (strcmp(paymentChoice, "part") == 0) {
        printf("Enter first payment method (cash/card): ");
        scanf("%9s", payment->paymentMethod1);
        printf("Enter amount for first payment: ");
        scanf("%f", &payment->amountPaid1);

        payment->remainingAmount = payment->totalAmount - payment->amountPaid1;
        printf("Remaining Amount: %.2f\n", payment->remainingAmount);

        if (payment->remainingAmount > 0) {
            printf("Enter second payment method (cash/card): ");
            scanf("%9s", payment->paymentMethod2);
            printf("Enter amount for second payment: ");
            scanf("%f", &payment->amountPaid2);
            payment->remainingAmount -= payment->amountPaid2;
        }
    } else {
        printf("Invalid choice. Defaulting to full payment.\n");
        strcpy(payment->paymentMethod1, "cash");
        payment->amountPaid1 = payment->totalAmount;
        payment->remainingAmount = 0;
    }

    if (payment->remainingAmount > 0) {
        printf("Payment incomplete. Remaining balance: %.2f\n", payment->remainingAmount);
    } else {
        printf("Payment complete!\n");
    }
}

// Save the transaction to a file
void save_transaction_to_file(PaymentUser userRecord, Payment payment) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error opening transactions file.\n");
        return;
    }

    fprintf(file, "\nTransaction for User ID: %d\n", userRecord.id);
    fprintf(file, "Product: %s\n", userRecord.product);
    fprintf(file, "Original Price: %.2f\n", userRecord.price);
    fprintf(file, "Discount: %.2f%% (Amount: %.2f)\n", userRecord.discount, payment.discountAmount);
    fprintf(file, "Total Amount: %.2f\n", payment.totalAmount);
    fprintf(file, "Payment Method 1: %s, Amount Paid: %.2f\n", payment.paymentMethod1, payment.amountPaid1);

    if (payment.amountPaid2 > 0) {
        fprintf(file, "Payment Method 2: %s, Amount Paid: %.2f\n", payment.paymentMethod2, payment.amountPaid2);
    }

    fprintf(file, "Remaining Amount: %.2f\n", payment.remainingAmount);
    fprintf(file, "------------------------------------------\n");

    fclose(file);
    printf("Transaction saved to file.\n");
}

// Display the invoice details
void display_invoice(PaymentUser userRecord, Payment payment) {
    printf("\n-------- Invoice --------\n");
    printf("User ID: %d\n", userRecord.id);
    printf("Product: %s\n", userRecord.product);
    printf("Original Price: %.2f\n", userRecord.price);
    printf("Discount: %.2f%% (Amount: %.2f)\n", userRecord.discount, payment.discountAmount);
    printf("Total Amount: %.2f\n", payment.totalAmount);
    printf("Payment Method 1: %s, Amount Paid: %.2f\n", payment.paymentMethod1, payment.amountPaid1);
    if (payment.amountPaid2 > 0) {
        printf("Payment Method 2: %s, Amount Paid: %.2f\n", payment.paymentMethod2, payment.amountPaid2);
    }
    printf("Remaining Amount: %.2f\n", payment.remainingAmount);
    printf("-------------------------\n");
}

// View all transactions from the file
void view_transactions() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening transactions file.\n");
        return;
    }

    char line[256];
    printf("\n-------- Transaction Records --------\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    printf("--------------------------------------\n");

    fclose(file);
}

// Main payment processing system function with menu
void payment_processing_system() {
    int choice;
    
    while (1) {
        // Display menu options
        printf("\n---- Payment Processing Menu ----\n");
        printf("1. Process a Payment\n");
        printf("2. View All Transactions\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                PaymentUser userRecord;
                Payment payment;
                int customerId;
                char productName[50];
                int recordFound = 0;

                // Input loop to ensure customer ID and product name are correct
                while (!recordFound) {
                    printf("Enter your customer ID: ");
                    scanf("%d", &customerId);
                    printf("Enter product name: ");
                    scanf("%49s", productName);  // Safeguard input size

                    // Retrieve user record
                    recordFound = get_user_record(customerId, productName, &userRecord);
                    if (!recordFound) {
                        printf("No record found for the given customer ID and product name. Please try again.\n");
                    }
                }

                // Apply additional discount if applicable
                apply_additional_discount(&userRecord);

                // Process the payment
                process_payment(userRecord, &payment);

                // Save the transaction details to a file
                save_transaction_to_file(userRecord, payment);

                // Give choice to display the invoice
                char displayChoice[10];
                printf("Do you want to display the invoice? (yes/no): ");
                scanf("%9s", displayChoice);  // Safeguard input size
                if (strcmp(displayChoice, "yes") == 0) {
                    display_invoice(userRecord, payment);
                }
                break;
            }
            case 2:
                // View transactions
                view_transactions();
                break;
            case 3:
                // Exit
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}



