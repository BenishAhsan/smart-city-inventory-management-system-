//
// Created by Binash on 04/12/2025.
//
#include<iostream>
#include"product.h"
#include <string>

using namespace std;

Product::Product(string name, int product_id, double price, int stock_quantity, string category){
    this->name = name;
    this->product_id = product_id;
    this->price = price;
    this->stock_quantity = stock_quantity;
    this->category = category;
}

//getters
int Product::getProductID() const {
    return product_id;
}

string Product::getName() const { return name; }

double Product::getPrice() const { return price; }

int Product::getStockQty() const { return stock_quantity; }

string Product::getCategory() const {
    return category;
}

// Setters
void Product::setName(const string &n) { name = n; }

void Product::setProductId(int id) { product_id = id; }

void Product::setPrice(double price) {
    if(price >= 0 ){
        this->price = price;
    }

}

void Product::setQuantity(int q) {
    if(q>= 0){
        stock_quantity = q;
    }
}

void Product::setCategory(const string &category) {
    this->category = category;
}

// overload operator for generic structures
bool Product::operator>(const Product &other) const {
    return name > other.name;
}

bool Product::operator<(const Product &other) const {
    return name < other.name;
}

std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << "ID: " << p.product_id
       << " | Name: " << p.name
       << " | Price: Rs." << p.price
       << " | Stock: " << p.stock_quantity
       << " | Category: " << p.category;
    return os;
}