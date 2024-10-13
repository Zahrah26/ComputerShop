#ifndef PRODUCT_MANAGEMENT_H
#define PRODUCT_MANAGEMENT_H

// Define the Product structure
typedef struct {
    int id;
    char name[50];  // Allowing up to 50 characters for the product name
    float price;
    int quantity;
} Product;

// Function declarations for product management
void addProduct();                      // Function to add a new product
void viewProducts();                    // Function to view all products
void updateProduct();                   // Function to update an existing product
void deleteProduct();                   // Function to delete a product
int check_product_availability(int productId, int quantity);  // Function to check product availability
void update_product_quantity(int productId, int quantity);    // Function to update product quantity

void productStaffMenu();                // Function to display the staff menu

#endif  // PRODUCT_MANAGEMENT_H
