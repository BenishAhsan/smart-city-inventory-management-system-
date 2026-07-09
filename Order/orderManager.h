//
// Created by Binash on 14/12/2025.
//

#ifndef INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_ORDERMANAGER_H
#define INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_ORDERMANAGER_H

#include<iostream>
#include "order.h"
#include "../Product/ProductManager.h"
#include "../Product/product.h"
#include "../../template.h"
using namespace std;

class OrderManager{
private:
    BST<Order>* orderTree;

    ProductManager* productManager;
    string filename;
public:
    // Constructor
    OrderManager(ProductManager* pm, const string& file = "orders.json");
    // Destructor
    ~OrderManager();

    void saveToFile();
    void loadFromFile();

    bool createOrder(const string& customer, const string& product, int quantity);
    bool cancelOrder(const string& customer, const string& product);

    void displayAllOrders();

    // Search operations
    Order* findOrder(const string& customer, const string& product);
    bool orderExists(const string& customer, const string& product) const;

    bool exportToFile(const string& exportFile) const;

    void clearAllOrders();
    string getFilename() const;

};



#endif //INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_ORDERMANAGER_H
