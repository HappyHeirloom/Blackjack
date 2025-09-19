#pragma once

#include <array>
#include <vector>
#include "card.h"

namespace deck {

    constexpr std::array suits = {
        card::suit_enum::hearts,
        card::suit_enum::diamonds,
        card::suit_enum::clubs,
        card::suit_enum::spades
    };

    constexpr std::array ranks{
	    card::rank_enum::ace,
	    card::rank_enum::two,
	    card::rank_enum::three,
	    card::rank_enum::four,
	    card::rank_enum::five,
	    card::rank_enum::six,
	    card::rank_enum::seven,
	    card::rank_enum::eight,
	    card::rank_enum::nine,
	    card::rank_enum::ten,
	    card::rank_enum::jack,
	    card::rank_enum::queen,
	    card::rank_enum::king
    };

    class deck {
	    public:
	        void init_deck(uint8_t deck_amount);
	        void shuffle_deck();
	        card::card draw_card();
	        void print_cards();

        private:
            std::vector<card::card> d_cards_{ 0 };
            std::vector<card::card> d_discard_pile_{ 0 };
            int d_next_card_index_ = { 0 };
    };

}
