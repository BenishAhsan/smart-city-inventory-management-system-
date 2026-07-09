# Smart City Inventory Management System

A robust backend inventory and order management module built in **C++**. This project demonstrates core **Data Structures & Algorithms (DSA)** and **Object-Oriented Programming (OOP)** concepts by implementing custom data structures instead of relying on STL containers such as `std::vector` or `std::map`.

---

## 🚀 Features

- **Inventory Management**
  - Add, update, delete, and search products
  - Automatic stock updates
  - Persistent storage using JSON

- **Order Processing**
  - Create and manage customer orders
  - Support for multiple products per order
  - Order tracking and cancellation

- **Customer Management**
  - Store customer information efficiently
  - Maintain relationships between customers and their orders

- **JSON Persistence**
  - Save and load application data using the `nlohmann/json` library
  - File-based storage for reliable data recovery

---

## 🛠️ Data Structures & Algorithms

### Custom Data Structures

- **Binary Search Tree (BST)**
  - Used in `CustomerManager` and `OrderManager` for hierarchical data storage and efficient record retrieval.

- **Custom Dynamic Array (`MyArray`)**
  - Implemented from scratch with manual memory management, resizing, and element access.

### Searching

- **BST Search**
  - Average time complexity: **O(log N)**

- **Linear Search**
  - Used for product lookup by name and other sequential operations.
  - Time complexity: **O(N)**

### Sorting Algorithms

- **Selection Sort**
  - Sort products by price.

- **Insertion Sort**
  - Sort products by available stock.

### Design Pattern

- **Singleton Pattern**
  - Implemented in `ProductManager` to ensure a single shared instance manages the inventory.

---

## 📂 Project Structure

```text
├── Customer/
│   ├── customer.h
│   ├── customer.cpp
│   ├── customerManager.h
│   └── customerManager.cpp
│
├── Order/
│   ├── order.h
│   ├── order.cpp
│   ├── orderManager.h
│   └── orderManager.cpp
│
├── Product/
│   ├── product.h
│   ├── product.cpp
│   ├── ProductManager.h
│   └── ProductManager.cpp
│
├── template.h
└── README.md
```

---

## 💻 Tech Stack

- **Language:** C++
- **JSON Library:** `nlohmann/json`
- **Programming Concepts:**
  - Object-Oriented Programming (OOP)
  - Generic Programming (Templates)
  - Manual Memory Management (`new` / `delete`)
  - File Handling

---

## 🔧 How to Run

### 1. Clone the repository

```bash
git clone https://github.com/BenishAhsan/smart-city-inventory-management-system.git
```

### 2. Navigate to the project directory

```bash
cd smart-city-inventory
```

### 3. Compile the project

Use your preferred IDE (CLion, Visual Studio, VS Code) or compile from the terminal with a C++ compiler.

### 4. Run the executable

Launch the generated executable to interact with the console-based inventory management system.

---

## 📚 Concepts Demonstrated

- Binary Search Trees
- Dynamic Arrays
- Sorting Algorithms
- Searching Algorithms
- Templates
- Singleton Design Pattern
- File Handling
- JSON Serialization
- Object-Oriented Programming
