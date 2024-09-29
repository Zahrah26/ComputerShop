//Shreya Doorgachurn 2312862
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

#endif // PRODUCT_MANAGEMENT_H
