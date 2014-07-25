#ifndef UNO_H
#define UNO_H

#include <time.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Card
{
public:
	Card(Card&);
	Card();
	Card& operator=(const Card&);
	void show();
	int type;									// to record the color or wildcards with different integers 
	int number; 
	bool CheckCurrent(Card&);					// check to see if it is allowed to put this card on the table after the current card 
};


class CardStack
{
public:
	CardStack();
	CardStack(CardStack&);
	~CardStack();
	Card* stack;
	int num_card;
	Card Pop();
	void Shuffle(Card&);
};

class Player
{
public:
	string name;
	int pull;
	CardStack myCard;
	Player* next;								// point to the next player
	void Display();								// Display the cards in hand and assign them numbers to let users choose
	void Play(Card&, CardStack&);
												// Display and check to see if there is a card the user can put on the table with 
												// CheckCurrent(...). Let the user select by number and if the selected number is 
												// out of range or there is no card to put on the table, pass and take a card from the 
												// stack.
	void ChangeColor(Card&);

												// If the player uses “wildcard” to change the color of the current card on the table 
												// Ask the user to assign a color from the four: red, yellow, green, or blue. 
};
typedef void (Player::*pFunc)(Card& curr, CardStack& stack1);
												// Use member function pointer to access the needed function in sequence 

class UNO
{
public:
	Player* list;
	CardStack tableCard;
	Card currentCard;
	int num;									//the number of players
	UNO();										//if the number of player is not given, there will be two players
	UNO(int);									// assign the number of players
	void shuffle();								// put the extra card into the stack
	void deal();								// distribute cards to players at the startup of the UNO game
	bool checkUNO(int);
												// check if there is someone that has no card, that is, someone that wins,
												// or someone who has only one card
												// the player has to say “UNO!"
	void Game();
												// The function calls Play(...) function of every Player in the list by member function 
												// pointer
};


#endif
