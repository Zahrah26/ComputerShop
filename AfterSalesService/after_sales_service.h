//Zahrah Suffee-2315249
#ifndef AFTER_SALES_SERVICE_H
#define AFTER_SALES_SERVICE_H

// Function declarations
int check_if_product_sold(int customerId, char productName[], int *purchaseYear, int *purchaseMonth, int *purchaseDay);
int is_within_warranty(int purchaseYear, int purchaseMonth, int purchaseDay, int currentYear, int currentMonth, int currentDay, int warrantyYears);
const char* choose_technician(const char *problem);
void create_service_request();
void display_available_technicians();
void view_service_requests();  // Added declaration
void after_sales_service_system();

#endif  // AFTER_SALES_SERVICE_H
