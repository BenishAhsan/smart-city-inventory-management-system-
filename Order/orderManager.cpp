//
// Created by Binash on 14/12/2025.
//
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "orderManager.h"
#include "../../json.hpp"

using json = nlohmann::json;

using namespace std;

int compareOrdersByCustomer(const Order &a, const Order &b) {
    if (a.getCustomerName() < b.getCustomerName())
        return -1;

    if (a.getCustomerName() > b.getCustomerName())
        return 1;

    if (a.getProductName() < b.getProductName())
        return -1;

    if (a.getProductName() > b.getProductName())
        return 1;

    return 0;
}

OrderManager::OrderManager(ProductManager *pm, const string &file)
        : productManager(pm), filename(file) {
    orderTree = new BST<Order>(compareOrdersByCustomer);
    loadFromFile();
}

// Destructor
OrderManager::~OrderManager() {
    saveToFile();
    delete orderTree;
}

// load data from file
void OrderManager::loadFromFile() {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No existing orders file found.\n";
        return;
    }

    json data;
    file >> data;
    file.close();

    if (!data.contains("orders")) return;

    for (auto &item: data["orders"]) {
        Order o(
                item["customer"],
                item["product"],
                item["quantity"],
                item["total"]
        );
        orderTree->insert(o);
    }

    cout << "Orders loaded from file.\n";
}

// save orders to file
void OrderManager::saveToFile() {
    json data;
    data["orders"] = json::array();

    // NOTE: using BST print-style traversal (NO lambdas)
    orderTree->storeInOrder(data["orders"]);

    ofstream file(filename);
    file << data.dump(4);
    file.close();

    cout << "Orders saved.\n";
}

// create order
bool OrderManager::createOrder(const string &customer, const string &product, int quantity) {
    if (quantity <= 0) {
        return false;
    }
    Product *p = productManager->searchProductByName(product);
    if (!p || p->getStockQty() < quantity)
        return false;

    productManager->updateProductQuantity(
            p->getProductID(),
            p->getStockQty() - quantity
    );

    Order o(customer, product, quantity, quantity * p->getPrice());
    orderTree->insert(o);
    saveToFile();

    cout << "Order placed.\n";
    return true;
}

// cancel order
bool OrderManager::cancelOrder(const string &customer, const string &product) {
    Order key(customer, product, 0, 0.0);
    Order *found = orderTree->search(key);

    if (!found) {
        return false;
    }

    Product *p = productManager->searchProductByName(product);
    if (p) {
        productManager->updateProductQuantity(
                p->getProductID(),
                p->getStockQty() + found->getQuantity()
        );
    }
    orderTree->remove(key);
    saveToFile();

    cout << " Order cancelled.\n";
    return true;
}

// Display
void OrderManager::displayAllOrders() {
    cout << "\nALL ORDERS\n";
    orderTree->printInOrder();
}

// ---------------- FIND ----------------
Order *OrderManager::findOrder(const string &customer, const string &product) {
    Order key(customer, product, 0, 0.0);
    return orderTree->search(key);
}

// ---------------- EXPORT ----------------
bool OrderManager::exportToFile(const string &exportFile) const {
    json data;
    data["orders"] = json::array();

    orderTree->storeInOrder(data["orders"]);

    ofstream file(exportFile);
    if (!file.is_open()) return false;

    file << data.dump(4);
    file.close();

    cout << "Orders exported.\n";
    return true;
}