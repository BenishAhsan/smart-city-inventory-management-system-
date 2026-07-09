//
// Created by Binash on 04/12/2025.
//
#include<iostream>
#include "template.h"
#include "src/Product/product.h"
#include "src/Order/order.h"
#include "src/Customer/customer.h"
#include "src/Product/ProductManager.h"
#include "src/Order/orderManager.h"
#include "src/Customer/customerManager.h"
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

void mainMenu();

void customerMenu();

void adminMenu();

void handleCustomerFlow();

void handleAdminFlow();

void clearInputBuffer();

string getStringInput(const string &prompt);

int getIntInput(const string &prompt);

double getDoubleInput(const string &prompt);

void showMainMenu() {
    cout << "\n========== STORE SYSTEM ==========" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Admin" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose role: ";
}

void showCustomerMenu() {
    cout << "\n------ CUSTOMER MENU ------" << endl;
    cout << "1. View all products" << endl;
    cout << "2. Search product by name" << endl;
    cout << "3. Sort products by price" << endl;
    cout << "4. Place order" << endl;
    cout << "5. View all orders" << endl;
    cout << "0. Back" << endl;
    cout << "Choice: ";
}

void showAdminMenu() {
    cout << "\n------ ADMIN MENU ------\n";
    cout << "1. Add product\n";
    cout << "2. Remove product\n";
    cout << "3. View all products\n";
    cout << "4. View all orders\n";
    cout << "0. Back\n";
    cout << "Choice: ";
}

ProductManager* productManager = nullptr;
OrderManager* orderManager = nullptr;
CustomerManager* customerManager = nullptr;

int main() {
    productManager = ProductManager::getInstance();
    orderManager = new OrderManager(productManager, "orders.json");
    customerManager = new CustomerManager();


    int roleChoice;
    bool exitProgram = false;

    do {
        mainMenu();

        if (!(cin >> roleChoice)) {
            cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (roleChoice) {
            case 1:
                handleCustomerFlow();
                break;

            case 2:
                handleAdminFlow();
                break;

            case 0:
                cout << "\nExiting system. Goodbye!\n";
                exitProgram = true;
                break;

            default:
                cout << "Invalid role selected. Please try again.\n";
        }

        cout << endl;

    } while (!exitProgram);

    if (productManager != nullptr) {
        delete productManager;
        productManager = nullptr;
    }

    return 0;
}


void clearInputBuffer() {
    cin.clear();
    // Use a large number instead of numeric_limits
    cin.ignore(10000, '\n');
}

string getStringInput(const string &prompt) {
    string input;
    cout << prompt;
    getline(cin, input);

    // Trim whitespace
    while (!input.empty() && (input.back() == ' ' || input.back() == '\t' || input.back() == '\n')) {
        input.pop_back();
    }
    while (!input.empty() && (input[0] == ' ' || input[0] == '\t' || input[0] == '\n')) {
        input.erase(0, 1);
    }

    return input;
}

int getIntInput(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid input. Please enter a valid integer.\n";
            clearInputBuffer();
        }
    }
}

double getDoubleInput(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid input. Please enter a valid number.\n";
            clearInputBuffer();
        }
    }
}

