//
// Created by Binash on 14/12/2025.
//

#include "customerManager.h"
#include <iostream>

using namespace std;


CustomerManager::CustomerManager(): cTree(compareCustomers) {}

// add customer
void CustomerManager::addCustomer(const Customer& c) {
    if (!customerExists(c)) {
        cTree.insert(c);
    }
}

Customer* CustomerManager::findCustomer(const Customer& c) {
    return cTree.search(c);
}

bool CustomerManager::customerExists(const Customer& c) const {
    BST<Customer>* temp = const_cast<BST<Customer>*>(&cTree);
    return temp->search(c) != nullptr;
}

bool CustomerManager::removeCustomer(const Customer& c) {
    if (!customerExists(c)) return false;
    cTree.remove(c);
    return true;
}

void CustomerManager::showCustomers() const {
    cout << "\n=== CUSTOMERS LIST ===\n";
    cTree.printInOrder();
}

int CustomerManager::getCustomerCount() const {
    return cTree.getSize(); // if not available, you can remove this function
}
