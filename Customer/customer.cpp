//
// Created by Binash on 13/12/2025.
//
#include <iostream>
#include "customer.h"

using namespace std;

// Constructor
Customer::Customer() : name(""), phone(""), email(""), customer_id(0), address("") {}

Customer::Customer(const string &name, const string &email) : name(name), phone(""), email(email),
                                                              customer_id(0), address("") {}

Customer::Customer(const string &name, const string &phone, const string &email, int customer_id,
                   const string &address) : name(name), phone(phone), email(email), customer_id(customer_id),
                                            address(address) {}

// Getters
string Customer::getName() const { return name; }

string Customer::getPhone() const { return phone; }

string Customer::getEmail() const { return email; }

int Customer::getCustomerId() const { return customer_id; }

string Customer::getAddress() const { return address; }

// Setters
void Customer::setName(const string &name) {
    this->name = name;
}

void Customer::setPhone(const string &phone) {
    this->phone = phone;
}

void Customer::setEmail(const string &email) {
    this->email = email;
}

void Customer::setCustomerId(int id) {
    customer_id = id;
}

void Customer::setAddress(const string &address) {
    this->address = address;
}

bool Customer::operator<(const Customer &other) const {
    return name < other.name;
}

bool Customer::operator==(const Customer &other) const {
    if (customer_id != 0 && other.customer_id != 0) {
        return customer_id == other.customer_id;
    }
    return name == other.name && phone == other.phone;
}

ostream &operator<<(ostream &os, const Customer &c) {
    os << "Customer ID: " << c.customer_id << " | Name: " << c.name << " | Phone: " << c.phone;

    if (!c.email.empty()) {
        os << " | Email: " << c.email;
    }

    if (!c.address.empty()) {
        os << " | Address: " << c.address;
    }

    return os;
}

int compareCustomers(const Customer& a, const Customer& b) {
    if (a.getCustomerId() < b.getCustomerId()) return -1;
    if (a.getCustomerId() > b.getCustomerId()) return 1;
    return 0;
}