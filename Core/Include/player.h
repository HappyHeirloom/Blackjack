#pragma once
#include "hand.h"

namespace player
{
	enum class action : uint8_t
	{
		hit = 1,
		stand,
		split,
		invalid
	};

	class player
	{
		public:
			std::vector<hand::hand> p_hands;

			player()
			{
				p_hands.emplace_back(false);
			}

			static void stand(hand::hand& hand);
			static void hit(card::card card, hand::hand& hand);
			static hand::hand& split(player& player, hand::hand& hand);
			static action parse_action(const std::string& input);
	};
}