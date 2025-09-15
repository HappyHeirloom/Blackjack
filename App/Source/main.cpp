#include <iostream>
#include <print>
#include "deck.h"
#include "game.h"

// GAME RULES
//Blackjack is played between a player and a dealer.
//
//Each starts with 2 cards.
//
//The goal is to get as close as possible to 21 without going over.
//
//Face cards(Jack, Queen, King) are worth 10, Aces are 1 or 11, numbers are their value.
//
//Player can hit(draw a card) or stand(keep current hand).
//
//Dealer has a simple rule : usually hits until 17 or higher.


int main(int argc, char* argv[])
{
	auto game = game::game();

	game.init();
	game.run();

	//deck.shuffle_deck();
	//deck.print_cards();
	return 0;
}