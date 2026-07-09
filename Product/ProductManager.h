//
// Created by Binash on 14/12/2025.
//

#ifndef INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_PRODUCTMANAGER_H
#define INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_PRODUCTMANAGER_H

#include<iostream>
#include<fstream>
#include<string>
#include "../../template.h"
#include "product.h"
#include "../../json.hpp"

using json = nlohmann::json;
using namespace std;

// Class ProductManager
class ProductManager {
private:
    MyArray<Product> products;  // array for linear operations
    BST<Product> *tree;     // fast search

    static ProductManager *instance;

    // Private Constructor
    ProductManager();

public:
    // Singleton Access
    static ProductManager *getInstance();

    // Destructor for Singleton
    ~ProductManager();

    ProductManager(const ProductManager&) = delete;
    ProductManager& operator=(const ProductManager&) = delete;

    void loadProducts();
    void saveProducts();

    void addProduct(const Product& p);
    bool deleteProduct(int id);
    Product *searchProduct(int id);

    void sortByPrice();
    void sortByQuantity();

    // Display
    void displayAllProducts() const;

    // getters
    MyArray<Product>& getAll() { return products; }
    int getProductCount() const {
        return products.getSize();
    }

    // Search Product by name
    Product* searchProductByName(const string& name);

    bool updateProductQuantity(int id, int newQuantity);
    bool updateProductPrice(int id, double newPrice);
};


int compareProductByID(const Product& a, const Product& b);
int compareProductByName(const Product& a, const Product& b);
int compareProductByPrice(const Product& a, const Product& b);


#endif //INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_PRODUCTMANAGER_H
