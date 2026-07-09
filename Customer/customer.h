//
// Created by Binash on 13/12/2025.
//

#ifndef INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_CUSTOMER_H
#define INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_CUSTOMER_H

#include<iostream>
#include <string>

using namespace std;

class Customer {
private:
    string name;
    string phone;
    string email;
    int customer_id;
    std::string address;
public:
    // Default Constructor
    Customer();

    // Parameterized Constructors
    Customer(const string &name, const string &email);
    Customer(const string &name, const string& phone, const string& email, int customer_id, const string& address);

    // Getters
    string getName() const ;
    string getPhone() const;
    string getEmail() const;
    int getCustomerId() const;
    string getAddress() const;

    // Setters
    void setName(const string &name);
    void setPhone(const string &phone);
    void setEmail(const std::string& email);
    void setCustomerId(int id);
    void setAddress(const std::string& address);

    bool operator<(const Customer& other) const;
    bool operator==(const Customer& other) const;

    friend ostream& operator<<(ostream& os, const Customer& c);
};

int compareCustomers(const Customer& a, const Customer& b);


#endif //INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_CUSTOMER_H
