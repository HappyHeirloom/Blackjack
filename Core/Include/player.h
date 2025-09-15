#pragma once
#include "hand.h"

namespace player
{
	enum class action : uint8_t
	{
		hit = 1,
		stand,
		invalid
	};

	class player
	{
	private:

	public:
		hand::hand p_hand{ false };

		static void stand(hand::hand& hand);
		void hit(card::card card);
		static action parse_action(const std::string& input);
	};
}