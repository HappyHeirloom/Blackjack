#include "player.h"

namespace player
{
	void player::stand(hand::hand& hand)
	{
		 hand.set_is_standing(true);
	}

	void player::hit(const card::card card)
	{
		p_hand.add_card_to_hand(card);
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
		if (uppercase_input == "S" || uppercase_input == "STAND")
		{
			return action::stand;
		} 
		return action::invalid;
		
	}
}
