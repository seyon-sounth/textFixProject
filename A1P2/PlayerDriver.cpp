#include "Player.h"
#include "../A1P4/Cards.h"
#include "../A1P1/Map.h"
#include <iostream>
#include <vector>
#include <initializer_list>

// A free function to demonstrate the functionality of the Player class
void testPlayers() {
    cout << "===== Testing Player functionality =====" << endl;

    // Create a deck and hand for demonstration purposes
    Deck* deck = new Deck();
    Hand* hand = new Hand();

    // Draw a few cards from the deck to the hand
    for (int i = 0; i < 5; i++) {
        hand->takeCard(deck->draw());
    }

    // Create territories for demonstration purposes
    Territory t1(1,1,"Territory1"), t2(1,1,"Territory2");// From Map class: explicit Territory(int id, int continentId, string name);


    vector<Territory*> territories;
    territories.push_back(&t1);
    territories.push_back(&t2);

    // Create a player with the hand and territories
    Player player(hand, territories);

    // Display the player's initial state
    cout << player << endl;

    // Display territories to defend and attack (arbitrary for now)
    cout << "Territories to defend: " << player.toDefend().size() << endl;
    cout << "Territories to attack: " << player.toAttack().size() << endl;

    // Issue an order
    player.issueOrder();

    // Display the player's state after issuing an order
    cout << player << endl;

    // Clean up
    delete deck;
    delete hand;

    cout << "===== End of Player testing =====" << endl;
}

// Main function to run the test
int main() {
    testPlayers();
    return 0;
}
