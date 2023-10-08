#include <string>
#include <vector> 
#include <typeinfo>
#include <iostream>

class Order{
    public:
    bool validate(){
        // Placeholder functionality
        return true;
    }
    
    bool execute(){
        // Placeholder functionality
        return true;
    }
};

class OrdersList{
    std::vector<Order> list;
    public:
    void add(Order order){
        list.push_back(order);
    }

    void move(std::string order, int priority){
        for(int i = 0; i < list.size(); ++i) {
            if(typeid(list[i]).name() == order){
                list.insert(list.begin() + priority, list[i]);
                list.erase(list.begin() + i);
            }
        }
    }

    void remove(std::string order){
        for(int i = 0; i < list.size(); ++i) {
            if(typeid(list[i]).name() == order)
                list.erase(list.begin() + i);
        }
    }
    // Add a friend function to overload the stream insertion operator
    friend std::ostream& operator<<(std::ostream &out, const OrdersList &ordersList);
};

// Define how to print an OrdersList object
std::ostream& operator<<(std::ostream &out, const OrdersList &ordersList) {
    out << "OrdersList with " << ordersList.list.size() << " orders.";
    // Add any other details as needed
    return out;
}


class deploy: public Order{
    public:
    deploy();
};

class advance: public Order{
    public:
    advance();
};

class bomb: public Order{
    public:
    bomb();
};

class blockade: public Order{
    public:
    blockade();
};

class airlift: public Order{
    public:
    airlift();
};

class negotiate: public Order{
    public:
    negotiate();
};