//Shreya Doorgachurn 2312862

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product_management.h"

#define FILENAME "Product_Management/product.txt"

void addProduct() {
    Product p;
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter product ID: ");
    scanf("%d", &p.id);
    printf("Enter product name: ");
    scanf("%s", p.name);
    printf("Enter product price: ");
    scanf("%f", &p.price);
    printf("Enter product quantity: ");
    scanf("%d", &p.quantity);

    fprintf(file, "%d %s %.2f %d\n", p.id, p.name, p.price, p.quantity);
    fclose(file);

    printf("Product added successfully.\n");
}

void viewProducts() {
    Product p;
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

            printf("\nID\t  Name\t\tPrice\t\tQuantity\n");
    while (fscanf(file, "%d\t%s\t\t%f\t%d", &p.id, p.name, &p.price, &p.quantity) != EOF) {
        printf("%d\t%s\t\t%.2f\t%d\n", p.id, p.name, p.price, p.quantity);
    }
    fclose(file);
}

void updateProduct() {
    Product p;
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int id, found = 0;
    printf("Enter product ID to update: ");
    scanf("%d", &id);

    FILE *tempFile = fopen("temp.txt", "w");

    while (fscanf(file, "%d\t%s\t%f\t%d", &p.id, p.name, &p.price, &p.quantity) != EOF) {
        if (p.id == id) {
            printf("Enter new product name: ");
            scanf("%s", p.name);
            printf("Enter new product price: ");
            scanf("%f", &p.price);
            printf("Enter new product quantity: ");
            scanf("%d", &p.quantity);
            found = 1;
        }
        fprintf(tempFile, "%d\t\t%s\t\t%.2f\t\t%d\n", p.id, p.name, p.price, p.quantity);
    }
    
    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("Product updated successfully.\n");
    } else {
        printf("Product not found.\n");
    }
}

void deleteProduct() {
    Product p;
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int id, found = 0;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);

    FILE *tempFile = fopen("temp.txt", "w");

    while (fscanf(file, "%d\t%s\t%f\t%d", &p.id, p.name, &p.price, &p.quantity) != EOF) {
        if (p.id != id) {
            fprintf(tempFile, "%d\t%s\t%.2f\t%d\n", p.id, p.name, p.price, p.quantity);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("Product deleted successfully.\n");
    } else {
        printf("Product not found.\n");
    }
}

int check_product_availability(int productId, int quantity) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    Product p;
    while (fscanf(file, "%d %s %f %d", &p.id, p.name, &p.price, &p.quantity) != EOF) {
        if (p.id == productId) {
            fclose(file);
            return p.quantity >= quantity;
        }
    }

    fclose(file);
    return 0;
}

void update_product_quantity(int productId, int quantity) {
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    Product p;

    while (fscanf(file, "%d %s %f %d", &p.id, p.name, &p.price, &p.quantity) != EOF) {
        if (p.id == productId) {
            p.quantity -= quantity;
        }
        fprintf(tempFile, "%d %s %.2f %d\n", p.id, p.name, p.price, p.quantity);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

void loadFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Load existing data if necessary
    fclose(file);
}

void saveToFile() {
    // Save any new data to the file if necessary
}

void productStaffMenu() {
   
    int choice;
    while (1) {
        printf("\nStaff Menu\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                updateProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                return;  // Exit to main menu
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}