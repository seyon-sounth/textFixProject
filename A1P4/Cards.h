#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

//Defining the type of each required card using enum to facilitate usage later on
enum class CardsType {
    BOMB,
    REINFORCEMENT,
    BLOCKADE,
    AIRLIFT,
    DIPLOMACY
};

//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------These are Card class related implementations---------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
class Card{

private:
    //making the card type private for protection.
    CardsType t;

public:

    //this will be the defaulted constructor
    Card();
    //destructor to deallocate memory/cleanup and prevent memory leaks
    ~Card();
    //this will be the constructor that takes a card of type Cardtype
    Card(CardsType t);
    //this is the copy constructor as required per the assignment
    Card(const Card& copy);
    // This is an assignment operator as requested per the requirements
    Card& operator=(const Card& assign);
    //this method will be to get the enum converted types into strings
    string stringConversion() const;
    

    // This is an stream insertion operator as requested using friend class to acess private members
    friend ostream & operator << (ostream &out, const Card &c);
    friend istream & operator >> (istream &in,  Card &c);
    //play method to used to play the card after it was picked from the deck
    void play();

    //This is a getter in the eventuality that we need to get the type of a card
    CardsType getType() const;
    //if ever need to create a new var and set its type.
    CardsType setType() const;


    //This method is to play all the cards avaiable in the hand
    void playAllHand();
};


//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------These are Deck class related implementations ---------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
class Deck{
//initializing private vector of Card cards and the max size that it can hold as well to a finite value of deck
private: 
   vector<Card*> cards; 
   size_t maxSize;
public:

   //this will be the defaulted constructor for Deck
   Deck();
   //destructor to deallocate memory/cleanup and prevent memory leaks
   ~Deck();
   //this will be the paremterized constructor that takes in the max size of the deck
   Deck(size_t maxSize);
   //this is the copy constructor for Deck as required using copy as a variable
   Deck(const Deck& copy);
   // This is an assignment operator for deck as requested using assign as the variable
   Deck& operator=(const Deck& assign);
   // This is an  stream insertion operator as requested using friend class to acess private members
   friend ostream & operator << (ostream &out, const Deck &c);
   friend istream & operator >> (istream &in,  Deck &c);
  
   //This method will be to determine the decksize using the function size()
   size_t size() const;

   // This will be for the draw methods where we can draw rng cards from the deck
   Card* draw();
   //method to add all the necessary Card to the deck
   void addCardToDeck(Card * c);
   
};

//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------These are hand class related implementations ---------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------//
class Hand{

private:
   vector<Card*> cards;
   size_t maxSize;
   CardsType t;
   
public:

    //this will be the defaulted constructor for hand class
    Hand();

    //this will be the parameterized constructor for hand class
    Hand(size_t maxSize);

     //destructor to deallocate memory/cleanup
    ~Hand();
     //this is the copy constructor for Hand as required 
     Hand(const Hand& copy);
     
    //This is an assignment operator for deck as requested
    Hand& operator=(const Hand& assign);
    // This is an d stream insertion operator as requested using friend class to acess private members
    friend ostream & operator << (ostream &out, const Hand &c);
    friend istream & operator >> (istream &in,  Hand &c);
   

    //take Card method is for after when drawing, adding the card to the hand.
    void takeCard(Card* cards);

    //getter method to get the elements of the Card vector
    vector<Card *> getCards();
    
    //This method will be to determine the hand size
    size_t size() const;

    //method to remove cards from the hand as we need to insert them in the deck per requirement
    void removeCard(Card * c);

};

#endif