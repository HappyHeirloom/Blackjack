#include "player.h"

namespace player
{
	void player::stand(hand::hand& hand)
	{
		 hand.set_is_standing(true);
	}

	void player::hit(const card::card card, hand::hand& hand)
	{
		hand.add_card_to_hand(card);
	}

	hand::hand& player::split(player& player, hand::hand& hand)
	{
		hand::hand new_hand { false };

		new_hand.h_cards.push_back(hand.h_cards[1]);
		hand.h_cards.pop_back();

		player.p_hands.push_back(new_hand);

		return player.p_hands.back();
	}

	action player::parse_action(const std::string& input)
	{
		std::string uppercase_input{};
		for (const auto& c : input)
		{
			uppercase_input += static_cast<char>(toupper(c));
		}

		if (uppercase_input == "H" || uppercase_input == "HIT")
		{
			return action::hit;
		}
		if (uppercase_input == "ST" || uppercase_input == "STAND")
		{
			return action::stand;
		}
		if (uppercase_input == "SP" || uppercase_input == "SPLIT")
		{
			return action::split;
		}

		return action::invalid;
		
	}
}
