#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "product_management.h"

#define FILENAME "Product_Management/product.txt"

// Function to add a product
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
    getchar();  // To remove any leftover newline character in input buffer
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;  // Remove trailing newline
    printf("Enter product price: ");
    scanf("%f", &p.price);
    printf("Enter product quantity: ");
    scanf("%d", &p.quantity);

    // Write to file with consistent formatting
    fprintf(file, "%d\t%s\t%.2f\t%d\n", p.id, p.name, p.price, p.quantity);
    fclose(file);

    printf("Product added successfully.\n");
}

// Function to view products
void viewProducts() {
    Product p;
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Display header
    printf("\n%-10s %-25s %-10s %-10s\n", "ID", "Name", "Price", "Quantity");
    printf("---------------------------------------------------------\n");

    // Read from file and print with proper alignment
    while (fscanf(file, "%d\t%[^\t]\t%f\t%d\n", &p.id, p.name, &p.price, &p.quantity) != EOF) {
        printf("%-10d %-25s %-10.2f %-10d\n", p.id, p.name, p.price, p.quantity);
    }

    fclose(file);
}

// Function to update a product
void updateProduct() {
    Product p;
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int id, found = 0;
    printf("Enter product ID to update: ");
    scanf("%d", &id);

    FILE *tempFile = fopen("temp.txt", "w");

    while (fscanf(file, "%d\t%[^\t]\t%f\t%d\n", &p.id, p.name, &p.price, &p.quantity) != EOF) {
        if (p.id == id) {
            printf("Enter new product name: ");
            getchar();
            fgets(p.name, sizeof(p.name), stdin);
            p.name[strcspn(p.name, "\n")] = 0;  // Remove trailing newline
            printf("Enter new product price: ");
            scanf("%f", &p.price);
            printf("Enter new product quantity: ");
            scanf("%d", &p.quantity);
            found = 1;
        }

        fprintf(tempFile, "%d\t%s\t%.2f\t%d\n", p.id, p.name, p.price, p.quantity);
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

// Function to delete a product
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

    while (fscanf(file, "%d\t%[^\t]\t%f\t%d\n", &p.id, p.name, &p.price, &p.quantity) != EOF) {
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

// Function to check product availability
int check_product_availability(int productId, int quantity) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    Product p;
    while (fscanf(file, "%d\t%[^\t]\t%f\t%d\n", &p.id, p.name, &p.price, &p.quantity) != EOF) {
        if (p.id == productId) {
            fclose(file);
            return p.quantity >= quantity;
        }
    }

    fclose(file);
    return 0;
}

// Function to update product quantity
void update_product_quantity(int productId, int quantity) {
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    Product p;

    while (fscanf(file, "%d\t%[^\t]\t%f\t%d\n", &p.id, p.name, &p.price, &p.quantity) != EOF) {
        if (p.id == productId) {
            p.quantity -= quantity;
        }

        fprintf(tempFile, "%d\t%s\t%.2f\t%d\n", p.id, p.name, p.price, p.quantity);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

// Function to display the staff menu
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
