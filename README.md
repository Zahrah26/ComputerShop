# Computer Shop


The Pixel Shop System is a comprehensive software solution designed to manage various aspects of a computer shop. This system provides functionalities for managing products, users, orders, payments, after-sales service, and generating sales reports. The project is a collaboration between Zahrah Suffee, Shreya Doorgachurn, and Oushvina Seewoobudut.

Pixel Shop System is a fully-integrated software solution developed to streamline operations in a computer shop. It encompasses various modules including product management, user management, order management, payment processing, after-sales services, and sales reporting. This system is designed to be modular, efficient, and user-friendly.

The system comprises six key modules that manage different aspects of the shop’s operations. Each module focuses on a distinct feature of the system, working together to provide a seamless experience for both the staff and customers.

Features:
1.Manage products and their inventories.

2.Handle customer information.

3.Process customer orders and payments.

4.Generate comprehensive sales reports.

5.Facilitate after-sales services, including warranty tracking and technician assignment.

Modules

1. Product Management
File: Product_Management/product_management.c
Header: Product_Management/product_management.h

This module provides functionalities for managing products in the shop, including:

Adding Products: Allows staff to input new products into the system by providing details like product ID, name, price, and quantity.
Viewing Products: Displays all the products currently available in the system.
Updating Products: Enables staff to update the details of an existing product.
Deleting Products: Removes a product from the system based on the product ID.
Stock Management: Provides functionality to check product availability and update stock quantities when orders are placed.


2. User Management
File: User_Management/user_management.c
Header: User_Management/user_management.h

This module handles all operations related to managing users, including:

Adding Users: Allows the addition of new customers with details such as user ID, name, email, and phone number.
Viewing Users: Lists all users currently in the system.
Updating Users: Modifies user details based on user ID.
Deleting Users: Deletes a user from the system based on their user ID.


3. Order Management
File: Order_Management/Order_Management.c
Header: Order_Management/Order_Management.h

This module manages customer orders and provides functionalities to:

Add Orders: Records new customer orders, including the product name, price, discount, payment method, and status (e.g., pre-order, delivered, pending).
View Orders: Displays all orders made by customers.
Query Orders: Finds a specific order based on customer ID.
Update Order Status: Allows the staff to update the status of an order (e.g., pre-order to delivered).
Delete Orders: Removes an order from the system.


4. Payment Processing
File: PaymentProcessing/payment.c
Header: PaymentProcessing/payment.h

This module handles the payment processing of customer purchases, including:

User Record Retrieval: Retrieves details of a customer's previous purchase from the order file to confirm the transaction.
Discount Application: Applies any eligible discounts (e.g., loyalty discounts if a customer has purchased more than five items).
Full or Part Payment: Allows the customer to make either full or partial payments, with support for multiple payment methods (cash or card).
Saving Transactions: Saves transaction details to a file after payment is processed.


5. After-Sales Service
File: AfterSalesService/after_sales_service.c
Header: AfterSalesService/after_sales_service.h

This module provides support for after-sales services, such as:

Service Requests: Allows customers to create service requests by verifying if the product was sold to the customer, checking warranty status, and assigning a technician based on the issue reported.
Technician Assignment: Assigns a technician based on the problem description (e.g., hardware or software issues).
Warranty Check: Validates whether a product is still under warranty before creating a service request.
Saving Service Requests: Records service requests and assigned technicians in a file for future reference.


6. Sales Reports
File: SalesReport/Sales_Report.c
Header: SalesReport/Sales_Report.h

The sales report module provides the following functionality:

Monthly Sales Report Generation: Generates a detailed monthly sales report that includes total sales, total discounts, net revenue, completed orders, and returned orders.
Order Data Loading: Loads order data from the system and filters it by year and month to generate the report.
