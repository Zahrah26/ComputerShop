#ifndef AFTER_SALES_SERVICE_H
#define AFTER_SALES_SERVICE_H

#define MAX_SERVICES 100
#define MAX_CUSTOMERS 100

// Structure for a product
typedef struct {
    int productId;
    char productName[50];
    int warrantyYears;
} Product;

// Structure for a service request
typedef struct {
    int serviceId;
    int productId;
    char problemDescription[100];
    char serviceStatus[20];  // "pending", "in progress", "completed"
    float serviceCost;
    char technicianName[50];
    int isUnderWarranty;  // 1 if under warranty, 0 if not
} ServiceRequest;

// Structure for customer information
typedef struct {
    int customerId;
    char customerName[50];
    ServiceRequest serviceRequests[MAX_SERVICES];
    int serviceCount;
} Customer;

// Function declarations

// Create a new service request for a customer
void create_service_request(Customer *customer, Product productList[], int productCount);

// Check if a product is under warranty based on the purchase year
int check_warranty(Product product, int purchaseYear);

// Assign a technician to a service request
void assign_technician(ServiceRequest *serviceRequest, const char *technicianName);

// Update the status of a service request (e.g., pending, in progress, completed)
void update_service_status(ServiceRequest *serviceRequest, const char *status);

// Display the service history for a customer
void display_service_history(Customer customer);

// Save the service history for a customer to a file
void save_service_to_file(Customer customer);

// Display available technicians and their specializations
void display_available_technicians();

// Choose a technician based on the problem description
const char* choose_technician(const char *problem);

void after_sales_service_system(); 

#endif // AFTER_SALES_SERVICE_H
