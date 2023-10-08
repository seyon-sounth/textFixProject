#include "Cards.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

// maybe might not need void if other is considered free fnc.
void testCards(){

   Deck* d = new Deck();
   Hand* h = new Hand();
   
    
    for (int i = 0; i < 3; ++i) {
        h->takeCard(d->draw());
    }

    cout << "\nThe number of cards in your deck currently are:" << d->size() << std::endl;
    
    cout << "The number of cards in your hand currently are:" << h->size() << std::endl;

    cout << "\n"<<endl;
    
    for (auto *card : h->getCards())
    {
        card->play();
        d->addCardToDeck(card);
        h->removeCard(card);
    }
    
    cout << "\nThe number of cards in your deck currently updated after are:" << d->size() << std::endl;
    
    cout << "The number of cards in your hand currently updated after are:" << h->size() << std::endl;

    cout << "\n"<<endl;

    cout << "\nthis is to test playallhand method "<<endl;

    Deck* d2 = new Deck();
    Hand* h2 = new Hand();
    for (int x = 0; x < 4; ++x) {
        h2->takeCard(d2->draw());
    }

    
    cout << "\nThe number of cards in your deck currently are:" << d2->size() << std::endl;
    
    cout << "The number of cards in your hand currently are:" << h2->size() << std::endl;

     cout << "\n"<<endl;

    
        for (auto *card : h2->getCards())
    {
        card->playAllHand();
        d2->addCardToDeck(card);
        h2->removeCard(card);
    }

    cout << "\nThe number of cards in your deck currently updated after are:" << d2->size() << std::endl;
    
    cout << "The number of cards in your hand currently updated after are:" << h2->size() << std::endl;

    cout << "\n"<<endl;



}

int main() {
    
    testCards();
    return 0;
};