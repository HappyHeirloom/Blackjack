#include "deck.h"
#include "card.h"
#include <print>
#include <algorithm>
#include <random>

namespace deck {
	void deck::init_deck(const uint8_t deck_amount)
	{
		d_next_card_index_ = 0;
		for (uint8_t i = 0; i < deck_amount; i++)
		{
			for (auto& suit : suits)
			{
				for (auto& rank : ranks)
				{
					auto card = card::card {.suit = suit, .rank = rank};
					d_cards_.push_back(card);
				}
			}
		}
	}

	void deck::shuffle_deck()
	{
		std::random_device rd;
		std::mt19937 g(rd());

		std::ranges::shuffle(d_cards_, g);
	}

	card::card deck::draw_card()
	{
		return d_cards_[d_next_card_index_++];
	}

	void deck::print_cards()
	{
		for (auto& [suit, rank] : d_cards_)
		{
			std::println("{} of {}", 
				card::card::rank_to_string(rank), 
				card::card::suit_to_string(suit));
		}
	}

}
