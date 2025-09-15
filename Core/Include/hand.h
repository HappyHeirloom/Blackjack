#pragma once

#include <vector>
#include "card.h"
#include "deck.h"

namespace hand {

	class hand {
		private:
			bool h_is_dealer_ = false;
			bool h_ignore_second_card_{ true };
			uint8_t h_hand_total_{ 0 };
			bool h_standing_{ false };
			bool h_busted_{ false };
			
		public:
			explicit hand(const bool is_dealer = false) :
							h_is_dealer_(is_dealer),
							h_ignore_second_card_(is_dealer) {}

			std::vector<card::card> h_cards;
			void print_hand(bool show_second_card = true);
			[[nodiscard]] uint8_t calculate_value(bool ignore_second_card = false) const;
			[[nodiscard]] auto get_is_dealer() const -> bool;
			[[nodiscard]] bool get_is_standing() const;
			[[nodiscard]] bool get_is_busted() const;
			void set_is_standing(bool value);
			[[nodiscard]] uint8_t get_hand_total(bool recount_total = false) const;
			void set_hand_total(uint8_t total);
			void add_card_to_hand(card::card card);
			[[nodiscard]] auto get_ignore_second_card() const -> bool;
			void set_ignore_second_card(bool value);
	};

}
