//
// Created by Binash on 13/12/2025.
//
#include <iostream>
#include <string>
#include "order.h"

using namespace std;

// Default Constructors

// Parameterized Constructor
Order::Order(string cname, string pname, int q, double t) {
    customer_name = cname;
    product_name = pname;
    quantity = q;
    total = t;
}

// getters
string Order::getCustomerName() const {
    return customer_name;
}

string Order::getProductName() const { return product_name; }

int Order::getQuantity() const { return quantity; }

double Order::getTotal() const { return total; }


// setters
void Order::setCustomerName(const string &cname){
    customer_name = cname;
}

void Order::setProductName(const string &pname){
    product_name = pname;
}

void Order::setQuantity(int q){
    quantity = q;
}

void Order::setTotal(double t){
    total = t;
}

// Comparison operators
bool Order::operator<(const Order &other) const{
    return customer_name < other.customer_name;
}

bool Order::operator==(const Order &other) const{
    return customer_name == other.customer_name && product_name == other.product_name;
}

ostream& operator<<(std::ostream& os, const Order& o) {
    os << o.customer_name << " ordered " << o.product_name
       << " x" << o.quantity << " | Total: Rs." << o.total;
    return os;
}
