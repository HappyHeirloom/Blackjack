#include <print>
#include "hand.h"
#include "deck.h"

namespace hand {

	void hand::print_hand(const bool show_second_card)
	{
        if (h_cards.empty()) return;

        std::vector<std::vector<std::string>> cards_rows;

        for (size_t i = 0; i < h_cards.size(); ++i)
        {
            if (i == 1 && !show_second_card && h_is_dealer_)
                cards_rows.push_back(h_cards[i].print_unknown_card());
            else
                cards_rows.push_back(h_cards[i].print_known_card());
        }

        for (size_t row = 0; row < cards_rows[0].size(); ++row)
        {
            std::string line;
            for (const auto& cr : cards_rows)
            {
                line += cr[row] + "  ";
            }
            std::println("{}", line);
        }
	}

	uint8_t hand::calculate_value(const bool ignore_second_card) const
	{
        uint8_t total = {};
        uint8_t ace_counter = {};
        uint8_t ignored_card_value = {};

		for (size_t i = 0; i < h_cards.size(); i++)
		{
            const card::card& card = h_cards[i];
            const uint8_t card_value = card.get_card_value();
            if (ignore_second_card && i == 1)
                ignored_card_value = card_value;

            if (card.rank == card::rank_enum::ace)
                ace_counter++;

            total += card_value;
		}

        for (uint8_t i = 1; i <= ace_counter; i++)
        {
	        if (total + 10 <= 21)
		        total += 10; //Ace can be worth 11, so add 10 to the 1 we already counted
        }

        if (ignore_second_card && total != 21)
            total -= ignored_card_value;

        return total;
	}

	bool hand::get_is_dealer() const
	{
		return h_is_dealer_;
	}

	auto hand::get_is_standing() const -> bool
	{
        return h_standing_;
	}

	bool hand::get_is_busted() const
	{
        return h_busted_;
	}

	void hand::set_is_standing(const bool value)
	{
        h_standing_ = value;
	}

	uint8_t hand::get_hand_total(const bool recount_total) const
	{
        if (recount_total)
            return calculate_value(false);
        return h_hand_total_;
	}

	void hand::set_hand_total(const uint8_t total)
	{
        h_hand_total_ = total;
	}

	void hand::add_card_to_hand(card::card card)
	{
        h_cards.emplace_back(card);
        h_hand_total_ = calculate_value(h_ignore_second_card_);
        if (h_hand_total_ > 21)
        {
            h_standing_ = true;
            h_busted_ = true;
        }
           
	}

    bool hand::get_ignore_second_card() const
    {
        return h_ignore_second_card_;
    }

    void hand::set_ignore_second_card(const bool value)
    {
        h_ignore_second_card_ = value;
    }
}
