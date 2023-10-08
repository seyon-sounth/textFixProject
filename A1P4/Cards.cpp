#include "Cards.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>
using namespace std;

//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------These are Deck class related implementations ---------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//

// This is a default constructor for Deck including initialization of the deck
//using srand to initialize random number generators.
Deck::Deck()
{
    // Defining initial values for the Cardstype to be used in the deck.
    //using push_back() to add a new element.
    cards.push_back(new Card(CardsType::BOMB));
    cards.push_back(new Card(CardsType::REINFORCEMENT));
    cards.push_back(new Card(CardsType::BLOCKADE));
    cards.push_back(new Card(CardsType::AIRLIFT));
    cards.push_back(new Card(CardsType::DIPLOMACY));

    // The following is to initialize and then randomize the cards.
    srand((unsigned)time(NULL));
    // inmported from <algorithm> to randomize the deck
    random_shuffle(cards.begin(),cards.end());
}

// This is the a parameterized constructor for Deck including initialization of the deck and max size.
Deck::Deck(size_t maxSize) : maxSize(maxSize)
{
    // Defining initial values for the Cardstype to be used in the deck.
    //using push_back() to add a new element.
    cards.push_back(new Card(CardsType::BOMB));
    cards.push_back(new Card(CardsType::REINFORCEMENT));
    cards.push_back(new Card(CardsType::BLOCKADE));
    cards.push_back(new Card(CardsType::AIRLIFT));
    cards.push_back(new Card(CardsType::DIPLOMACY));

    // The following is to initialize and then randomize the cards.
    srand((unsigned)time(NULL));
    // inmported random shuffle from <algorithm> to mix the deck
    random_shuffle(cards.begin(),cards.end());
}

// destructor to deallocate memory/cleanup and prevent memory leaks
Deck::~Deck()
{
   //This loop iterate through cards and deletes the current elements using back()
   //to return the ref to last element and pop to remove the element
   while (!cards.empty()) {
   delete cards.back();
   cards.pop_back();
 }
};

//This is the copy constructor for deck using copy as variable and for looping through
//the Card vector and then using push_back() function for each card to add a new element at its end
Deck::Deck(const Deck &copy)
{
    for (const Card *c:copy.cards)
    {
        cards.push_back(new Card(*c));
    }
}

// The assingment operator as asked in the instructionss to initialize one object using another object for deck
Deck &Deck::operator=(const Deck &assign)
{
    if (this!=&assign)
    {
        // This loop iterate through cards and deletes the current elements using back()
        //to return the ref to last element and pop to remove the element
         while (!cards.empty()) {
            delete cards.back();
            cards.pop_back();
        }
        // Similar to the copy constructor to initialize by copying the existing one
        for (const Card *c:assign.cards)
        {
            cards.push_back(new Card(*c));
        }
    }
    return *this;
}

// this is the draw method to draw cards from the deck, we first check the deck
//if there are cards in there, then we reference the last card to then remove and it will be added to the hand
Card *Deck::draw()
{
    if (!cards.empty())
    {
        // .back returns the reference to the last element of the vector.
        Card *cardsdrew = cards.back();

        // pop_back is used remove elements from a vector from the back
        cards.pop_back();

        return cardsdrew;
    }
    else
    {
        cout << "\nAll of the draws have been done !. ";
        cout << "\n";
        return nullptr;
    }

    return nullptr;
}

// returning the size of the deck using size() built in function
size_t Deck::size() const
{
    return cards.size();
}

//function to add cards to deck using push_back
void Deck::addCardToDeck(Card *c)
{
    cards.push_back(c);
}

//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------These are Cards class related implementations---------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//

// This is the default constructor for Cards class
Card::Card()
{
    string CardsType = "this will be a default type";
}

// This is the parameterized constructor for Cards class, we must use this specific
// bc of memeber initializing and working with constants which are the enums
Card::Card(CardsType t) : t(t) {}

// Ths is the copy constructor for Cards
Card::Card(const Card &copy) : t(copy.t) {}

// destructor to deallocate memory/cleanup and prevent memo leaks.
Card::~Card()
{
    Card* c = new Card();
    delete c; 
}

// The assingment operator as asked in the instructionss to assign a card type
Card &Card::operator=(const Card &assign)
{
    if (this != &assign){
         t = assign.t;}
    return *this;
}

