#include "after_sales_service.h"
#include <stdio.h>
#include <string.h>

// Simulate a list of available technicians for different problems
void display_available_technicians() {
    printf("Available Technicians:\n");
    printf("Technician A - Electronics\n");
    printf("Technician B - Software\n");
    printf("Technician C - Hardware\n");
}

// Choose a technician based on the problem description
const char* choose_technician(const char *problem) {
    if (strstr(problem, "screen") || strstr(problem, "display")) {
        return "Technician A";
    } else if (strstr(problem, "software")) {
        return "Technician B";
    } else {
        return "Technician C";  // Default to hardware
    }
}

void create_service_request(Customer *customer, ProductStruct productList[], int productCount) {
    int productId, purchaseYear;
    char problem[100];

    printf("Enter Product ID: ");
    scanf("%d", &productId);

    printf("Enter year of purchase: ");
    scanf("%d", &purchaseYear);

    printf("Describe the problem: ");
    getchar();  // To consume newline character left by previous scanf
    fgets(problem, sizeof(problem), stdin);
    problem[strcspn(problem, "\n")] = 0;  // Remove newline character

    // Find the product by ID
    ProductStruct selectedProduct;
    int productFound = 0;
    for (int i = 0; i < productCount; i++) {
        if (productList[i].productId == productId) {
            selectedProduct = productList[i];
            productFound = 1;
            break;
        }
    }

    if (!productFound) {
        printf("Product not found.\n");
        return;
    }

    // Check if the product is under warranty
    int isUnderWarranty = check_warranty(selectedProduct, purchaseYear);

    // Create the service request
    ServiceRequest *service = &customer->serviceRequests[customer->serviceCount];
    service->serviceId = customer->serviceCount + 1;
    service->productId = productId;
    strcpy(service->problemDescription, problem);
    strcpy(service->serviceStatus, "pending");
    service->serviceCost = isUnderWarranty ? 0.0 : 500.0;  // Example cost if not under warranty
    service->isUnderWarranty = isUnderWarranty;

    // Assign technician based on the problem
    const char *assignedTechnician = choose_technician(problem);
    strcpy(service->technicianName, assignedTechnician);

    printf("Technician %s has been assigned to the problem: %s.\n", assignedTechnician, problem);

    customer->serviceCount++;
}

int check_warranty(ProductStruct product, int purchaseYear) {
    int currentYear = 2024;  // Example current year
    int warrantyEndYear = purchaseYear + product.warrantyYears;

    if (currentYear <= warrantyEndYear) {
        printf("Product is still under warranty.\n");
        return 1;  // Under warranty
    } else {
        printf("Product is no longer under warranty.\n");
        return 0;  // Not under warranty
    }
}

void assign_technician(ServiceRequest *serviceRequest, const char *technicianName) {
    strcpy(serviceRequest->technicianName, technicianName);
    printf("Technician %s assigned to service request %d.\n", technicianName, serviceRequest->serviceId);
}

void update_service_status(ServiceRequest *serviceRequest, const char *status) {
    strcpy(serviceRequest->serviceStatus, status);
    printf("Service request %d status updated to %s.\n", serviceRequest->serviceId, status);
}

float estimate_service_cost(ServiceRequest serviceRequest) {
    if (strcmp(serviceRequest.serviceStatus, "completed") == 0) {
        return serviceRequest.isUnderWarranty ? 0.0 : 500.0;  // Example cost for non-warranty service
    }
    return 0.0;  // Free if under warranty or not completed
}

void display_service_history(Customer customer) {
    printf("\nService History for Customer %s:\n", customer.customerName);
    for (int i = 0; i < customer.serviceCount; i++) {
        ServiceRequest service = customer.serviceRequests[i];
        printf("Service ID: %d | Product ID: %d | Description: %s | Status: %s | Technician: %s | Cost: %.2f\n",
               service.serviceId, service.productId, service.problemDescription, service.serviceStatus,
               service.technicianName, service.serviceCost);
    }
}

void save_service_to_file(Customer customer) {
    FILE *file = fopen("service_history.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "\nService History for Customer %s:\n", customer.customerName);
    for (int i = 0; i < customer.serviceCount; i++) {
        ServiceRequest service = customer.serviceRequests[i];
        fprintf(file, "Service ID: %d | Product ID: %d | Description: %s | Status: %s | Technician: %s | Cost: %.2f\n",
                service.serviceId, service.productId, service.problemDescription, service.serviceStatus,
                service.technicianName, service.serviceCost);
    }

    fclose(file);
    printf("Service history saved to file.\n");
}

// Function to handle the after-sales service system
void after_sales_service_system() {
    ProductStruct productList[] = {
        {101, "Laptop", 2},  // Product with a 2-year warranty
        {102, "Mouse", 1},   // Product with a 1-year warranty
        {103, "Keyboard", 1} // Product with a 1-year warranty
    };
    int productCount = sizeof(productList) / sizeof(productList[0]);

    Customer customers[MAX_CUSTOMERS];
    int customerCount = 0;

    // Example customer
    Customer customer1 = {1, "John Doe", {{0}}, 0};
    customers[customerCount++] = customer1;

    int choice;
    int running = 1;

    while (running) {
        printf("\nAfter-Sales Service System\n");
        printf("1. Create a Service Request\n");
        printf("2. Display Available Technicians\n");
        printf("3. Display Service History\n");
        printf("4. Save Service History to File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_service_request(&customers[0], productList, productCount);
                break;
            case 2:
                display_available_technicians();
                break;
            case 3:
                display_service_history(customers[0]);
                break;
            case 4:
                save_service_to_file(customers[0]);
                break;
            case 5:
                running = 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
