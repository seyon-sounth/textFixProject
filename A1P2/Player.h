// Ensure the header file is included only once to avoid multiple definitions
#pragma once

// Include necessary header files
#include "../A1P4/Cards.h"
#include "../A1P3/Orders.h"
#include "../A1P1/Map.h"

// Use the standard namespace for simplification
using namespace std;

// Define the Player class
class Player {
private:
    // Data members representing territories owned by the player
    vector<Territory *> ownedTerritories;

    OrdersList* ordersList;
    // Pointer to the hand of cards owned by the player
    Hand* hand;

public:
    // Default constructor declaration
    Player();

    // Parametrized constructor declaration
    // Takes an initial hand and a list of territories as parameters
    Player(Hand* initialHand, vector<Territory*> &initialTerritories);

    // Copy constructor declaration
    Player(Player& player);

    // Destructor declaration
    ~Player();

    // Getter for the player's hand of cards
    Hand* getHand();

    // Getter for the territories owned by the player
    vector<Territory*> getOwnedTerritories();

    // Getter for the player's list of orders
    OrdersList* getOrdersList();

    // Method to determine territories the player wants to defend
    vector<Territory*> toDefend();

    // Method to determine territories the player wants to attack
    vector<Territory*> toAttack();

    // Method for the player to issue a new order
    void issueOrder();

    // Overloaded assignment operator declaration
    void operator=(Player& player);

    // Overloaded stream insertion operator declaration
    // Allows for easy printing of player details
    friend std::ostream& operator<<(std::ostream &out, const Player &p);

    void addCardToHand(Card* c);
};