void handleCustomerFlow() {
    string customerName = getStringInput("Enter your name: ");
    string customerEmail = getStringInput("Enter your email: ");

    if (customerName.empty() || customerEmail.empty()) {
        cout << "Name cannot be empty. Returning to main menu.\n";
        return;
    }

    Customer c(customerName, customerEmail);
    customerManager->addCustomer(c);

    int choice;
    bool backToMain = false;

    do {
        customerMenu();
        choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                productManager->displayAllProducts();
                break;

            case 2: {
                string pname = getStringInput("Enter product name: ");

                if (pname.empty()) {
                    cout << "Product name cannot be empty.\n";
                    break;
                }

                // Temporary: Display all products for debugging
                cout << "\nAll products in inventory:\n";
                productManager->displayAllProducts();

                // Search for the product
                Product *p = productManager->searchProductByName(pname);

                if (p != NULL) {
                    cout << "\nFound product:\n";
                    cout << *p << endl;
                } else {
                    cout << "\nProduct not found.\n";
                    cout << "Note: Search is case-insensitive and partial match.\n";
                    cout << "Try: 'sam' for 'Samsung' or 'pho' for 'Phone'\n";
                }
                break;
            }

            case 3:
                productManager->sortByPrice();
                productManager->displayAllProducts();
                break;

            case 4: {
                string pname = getStringInput("Product name: ");

                if (pname.empty()) {
                    cout << "Product name cannot be empty.\n";
                    break;
                }

                int qty = getIntInput("Quantity: ");

                if (qty <= 0) {
                    cout << "Quantity must be positive.\n";
                    break;
                }

                Product *p = productManager->searchProductByName(pname);
                if (p == NULL) {
                    cout << "Product '" << pname << "' does not exist.\n";
                    break;
                }

                if (p->getStockQty() < qty) {
                    cout << "Insufficient stock. Only " << p->getStockQty() << " units available.\n";
                    break;
                }

                orderManager->createOrder(customerName, pname, qty);
                cout << "Order created successfully!\n";
                break;
            }

            case 5:
                orderManager->displayAllOrders();
                break;

            case 0:
                cout << "Returning to main menu\n";
                backToMain = true;
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << endl;

    } while (!backToMain);
}

void handleAdminFlow() {
    int choice;
    bool backToMain = false;

    do {
        adminMenu();
        choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1: {
                // getting user input
                int id = getIntInput("Product ID: ");
                string name = getStringInput("Product name: ");
                string category = getStringInput("Category: ");

                if (name.empty()) {
                    cout << "Product name cannot be empty." << endl;
                    break;
                }

                if (category.empty()) {
                    cout << "Category cannot empty" << endl;
                    break;
                }

                double price = getDoubleInput("Price: ");

                if (price < 0) {
                    cout << "Price cannot be negative.\n";
                    break;
                }

                int qty = getIntInput("Quantity: ");

                if (qty < 0) {
                    cout << "Quantity cannot be negative.\n";
                    break;
                }


                Product p(name, id, price, qty, category);
                productManager->addProduct(p);

                cout << "Product added successfully!\n";
                break;
            }

            case 2: {
                int id = getIntInput("Enter product ID to remove: ");

                string confirm = getStringInput("Are you sure? (yes/no): ");
                if (confirm == "yes" || confirm == "y") {
                    productManager->deleteProduct(id);
                    cout << "Product removed.\n";
                } else {
                    cout << "Removal cancelled.\n";
                }
                break;
            }

            case 3:
                productManager->displayAllProducts();
                break;

            case 4:
                orderManager->displayAllOrders();
                break;

            case 0:
                cout << "Returning to main menu\n";
                backToMain = true;
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << endl;

    } while (!backToMain);
}

void mainMenu() {
    cout << "========================================\n";
    cout << "       STORE MANAGEMENT SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Customer\n";
    cout << "2. Admin\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Select your role: ";
}

void customerMenu() {
    cout << "========================================\n";
    cout << "           CUSTOMER MENU\n";
    cout << "========================================\n";
    cout << "1. View All Products\n";
    cout << "2. Search Product by Name\n";
    cout << "3. View Products Sorted by Price\n";
    cout << "4. Place Order\n";
    cout << "5. View All Orders\n";
    cout << "0. Back to Main Menu\n";
    cout << "========================================\n";
}

void adminMenu() {
    cout << "========================================\n";
    cout << "            ADMIN MENU\n";
    cout << "========================================\n";
    cout << "1. Add New Product\n";
    cout << "2. Remove Product\n";
    cout << "3. View All Products\n";
    cout << "4. View All Orders\n";
    cout << "0. Back to Main Menu\n";
    cout << "========================================\n";
}