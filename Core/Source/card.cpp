#include "card.h"
#include <print>

namespace card {
	
    uint8_t card::get_card_value() const
    {
        if (rank == rank_enum::jack)
            return 10;

        if (rank == rank_enum::queen)
            return 10;

        if (rank == rank_enum::king)
            return 10;

        return static_cast<uint8_t>(rank);
    }

    std::string card::suit_to_string(const suit_enum s)
    {
        switch (s)
        {
	        case suit_enum::hearts:
	            return "Hearts";
	        case suit_enum::diamonds:
	            return "Diamonds";
	        case suit_enum::clubs:
	            return "Clubs";
	        case suit_enum::spades:
	            return "Spades";
        }

		return "Unknown suit";
    }

    std::string card::rank_to_string(const rank_enum r)
    {
		switch (r)
		{
			case rank_enum::ace:
				return "A";
			case rank_enum::two:
				return "2";
			case rank_enum::three:
				return "3";
			case rank_enum::four:
				return "4";
			case rank_enum::five:
				return "5";
			case rank_enum::six:
				return "6";
			case rank_enum::seven:
				return "7";
			case rank_enum::eight:
				return "8";
			case rank_enum::nine:
				return "9";
			case rank_enum::ten:
				return "10";
			case rank_enum::jack:
				return "J";
			case rank_enum::queen:
				return "Q";
			case rank_enum::king:
				return "K";
		}
	    return "Unknown rank";
    }

    std::vector<std::string> card::print_known_card() const
    {
		const std::string r = rank_to_string(rank);
		const std::string s = suit_to_string(suit).substr(0,1);

		// padding so ranks align properly
		const std::string left = r + std::string(5 - r.size(), ' ');
		const std::string right = std::string(5 - r.size(), ' ') + r;

		return {
			" ----- ",
			"|" + left + "|",
			"|     |",
			"|  " + s + "  |",
			"|     |",
			"|" + right + "|",
			" ----- "
		};
    }

    std::vector<std::string> card::print_unknown_card()
    {
		return {
		" ----- ",
		"|  ?  |",
		"|     |",
		"|  ?  |",
		"|     |",
		"|  ?  |",
		" ----- ",
		};
    }
}
