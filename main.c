#include <stdio.h>
#include "Order_Management.h"

int main() {
    char output[5000] = "";  // To accumulate all output for final display

    // Load existing orders from the provided Order.txt file
    load_orders_from_file("Order.txt");

    // Store initial orders list
    sprintf(output + strlen(output), "\n--- Initial Order List ---\n");
    char initialOrders[2000] = "";
    list_orders(initialOrders);
    sprintf(output + strlen(output), "%s", initialOrders);

    // Create new orders with discount, payment method, and product name
    Order order1 = {11, "Ethan", "Laptop", 1352, "2024-09-25", 500.75, 10.00, "Credit", "Pending"};
    create_order(&order1);
    
    Order order2 = {12, "Olivia", "Smartphone", 1353, "2024-09-26", 320.55, 5.00, "Cash", "Shipped"};
    create_order(&order2);

    // Store orders list after adding new ones
    sprintf(output + strlen(output), "\n--- Order List After Adding New Orders ---\n");
    char addedOrders[2000] = "";
    list_orders(addedOrders);
    sprintf(output + strlen(output), "%s", addedOrders);

    // Query a specific order (for example, orderID 11)
    sprintf(output + strlen(output), "\n--- Querying Order with OrderID 11 ---\n");
    char queryOrder[2000] = "";
    query_order(11, queryOrder);
    sprintf(output + strlen(output), "%s", queryOrder);

    // Delete an order (for example, orderID 10)
    sprintf(output + strlen(output), "\n--- Deleting Order with OrderID 10 ---\n");
    char deleteMessage[2000] = "";
    delete_order(10, deleteMessage);
    sprintf(output + strlen(output), "%s", deleteMessage);

    // Store orders list after deletion
    sprintf(output + strlen(output), "\n--- Order List After Deletion ---\n");
    char deletedOrders[2000] = "";
    list_orders(deletedOrders);
    sprintf(output + strlen(output), "%s", deletedOrders);

    // Print final output once all actions are done
    printf("%s", output);

    return 0;
}
