#include "payment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "PaymentProcessing/transactions.txt"

// Function to retrieve user record from order file
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
    char line[256]; // Buffer to store each line of the file

    // Debugging: Print the productName entered by the user
    printf("Looking for product: '%s'\n", productName);

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Debugging: Print each line being read
        printf("Reading line: %s", line);

        // Use sscanf to parse the line, handling only the required fields
        int parsed = sscanf(line, "%d %49s %f %f %d", &id, product, &price, &discount, &totalPurchases);

        // Ensure all required fields are parsed
        if (parsed == 5) {
            // Debugging: Print the parsed values
            printf("Parsed ID: %d, Product: '%s', Price: %.2f, Discount: %.2f, TotalPurchases: %d\n", 
                    id, product, price, discount, totalPurchases);

            // Trim any trailing newline or spaces in product names
            product[strcspn(product, "\n")] = 0;
            product[strcspn(product, "\r")] = 0;

            // Compare customer ID and product name (case-sensitive)
            if (id == customerId && strcmp(product, productName) == 0) {
                // Populate the user record
                userRecord->id = id;
                strcpy(userRecord->product, product);
                userRecord->price = price;
                userRecord->discount = discount;
                userRecord->totalPurchases = totalPurchases;
                
                fclose(file);
                printf("Match found!\n");  // Debugging: Print success message
                return 1;  // User found
            } else {
                // Debugging: Print mismatch details
                printf("No match: ID = %d, Product = '%s' (input: '%s')\n", id, product, productName);
            }
        }
    }

    fclose(file);
    printf("Order not found for customer.\n");
    return 0;  // Order not found
}

// Function to apply additional discount if user purchased more than 5 products
void apply_additional_discount(PaymentUser *userRecord) {
    if (userRecord->totalPurchases > 5) {
        printf("Customer qualifies for an additional 2%% loyalty discount!\n");
        userRecord->discount += 2;  // Add loyalty discount
    }
}

// Function to process payment
void process_payment(PaymentUser userRecord, Payment *payment) {
    // Calculate total amount after applying the discount
    payment->totalAmount = userRecord.price - (userRecord.price * userRecord.discount / 100);
    printf("Total Amount after discount: %.2f\n", payment->totalAmount);

    // Ask for payment method
    printf("Do you want to make full or part payment? (full/part): ");
    char paymentChoice[10];
    scanf("%s", paymentChoice);

    // Full payment
    if (strcmp(paymentChoice, "full") == 0) {
        printf("Enter payment method (cash/card): ");
        scanf("%s", payment->paymentMethod1);
        payment->amountPaid1 = payment->totalAmount;
        payment->remainingAmount = 0;  // No remaining balance for full payment
    } 
    // Part payment
    else if (strcmp(paymentChoice, "part") == 0) {
        printf("Enter payment method for first part (cash/card): ");
        scanf("%s", payment->paymentMethod1);
        printf("Enter amount paid for first part: ");
        scanf("%f", &payment->amountPaid1);

        payment->remainingAmount = payment->totalAmount - payment->amountPaid1;
        printf("Remaining Amount: %.2f\n", payment->remainingAmount);

        if (payment->remainingAmount > 0) {
            printf("Enter second payment method (cash/card): ");
            scanf("%s", payment->paymentMethod2);
            printf("Enter amount paid for second part: ");
            scanf("%f", &payment->amountPaid2);
            payment->remainingAmount -= payment->amountPaid2;
        }
    } 
    else {
        printf("Invalid payment choice. Defaulting to full payment.\n");
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

// Function to save the transaction details to a file
void save_transaction_to_file(PaymentUser userRecord, Payment payment) {
    FILE *file = fopen("transactions.txt", "a");
    if (file == NULL) {
        printf("Error opening transactions file.\n");
        return;
    }

    fprintf(file, "\nTransaction for User ID: %d\n", userRecord.id);
    fprintf(file, "Product: %s\n", userRecord.product);
    fprintf(file, "Price: %.2f\n", userRecord.price);
    fprintf(file, "Discount: %.2f%%\n", userRecord.discount);
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

// Function for payment processing system
void payment_processing_system() {
    PaymentUser userRecord;
    Payment payment;

    int customerId;
    char productName[50];

    printf("Enter your customer ID: ");
    scanf("%d", &customerId);
    printf("Enter product name: ");
    scanf("%s", productName);

    // Retrieve user record
    if (!get_user_record(customerId, productName, &userRecord)) {
        return;  // Stop if the user record is not found
    }

    // Apply additional discount if applicable
    apply_additional_discount(&userRecord);

    // Process payment
    process_payment(userRecord, &payment);

    // Save transaction details to file
    save_transaction_to_file(userRecord, payment);
}

