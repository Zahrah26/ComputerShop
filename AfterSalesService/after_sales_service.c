#include "after_sales_service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if the product was sold to the customer
int check_if_product_sold(int customerId, char productName[], int *purchaseYear,
                          int *purchaseMonth, int *purchaseDay) {
  FILE *file = fopen("Order_Management/Order.txt", "r");
  if (file == NULL) {
    printf("Error: Could not open 'Order.txt'.\n");
    return 0;
  }

  int orderId;
  char customerName[50], product[50], paymentMethod[20], status[20];
  float price, discount;
  int day, month, year;

  // Scan through each order and check if it matches customer ID and product
  // name
  while (fscanf(file, "%d %s %s %f %f %s %s %d-%d-%d", &orderId, customerName,
                product, &price, &discount, paymentMethod, status, &day, &month,
                &year) != EOF) {
    if (customerId == orderId) {
      *purchaseYear = year;
      *purchaseMonth = month;
      *purchaseDay = day;
      fclose(file);
      return 1; // Product found
    }
  }

  fclose(file);
  printf("Error: Product '%s' was not purchased by customer ID %d.\n",
         productName, customerId);
  return 0; // Product not found
}

// Function to compare the current date with the purchase date and check
// warranty
int is_within_warranty(int purchaseYear, int purchaseMonth, int purchaseDay,
                       int currentYear, int currentMonth, int currentDay,
                       int warrantyYears) {
  if (currentYear < purchaseYear + warrantyYears ||
      (currentYear == purchaseYear + warrantyYears &&
       currentMonth < purchaseMonth) ||
      (currentYear == purchaseYear + warrantyYears &&
       currentMonth == purchaseMonth && currentDay <= purchaseDay)) {
    return 1; // Under warranty
  }
  return 0; // Warranty expired
}

// Function to choose a technician based on the problem description
const char *choose_technician(const char *problem) {
  if (strstr(problem, "screen") || strstr(problem, "display")) {
    return "Technician A";
  } else if (strstr(problem, "software")) {
    return "Technician B";
  } else {
    return "Technician C"; // Default for hardware issues
  }
}

// Function to display available technicians
void display_available_technicians() {
  printf("Available Technicians:\n");
  printf("Technician A - Electronics\n");
  printf("Technician B - Software\n");
  printf("Technician C - Hardware\n");
}

// Function to create a service request and process warranty and technician
// assignment
void create_service_request() {
  int customerId, purchaseYear, purchaseMonth, purchaseDay;
  char productName[50], problem[100];
  int day, month, year;

  printf("Enter Customer ID: ");
  scanf("%d", &customerId);

  printf("Enter Product Name: ");
  scanf("%s", productName);

  // Check if the product was sold to the customer
  if (!check_if_product_sold(customerId, productName, &purchaseYear,
                             &purchaseMonth, &purchaseDay)) {
    return; // Exit if product was not found
  }

  // Ask for the current date
  printf("Enter today's date (dd mm yyyy): ");
  scanf("%d %d %d", &day, &month, &year);

  // Check if the product is within warranty
  if (!is_within_warranty(purchaseYear, purchaseMonth, purchaseDay, year, month,
                          day, 2)) { // Assuming 2-year warranty for simplicity
    printf("Warranty no longer available.\n");
    return;
  } else {
    printf("Warranty is still valid.\n");
  }

  // Ask for the problem description
  printf("Describe the problem: ");
  getchar(); // Consume leftover newline
  fgets(problem, sizeof(problem), stdin);
  problem[strcspn(problem, "\n")] = 0; // Remove trailing newline

  // Assign a technician based on the problem description
  const char *assignedTechnician = choose_technician(problem);
  printf("Technician %s has been assigned to the issue: %s\n",
         assignedTechnician, problem);

  // Save the service request details to a file
  FILE *file = fopen("service_requests.txt", "a");
  if (file == NULL) {
    printf("Error: Could not open 'service_requests.txt'.\n");
    return;
  }

  fprintf(file,
          "Customer ID: %d\nProduct: %s\nProblem: %s\nAssigned Technician: "
          "%s\nDate: %d-%d-%d\n\n",
          customerId, productName, problem, assignedTechnician, day, month,
          year);
  fclose(file);

  printf("Service request saved successfully.\n");
}

// Function to handle after-sales service system
void after_sales_service_system() {
  int choice;
  int running = 1;

  while (running) {
    printf("\n--- After-Sales Service System Menu ---\n");
    printf("1. Create a Service Request\n");
    printf("2. Display Available Technicians\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      create_service_request();
      break;
    case 2:
      display_available_technicians();
      break;
    case 3:
      running = 0;
      printf("Exiting system...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
}