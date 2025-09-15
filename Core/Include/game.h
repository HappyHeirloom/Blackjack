#pragma once
#include "dealer.h"
#include "deck.h"
#include "player.h"

namespace game {

	class game
	{
		private:
			player::player g_player_;
			dealer::dealer g_dealer_;
			deck::deck g_deck_{};

		public:
			void init();
			void replay();
			void run();
			void print_board(bool dealer_done = false);
			static void compare_hands(const hand::hand& dealer, const hand::hand& player);
	};

}
