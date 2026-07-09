//
// Created by Binash on 14/12/2025.
//

#ifndef INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_CUSTOMERMANAGER_H
#define INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_CUSTOMERMANAGER_H

#include "customer.h"
#include "../../template.h"

class CustomerManager {
private:
    BST<Customer> cTree;
public:
    CustomerManager();

    // Core operations
    void addCustomer(const Customer& c);
    Customer* findCustomer(const Customer& c);
    bool customerExists(const Customer& c) const;
    bool removeCustomer(const Customer& c);

    // Utility
    void showCustomers() const;
    int getCustomerCount() const;
};


#endif //INC_2025_FALL_ITULAHORE_DSA_SE200T_PROJECT_2025_FALL_GROUP_J_CUSTOMERMANAGER_H
