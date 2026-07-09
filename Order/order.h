//
// Created by Binash on 13/12/2025.
//

#ifndef INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_ORDER_H
#define INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_ORDER_H

#include <iostream>
#include <string>

using namespace std;

class Order {
private:
    string customer_name;
    string product_name;
    int quantity;
    double total;
public:
    // Constructors
    Order() {
        customer_name = "";
        product_name = "";
        quantity = 0;
        total = 0.0;
    }

    Order(string cname, string pname, int q, double t);

    // getters
    string getCustomerName() const;

    string getProductName() const;

    int getQuantity() const;

    double getTotal() const;

    // Setters
    void setCustomerName(const string &name);

    void setProductName(const string &name);

    void setQuantity(int q);

    void setTotal(double t);

    // Comparison operators
    bool operator<(const Order &other) const;

    bool operator==(const Order &other) const;

    // Friend output operator
    friend std::ostream &operator<<(std::ostream &os, const Order &o);
};


#endif //INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_ORDER_H
