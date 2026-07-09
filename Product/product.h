//
// Created by Binash on 04/12/2025.
//

#ifndef INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_PRODUCT_H
#define INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_PRODUCT_H

#include<iostream>
#include <string>
using namespace std;

// ____ Product class ___
class Product {
private:
    string name;
    int product_id;
    double price;
    int stock_quantity;
    string category;
public:
    // Default Constructor
    Product(): name(""), product_id(0), price(0.0), stock_quantity(0), category(""){}

    // Parameterized constructor
    Product(string name, int product_id, double price, int stock_quantity, string category);

    //getters
    int getProductID() const;
    string getName() const;
    double getPrice() const;
    int getStockQty() const;
    string getCategory() const;

    // Setters
    void setName(const string& n);
    void setProductId(int id);
    void setPrice(double price);
    void setQuantity(int q);
    void setCategory(const string& category);


    // overload operator for generic structures
    bool operator>(const Product &other) const;

    bool operator<(const Product &other) const;

    friend std::ostream& operator<<(std::ostream& os, const Product& p);
};


#endif //INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_PRODUCT_H
