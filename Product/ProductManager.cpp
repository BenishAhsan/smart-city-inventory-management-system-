//
// Created by Binash on 14/12/2025.
//
#include<iostream>
#include<fstream>
#include<string>
#include "ProductManager.h"
#include "../../template.h"
#include "../../json.hpp"
#include <cctype>

using json = nlohmann::json;


string toLowercase(const string& str);

ProductManager *ProductManager::instance = nullptr;


// Comparison functions implementation
int compareProductByID(const Product &a, const Product &b) {
    if (a.getProductID() < b.getProductID()) return -1;
    if (a.getProductID() > b.getProductID()) return 1;
    return 0;
}

int compareProductByName(const Product &a, const Product &b) {
    if (a.getName() < b.getName()) return -1;
    if (a.getName() > b.getName()) return 1;
    return 0;
}

int compareProductByPrice(const Product &a, const Product &b) {
    if (a.getPrice() < b.getPrice()) return -1;
    if (a.getPrice() > b.getPrice()) return 1;
    return 0;
}

// Constructor
ProductManager::ProductManager() {
    // BST with ID comparison function
    tree = new BST<Product>(compareProductByID);
    loadProducts();
}

// Destructor
ProductManager::~ProductManager() {
    if(tree) {
        delete tree;
        tree = nullptr;
    }
}

// Singleton access
ProductManager *ProductManager::getInstance() {
    if (!instance) {
        instance = new ProductManager();
    }
    return instance;
}

// load products from file
void ProductManager::loadProducts() {
    cout << "DEBUG: Loading products.json from runtime directory\n";
    ifstream file("products.json");

    if (!file.is_open()) {
        cout << "No existing products file found." << endl;
        return;
    }

    json data;
    file >> data;
    file.close();

    if (!data.contains("products")) {
        cout << "Invalid products file format." << endl;
        return;
    }

    int n = 0;

    for (auto& item : data["products"]) {
        Product p;
        p.setName(item["name"]);
        p.setProductId(item["id"]);
        p.setPrice(item["price"]);
        p.setQuantity(item["quantity"]);
        p.setCategory(item["category"]);

        products.insert(p);   // your custom array
        tree->insert(p);      // BST
        n++;
    }

    cout << "Loaded " << n << " products." << endl;

}

// Save products to file
void ProductManager::saveProducts() {
    json data;
    data["products"] = json::array();

    int n = products.getSize();
    for (int i = 0; i < n; ++i) {
        Product& p = products[i];
        json productJson;
        productJson["name"] = p.getName();
        productJson["id"] = p.getProductID();
        productJson["price"] = p.getPrice();
        productJson["quantity"] = p.getStockQty();
        productJson["category"] = p.getCategory();

        data["products"].push_back(productJson);
    }

    // Save to file
    ofstream file("products.json");
    if (file.is_open()) {
        file << data.dump(4);  // Pretty print with indentation
        file.close();
        cout << "Products saved successfully (" << n << " products)." << endl;
    } else {
        cout << "Error saving products to file." << endl;
    }
}

void ProductManager::addProduct(const Product& p) {
    // Check if product with same ID already exists
    if (searchProduct(p.getProductID()) != nullptr) {
        cout << "Product with ID " << p.getProductID() << " already exists!" << endl;
        return;
    }

    // Add to array
    products.insert(p);

    // Add to BST
    tree->insert(p);

    // Save changes
    saveProducts();

    cout << "Product added: " << p.getName()
         << " (ID: " << p.getProductID()
         << ", Price: Rs." << p.getPrice() << ")" << endl;
}

bool ProductManager::deleteProduct(int id) {
    int idx = -1;
    int n = products.getSize();

    for (int i = 0; i < n; ++i) {
        if (products[i].getProductID() == id) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        cout << "Product with ID " << id << " not found." << endl;
        return false;
    }

    // Remove from array
    products.remove_at(idx);

    // Rebuild BST safely
    delete tree;
    tree = new BST<Product>(compareProductByID);

    for (int i = 0; i < products.getSize(); ++i) {
        tree->insert(products[i]);
    }

    saveProducts();
    cout << "Product with ID " << id << " deleted successfully." << endl;
    return true;

}

Product *ProductManager::searchProduct(int id) {
    Product searchKey;
    searchKey.setProductId(id);

    return tree->search(searchKey);
}


//helper function
string toLowercase(const string& str) {
    string result = str;
    for (char &c : result) {
        c = tolower(c);
    }
    return result;
}

// Search product by name (linear search)
Product* ProductManager::searchProductByName(const string& name) {
    string searchName = toLowercase(name);
    int n = products.getSize();

    for (int i = 0; i < n; ++i) {
        string productName = toLowercase(products[i].getName());

        if (productName.find(searchName) != string::npos) {
            return &products[i];
        }
    }
    return nullptr;
}

// selection sort by price
void ProductManager::sortByPrice() {
    int n = products.getSize();

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (products[j].getPrice() < products[minIdx].getPrice()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            // Swap products
            Product temp = products[i];
            products[i] = products[minIdx];
            products[minIdx] = temp;
        }
    }

    // Rebuild BST (since sorting changes order)
    delete tree;
    tree = new BST<Product>(compareProductByID);

    for (int i = 0; i < n; ++i) {
        tree->insert(products[i]);
    }
    saveProducts();
    cout << "Products sorted by price." << endl;
}

// insertion sort by quantity
void ProductManager::sortByQuantity() {
    int n = products.getSize();

    for (int i = 1; i < n; ++i) {
        Product key = products[i];
        int j = i - 1;

        while (j >= 0 && products[j].getStockQty() > key.getStockQty()) {
            products[j + 1] = products[j];
            --j;
        }
        products[j + 1] = key;
    }

    // Rebuild BST (since sorting changes order)
    delete tree;
    tree = new BST<Product>(compareProductByID);

    for (int i = 0; i < n; ++i) {
        tree->insert(products[i]);
    }

    saveProducts();
    cout << "Products sorted by quantity." << endl;
}

// Display all products
void ProductManager::displayAllProducts() const {
    int n = products.getSize();

    cout << "\n=== PRODUCT INVENTORY (" << n << " products) ===" << endl;

    if (n == 0) {
        cout << "No products available." << endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        cout << i + 1 << ". " << products[i] << endl;
    }
}

// Update product quantity
bool ProductManager::updateProductQuantity(int id, int newQuantity) {
    if (newQuantity < 0) return false;

    // Update array
    int n = products.getSize();
    for (int i = 0; i < n; ++i) {
        if (products[i].getProductID() == id) {
            products[i].setQuantity(newQuantity);
            break;
        }
    }

    // Update BST
    Product* product = searchProduct(id);
    if (product) {
        product->setQuantity(newQuantity);
        saveProducts();
        return true;
    }

    return false;
}

// Update product price
bool ProductManager::updateProductPrice(int id, double newPrice) {
    if (newPrice < 0) return false;

    bool updated = false;

    // Update in array
    int n = products.getSize();
    for (int i = 0; i < n; ++i) {
        if (products[i].getProductID() == id) {
            products[i].setPrice(newPrice);
            updated = true;
            break;
        }
    }

    // Update in BST
    Product* product = searchProduct(id);
    if (product) {
        product->setPrice(newPrice);
        updated = true;
    }

    if (updated) {
        saveProducts();
        cout << "Price updated for product ID " << id
             << ": Rs." << newPrice << endl;
        return true;
    }

    cout << "Failed to update price for product ID " << id << endl;
    return false;
}