// Enum conversion to Strings for each CardsType to manipulate in vector
string Card::stringConversion() const
{
    switch (t)
    {
    case CardsType::BOMB:
        return "BOMB";

    case CardsType::REINFORCEMENT:
        return "REINFORCEMENT";

    case CardsType::BLOCKADE:
        return "BLOCKADE";

    case CardsType::AIRLIFT:
        return "AIRLIFT";

    case CardsType::DIPLOMACY:
        return "DIPLOMACY";

    default:
        return "TYPE DNE";
    }
}

// this is an stream insertion operator as requested to access private members and output the card
ostream &operator<<(ostream &out, const Card &c)
{
    out << c.stringConversion();
    return out;
}

// This is the play method in Card where you can use a card
// and after used it is sent back to the deck this is done in the compiler.
void Card::play()
{
    switch (t)
    {
    case CardsType::BOMB:
        cout << "The BOMB card has been played ! it goes BOOOOOMMMMMM." << endl;
        break;
    case CardsType::REINFORCEMENT:
        cout << "The REINFORCEMENT card has been played, rally the troops!" << endl;
        break;
    case CardsType::BLOCKADE:
        cout << "The BLOCKADE card has been played, a neutral zone will be created" << endl;
        break;
    case CardsType::AIRLIFT:
        cout << "The AIRLIFT card has been played, armies will be transfered to a possible location" << endl;
        break;
    case CardsType::DIPLOMACY:
        cout << "Played DIPLOMACY card, peace will be had for a little while" << endl;
        break;
    default:
        cout << "TYPE DNE nothing was made." << endl;
        break;
    }
}

// This is the getter method to get the cards' types.
CardsType Card::getType() const
{
    return CardsType();
}
// probably wont need this unless required to create and set a type later one
CardsType Card::setType() const
{
    return CardsType();
}

//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------These are hand class related implementations ---------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//

// This is the default constructor for hand class
Hand::Hand()
{
    string h = "this will be a default type for hand constructor";
};
// Constructor to be used with the max size of the hand
Hand::Hand(size_t maxSize) : maxSize(maxSize)
{
}

// destructor to deallocate memory/cleanup and prevent memory leaks
Hand::~Hand()
{
    
   // This loop iterate through cards and deletes the current elements using back()
   //to return the ref to last element and pop to remove the element
   while (!cards.empty()) {
    delete cards.back();
    cards.pop_back();
    }
}

// This is the copy constructor for hand class, simlilar to the methods above
Hand::Hand(const Hand &copy)
{
    for (const Card *c:copy.cards)
    {
        cards.push_back(new Card(*c));
    }
};

// The assingment operator as asked in the instructions to initialize one object using another object for hand
Hand &Hand::operator=(const Hand &assign)
{
    if (this != &assign)
    {
        // This loop iterate through cards and deletes the current elements using back()
        //to return the ref to last element and pop to remove the element
         while (!cards.empty()) {
            delete cards.back();
            cards.pop_back();
        }
        // Similar to the copy instructor to initialize by copying the existing one
        for (const Card *c:assign.cards)
        {
            cards.push_back(new Card(*c));
        }
    }

    //This points to an obj of the called member function
    return *this;
}

// This is to take the card that was picked from the deck and put in your hand
void Hand::takeCard(Card *c)
{
    // push back is used to put elements at the end of the vector
    cards.push_back(c);
}

// This method is to remove the card(s) from the current hand
void Hand::removeCard(Card *c)
{
    cards.pop_back();
}

// to get the hand size of the player.
size_t Hand::size() const
{
    return cards.size();
}

// retrieval of the cards that are on the hand using vector Card*
vector<Card *> Hand::getCards()
{
    return cards;
}

//Method to play all the cards in the hand, demonstrated in compiler.
void Card::playAllHand()
{
        switch (t)
        {
        case CardsType::BOMB:
            cout << "The BOMB card has been played ! it goes BOOOOOMMMMMM." << endl;
            break;
        case CardsType::REINFORCEMENT:
            cout << "The REINFORCEMENT card has been played, rally the troops!" << endl;
            break;
        case CardsType::BLOCKADE:
            cout << "The BLOCKADE card has been played, a neutral zone will be created" << endl;
            break;
        case CardsType::AIRLIFT:
            cout << "The AIRLIFT card has been played, armies will be transfered to a possible location" << endl;
            break;
        case CardsType::DIPLOMACY:
            cout << "Played DIPLOMACY card, peace will be had for a little while" << endl;
            break;
        default:
            cout << "TYPE DNE nothing was made." << endl;
            break;
        }
}