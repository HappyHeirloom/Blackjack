#pragma once

#include <string>
#include <vector>

namespace card {

    enum class suit_enum : uint8_t
    {
        hearts,
        diamonds,
        clubs,
        spades
    };

    enum class rank_enum : uint8_t
    {
        ace = 1,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king
    };

    class card {
		public:
			suit_enum suit;
			rank_enum rank;

			[[nodiscard]] uint8_t get_card_value() const;
			static std::string suit_to_string(suit_enum s);
            static std::string suit_to_unicode(suit_enum s);
            static std::string rank_to_string(rank_enum r);

			[[nodiscard]] std::vector<std::string> print_known_card() const;
			[[nodiscard]] std::vector<std::string> print_unknown_card();
    };


}
