#include "payment.h"
#include <stdio.h>

// Function to calculate the total cost of items
float calculate_total(Item items[], int itemCount) {
    float total = 0;
    for (int i = 0; i < itemCount; i++) {
        total += items[i].price * items[i].quantity;
    }
    return total;
}

// Function to apply a discount to the total amount
float apply_discount(float total, float discountRate) {
    return total - (total * discountRate / 100);
}

// Function to process the payment by handling multiple payment methods
void process_payment(Transaction *transaction) {
    printf("Enter the first payment method (cash/card): ");
    scanf("%s", transaction->payment.paymentMethod1);
    
    printf("Enter amount paid via %s: ", transaction->payment.paymentMethod1);
    scanf("%f", &transaction->payment.amountPaid1);

    if (transaction->payment.amountPaid1 < transaction->payment.totalAmount) {
        float remainingAmount = transaction->payment.totalAmount - transaction->payment.amountPaid1;
        printf("Remaining amount: %.2f\n", remainingAmount);

        printf("Enter the second payment method (cash/card): ");
        scanf("%s", transaction->payment.paymentMethod2);
        
        printf("Enter amount paid via %s: ", transaction->payment.paymentMethod2);
        scanf("%f", &transaction->payment.amountPaid2);

        if (transaction->payment.amountPaid1 + transaction->payment.amountPaid2 >= transaction->payment.totalAmount) {
            printf("Payment successful!\n");
        } else {
            printf("Insufficient funds!\n");
        }
    } else {
        printf("Payment successful!\n");
    }
}

// Function to update the inventory after a transaction
void update_inventory(Item inventory[], int inventoryCount, Transaction transaction) {
    for (int i = 0; i < transaction.itemCount; i++) {
        for (int j = 0; j < inventoryCount; j++) {
            if (inventory[j].id == transaction.items[i].id) {
                if (inventory[j].quantity >= transaction.items[i].quantity) {
                    inventory[j].quantity -= transaction.items[i].quantity;
                } else {
                    printf("Not enough stock for %s\n", inventory[j].name);
                }
            }
        }
    }
}

// Function to display the transaction invoice
void display_invoice(Transaction transaction) {
    printf("\nInvoice:\n");
    for (int i = 0; i < transaction.itemCount; i++) {
        printf("Item: %s | Quantity: %d | Price: %.2f\n", transaction.items[i].name, transaction.items[i].quantity, transaction.items[i].price);
    }
    printf("Total Amount: %.2f\n", transaction.payment.totalAmount);
    printf("Payment Method 1: %s\n", transaction.payment.paymentMethod1);
    if (transaction.payment.amountPaid2 > 0) {
        printf("Payment Method 2: %s\n", transaction.payment.paymentMethod2);
    }
}

// Function to save the transaction details to a file
void save_transaction_to_file(Transaction transaction) {
    FILE *file = fopen("transactions.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "\nTransaction ID: %d\n", transaction.transactionId);
    fprintf(file, "Customer Name: %s\n", transaction.payment.customerName);
    for (int i = 0; i < transaction.itemCount; i++) {
        fprintf(file, "Item: %s | Quantity: %d | Price: %.2f\n", transaction.items[i].name, transaction.items[i].quantity, transaction.items[i].price);
    }
    fprintf(file, "Total Amount: %.2f\n", transaction.payment.totalAmount);
    fprintf(file, "Payment Method 1: %s\n", transaction.payment.paymentMethod1);
    if (transaction.payment.amountPaid2 > 0) {
        fprintf(file, "Payment Method 2: %s\n", transaction.payment.paymentMethod2);
    }
    fprintf(file, "-------------------------------------\n");

    fclose(file);
}

// Function to handle the payment processing system
void payment_processing_system() {
    // Initialize inventory with some items
    Item inventory[MAX_ITEMS] = {
        {1, "Laptop", 10, 50000},
        {2, "Mouse", 50, 500},
        {3, "Keyboard", 30, 1500}
    };
    int inventoryCount = 3;

    Transaction transaction;
    transaction.itemCount = 0;
    transaction.transactionId = 1;  // Assign a unique transaction ID

    printf("Enter customer name: ");
    scanf("%s", transaction.payment.customerName);

    printf("How many items does the customer want to buy? ");
    scanf("%d", &transaction.itemCount);

    for (int i = 0; i < transaction.itemCount; i++) {
        printf("Enter item ID: ");
        scanf("%d", &transaction.items[i].id);
        printf("Enter quantity: ");
        scanf("%d", &transaction.items[i].quantity);

        // Match the entered item ID with the inventory and assign the price
        for (int j = 0; j < inventoryCount; j++) {
            if (inventory[j].id == transaction.items[i].id) {
                transaction.items[i].price = inventory[j].price;
                break;
            }
        }
    }

    // Calculate total cost and apply discount
    transaction.payment.totalAmount = calculate_total(transaction.items, transaction.itemCount);

    printf("Enter discount rate (in percentage): ");
    scanf("%f", &transaction.payment.discountRate);
    transaction.payment.totalAmount = apply_discount(transaction.payment.totalAmount, transaction.payment.discountRate);

    printf("Total Amount (after discount): %.2f\n", transaction.payment.totalAmount);

    // Process payment and update inventory
    process_payment(&transaction);
    update_inventory(inventory, inventoryCount, transaction);
    
    // Display and save the invoice
    display_invoice(transaction);
    save_transaction_to_file(transaction);
}

