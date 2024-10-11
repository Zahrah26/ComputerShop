// Shreya Doorgachurn 2312862
#ifndef PRODUCT_MANAGEMENT_H
#define PRODUCT_MANAGEMENT_H

// Structure for a product
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;

// Function prototypes
void addProduct();
void viewProducts();
void updateProduct();
void deleteProduct();
void saveToFile();
void loadFromFile();
void productStaffMenu();
int check_product_availability(int productId, int quantity);  // Check availability
void update_product_quantity(int productId, int quantity);    // Update stock

#endif // PRODUCT_MANAGEMENT_H
