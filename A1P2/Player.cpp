#include "Player.h"
#include "../A1P1/Map.h"
#include "../A1P3/Orders.h"

// Default Constructor
Player::Player() {
//    // Initialize an empty list of territories the player owns
//    ownedTerritories = {};
    // Allocate memory for a new empty orders list for the player
    ordersList = new OrdersList();
    // Allocate memory for a new empty hand of cards for the player
    hand = new Hand();
}

// Parametrized Constructor
Player::Player(Hand* initialHand, vector<Territory*> &initialTerritories) {
    // Assign the provided hand to the player
    hand = initialHand;
    // Assign the provided territories to the player
    ownedTerritories = initialTerritories;
    // Allocate memory for a new empty orders list for the player
    ordersList = new OrdersList();
}

// Copy Constructor
Player::Player(Player& player) {
    // Deep copy the hand of cards from the provided player
    hand = new Hand(*(player.hand));
    // Deep copy the orders list from the provided player
    ordersList = new OrdersList(*(player.ordersList));
    // Shallow copy the territories since territories are shared among players
    ownedTerritories = player.ownedTerritories;
}

// Destructor
Player::~Player() {
    // Deallocate memory for the player's hand of cards
    delete hand;
    // Deallocate memory for the player's orders list
    delete ordersList;
}

// Method to retrieve the player's hand of cards
Hand* Player::getHand() {
    return hand;
}

// Method to retrieve the list of territories the player owns
vector<Territory*> Player::getOwnedTerritories() {
    return ownedTerritories;
}

// Method to retrieve the player's list of orders
OrdersList* Player::getOrdersList() {
    return ordersList;
}

// Method to determine which territories the player should defend
vector<Territory*> Player::toDefend() {
    // For now, return all owned territories as territories to defend
    return ownedTerritories;
}

// Method to determine which territories the player should attack
//vector<Territory*> Player::toAttack() {
//    // For now, return an empty list as territories to attack
//    return {};
//}

vector<Territory*> Player::toAttack() {
    return vector<Territory*>();
}

// Method for the player to issue an order
void Player::issueOrder() {
    // For now, create a new generic order
    Order* newOrder = new Order();
    // Add the new order to the player's list of orders
    ordersList->add(*newOrder);
}

// Overloaded assignment operator for the player class
void Player::operator=(Player& player) {
    // Ensure we're not assigning to the same object
    if (this != &player) {
        // Deallocate memory for the current hand and orders list
        delete hand;
        delete ordersList;

        // Deep copy the hand and orders list from the provided player
        hand = new Hand(*(player.hand));
        ordersList = new OrdersList(*(player.ordersList));
        // Shallow copy the territories
        ownedTerritories = player.ownedTerritories;
    }
}

// Overloaded stream insertion operator for printing a player's details
std::ostream& operator<<(std::ostream &out, const Player &p) {
    out << "Player owns territories: ";
    // Loop through and print each territory the player owns
    for (auto t : p.ownedTerritories) {
        out << t->getName() << ", ";  // Assuming Territory has a getName() method
    }
    // Print the player's hand of cards and orders list
    out << "\nHand: " << *(p.hand);  // Assuming Hand has an overloaded stream insertion operator
    out << "\nOrders: " << *(p.ordersList);  // Assuming OrdersList has an overloaded stream insertion operator
    return out;
}

//function to add cards to deck using push_back
void Player::addCardToHand(Card *c)
{
    hand->takeCard(c);
}