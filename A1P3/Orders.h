#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Order {
public:
    string type;
    bool validate();
    bool execute();
};

class OrdersList {
public:
    vector<Order> list;
    void add(Order order);
    void move(string order, int priority);
    void remove(string order);
    void iterate();

    friend std::ostream& operator<<(std::ostream &out, const OrdersList &ordersList);
};

// Define the operator<< for OrdersList outside the class
std::ostream& operator<<(std::ostream &out, const OrdersList &ordersList) {
    out << "Orders List: ";
    // You can iterate through the orders in the ordersList and print them here.
    // For example:
    // for (const Order& order : ordersList.list) {
    //     out << order.type << ", "; // Print the type of order for simplicity
    // }
    return out;
}

class Deploy : public Order {
public:
    Deploy();
};

class Advance : public Order {
public:
    Advance();
};

class Bomb : public Order {
public:
    Bomb();
};

class Blockade : public Order {
public:
    Blockade();
};

class Airlift : public Order {
public:
    Airlift();
};

class Negotiate : public Order {
public:
    Negotiate();
};
