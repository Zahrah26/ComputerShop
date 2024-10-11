//Zahrah Suffee-2315249
#include "after_sales_service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "AfterSalesService/service_requests.txt"  // Ensuring file is in the same folder

// Function to check if the product was sold to the customer
int check_if_product_sold(int customerId, char productName[], int *purchaseYear, int *purchaseMonth, int *purchaseDay) {
  FILE *file = fopen("Order_Management/Order.txt", "r");
  if (file == NULL) {
    printf("Error: Could not open 'Order.txt'.\n");
    return 0;
  }

  int orderId;
  char customerName[50], product[50], paymentMethod[20], status[20];
  float price, discount;
  int day, month, year;

  // Scan through each order and check if it matches customer ID and product name
  while (fscanf(file, "%d %s %s %f %f %s %s %d-%d-%d", &orderId, customerName, product, &price, &discount, paymentMethod, status, &day, &month, &year) != EOF) {
    if (customerId == orderId) {
      *purchaseYear = year;
      *purchaseMonth = month;
      *purchaseDay = day;
      fclose(file);
      return 1; // Product found
    }
  }

  fclose(file);
  printf("Error: Product '%s' was not purchased by customer ID %d.\n", productName, customerId);
  return 0; // Product not found
}

// Function to check warranty validity
int is_within_warranty(int purchaseYear, int purchaseMonth, int purchaseDay, int currentYear, int currentMonth, int currentDay, int warrantyYears) {
  if (currentYear < purchaseYear + warrantyYears || (currentYear == purchaseYear + warrantyYears && currentMonth < purchaseMonth) || 
      (currentYear == purchaseYear + warrantyYears && currentMonth == purchaseMonth && currentDay <= purchaseDay)) {
    return 1; // Under warranty
  }
  return 0; // Warranty expired
}

// Function to assign a technician based on problem description
const char *choose_technician(const char *problem) {
  if (strstr(problem, "screen") || strstr(problem, "display")) {
    return "John";
  } else if (strstr(problem, "software")) {
    return "Mark";
  } else {
    return "Sam"; // Default for hardware issues
  }
}

// Function to display available technicians
void display_available_technicians() {
  printf("Available Technicians:\n");
  printf("John - Electronics\n");
  printf("Mark - Software\n");
  printf("Sam - Hardware\n");
}

// Function to create a service request
void create_service_request() {
  int customerId, purchaseYear, purchaseMonth, purchaseDay;
  char productName[50], problem[100];
  int day, month, year;

  printf("Enter Customer ID: ");
  scanf("%d", &customerId);

  printf("Enter Product Name: ");
  scanf("%s", productName);

  // Check if the product was sold to the customer
  if (!check_if_product_sold(customerId, productName, &purchaseYear, &purchaseMonth, &purchaseDay)) {
    return; // Exit if product was not found
  }

  // Ask for the current date
  printf("Enter today's date (dd mm yyyy): ");
  scanf("%d %d %d", &day, &month, &year);

  // Check warranty
  if (!is_within_warranty(purchaseYear, purchaseMonth, purchaseDay, year, month, day, 5)) { // Assuming 5-year warranty
    printf("Warranty no longer available.\n");
    return;
  } else {
    printf("Warranty is still valid.\n");
  }

  // Problem description
  printf("Describe the problem: ");
  getchar(); // Consume leftover newline
  fgets(problem, sizeof(problem), stdin);
  problem[strcspn(problem, "\n")] = 0; // Remove trailing newline

  // Assign technician
  const char *assignedTechnician = choose_technician(problem);
  printf("Technician %s has been assigned to the issue: %s\n", assignedTechnician, problem);

  // Save service request to file
  FILE *file = fopen(FILE_NAME, "a");  // Use FILE_NAME for the file path
  if (file == NULL) {
    printf("Error: Could not open '%s'.\n", FILE_NAME);
    return;
  }

  fprintf(file, "Customer ID: %d\nProduct: %s\nProblem: %s\nAssigned Technician: %s\nDate: %d-%d-%d\n\n", 
          customerId, productName, problem, assignedTechnician, day, month, year);
  fclose(file);

  printf("Service request saved successfully.\n");
}

// Function to display service requests
void view_service_requests() {
  FILE *file = fopen(FILE_NAME, "r");  // Use FILE_NAME for the file path
  if (file == NULL) {
    printf("Error: Could not open '%s'.\n", FILE_NAME);
    return;
  }

  char ch;
  printf("\n--- Service Requests ---\n");
  while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
  }
  fclose(file);
}

// Function to handle after-sales service system
void after_sales_service_system() {
  int choice;
  int running = 1;

  while (running) {
    printf("\n--- After-Sales Service System Menu ---\n");
    printf("1. Create a Service Request\n");
    printf("2. Display Available Technicians\n");
    printf("3. View Service Requests\n");
    printf("4. Exit\n");
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
      view_service_requests();  // View service requests option
      break;
    case 4:
      running = 0;
      printf("Exiting system...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
 }
}
}