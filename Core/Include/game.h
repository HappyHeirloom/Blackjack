#pragma once
#include "dealer.h"
#include "deck.h"
#include "player.h"

namespace game {

	class game
	{
		public:
			void init(uint8_t amount_of_decks, uint8_t amount_of_players);
			void run();
			void replay();
			void print_board(bool dealer_done = false);
			static void compare_hands(const hand::hand& dealer, const std::vector<hand::hand>& player_hands);

		private:
			player::player g_player_;
			dealer::dealer g_dealer_;
			deck::deck g_deck_{};
	};

}
