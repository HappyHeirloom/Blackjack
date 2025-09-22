#include <iostream>
#include <print>
#include <algorithm>
#include <thread>

#include "dealer.h"
#include "game.h"
#include "deck.h"
#include "player.h"

namespace
{
	uint8_t deck_amount { 6 };
	uint8_t player_amount { 1 };

	bool should_keep_going(const hand::hand& hand)
	{
		return !(hand.get_is_standing() || hand.get_is_busted() || hand.get_has_blackjack());
	}

	bool player_has_blackjack(player::player& player)
	{
		return std::ranges::any_of(player.p_hands, [](const hand::hand& hand) {return hand.get_has_blackjack(); });
	}

	bool player_only_has_blackjacks(player::player& player)
	{
		return std::ranges::all_of(player.p_hands, [](const hand::hand& hand) {return hand.get_has_blackjack(); });
	}

	bool any_blackjack(const dealer::dealer& dealer, player::player& player)
	{
		if (player_has_blackjack(player) || dealer.d_hand.get_has_blackjack())
			return true;

		return false;
	}
}

namespace game {

	void game::init(const uint8_t amount_of_decks, const uint8_t amount_of_players)
	{
		deck_amount = amount_of_decks;
		player_amount = amount_of_players;

		g_deck_ = deck::deck();
		g_deck_.init_deck(amount_of_decks);
		g_deck_.shuffle_deck();

		g_player_ = player::player();
		g_dealer_ = dealer::dealer();

		for (int i = 0; i < 4; i++)
		{
			if (i % 2 == 0)
			{
				g_player_.p_hands[0].add_card_to_hand(g_deck_.draw_card());
			}
			else
			{
				g_dealer_.d_hand.add_card_to_hand(g_deck_.draw_card());
			}
		}

		print_board();
	}

	void game::run()
	{
		// Using indices since we may add new hands during iteration (action::split)
		for (size_t i = 0; i < g_player_.p_hands.size(); i++)  // NOLINT(modernize-loop-convert)
		{
			while (should_keep_going(g_player_.p_hands[i]))
			{
				std::string user_choice;
				bool valid = false;
				while (!valid)
				{
					std::println("\nFor hand #{}, what will you do? ('Stand (st)', 'Hit(h)' or 'Split(sp)') ", i);
					if (!(std::cin >> user_choice)) {
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						std::println("Invalid input, try again.");
						continue;
					}

					switch (player::player::parse_action(user_choice))
					{
					case player::action::stand:
						player::player::stand(g_player_.p_hands[i]);
						valid = true;
						break;

					case player::action::hit:
						player::player::hit(g_deck_.draw_card(), g_player_.p_hands[i]);
						print_board();
						valid = true;
						break;

					case player::action::split: {
						if (g_player_.p_hands[i].h_cards.size() != 2 ||
							g_player_.p_hands[i].h_cards[0].get_card_value() != g_player_.p_hands[i].h_cards[1].get_card_value()
							)
						{
							std::println("Cannot split when both cards aren't the same value");
							break;
						}

						auto& new_hand{ player::player::split(g_player_, g_player_.p_hands[i]) };
						g_player_.p_hands[i].add_card_to_hand(g_deck_.draw_card());
						new_hand.add_card_to_hand(g_deck_.draw_card());
						print_board();
						valid = true;
						break;
					}

					case player::action::invalid:
						valid = false;
						break;
					}
				}

			}
		}

		while (should_keep_going(g_dealer_.d_hand) || !player_only_has_blackjacks(g_player_))
		{
			if (std::ranges::all_of(g_player_.p_hands, [](const hand::hand& hand) { return hand.get_is_busted(); }))
			{
				break;
			}

			g_dealer_.d_hand.set_ignore_second_card(false);
			bool is_soft = false;
			const uint8_t dealer_total = g_dealer_.d_hand.get_hand_total(true);
			g_dealer_.d_hand.set_hand_total(dealer_total);
			if (dealer_total >= 17 && g_dealer_.d_hand.h_cards.size() == 2)
			{
				for (auto& [suit, rank] : g_dealer_.d_hand.h_cards)
				{
					is_soft = rank == card::rank_enum::ace;
				}

				if (is_soft)
				{
					g_dealer_.d_hand.add_card_to_hand(g_deck_.draw_card());
					print_board(g_dealer_.d_hand.get_is_standing());
					continue;
				}
			}
			if (dealer_total < 17)
			{
				g_dealer_.d_hand.add_card_to_hand(g_deck_.draw_card());
				print_board(g_dealer_.d_hand.get_is_standing());
				continue;
			}

			if (dealer_total >= 17 && !is_soft)
			{
				g_dealer_.d_hand.set_is_standing(true);
				print_board(g_dealer_.d_hand.get_is_standing());
				break;
			}
		}

		compare_hands(g_dealer_.d_hand, g_player_.p_hands);
		std::this_thread::sleep_for(std::chrono::seconds(3));
		replay();
	}

	void game::replay()
	{
		for (int i = 0; i < 50; i++)
			std::println("################");

		init(deck_amount, player_amount);

		if (any_blackjack(g_dealer_, g_player_))
		{
			compare_hands(g_dealer_.d_hand, g_player_.p_hands);
			std::this_thread::sleep_for(std::chrono::seconds(3));
			replay();
		}
		else
		{
			run();
		}

	}

	void game::print_board(const bool dealer_done)
	{
		uint8_t dealer_total = g_dealer_.d_hand.get_hand_total();
		std::println("################");
		std::println("Dealer total: {}", dealer_total);


		g_dealer_.d_hand.print_hand(dealer_total == 21 || g_dealer_.d_hand.h_cards.size() != 2 || dealer_done);

		for (size_t i = 0; i < g_player_.p_hands.size(); i++)
		{
			g_player_.p_hands[i].print_hand();
			std::println("Player hand #{} total: {}", i, g_player_.p_hands[i].get_hand_total());
		}

		std::println("################");
		std::cout << "\n";
	}

	void game::compare_hands(const hand::hand& dealer, const std::vector<hand::hand>& player_hands)
	{
		const bool dealer_busted = dealer.get_is_busted();
		const uint8_t dealer_total = dealer.get_hand_total();
		const bool dealer_blackjack = dealer.get_has_blackjack();

		for (size_t i = 0; i < player_hands.size(); i++)
		{
			if (player_hands.size() > 1)
				std::println("\nResult for hand #{}", i);

			std::println("################");
			std::println("################");

			const bool player_busted = player_hands[i].get_is_busted();
			const uint8_t player_total = player_hands[i].get_hand_total();
			const bool player_blackjack = player_hands[i].get_has_blackjack();

			if (dealer_blackjack && !player_blackjack)
			{
				std::println("Winner is the dealer :( - Won by having blackjack");
			}
			else if (player_blackjack && !dealer_blackjack)
			{
				std::println("Winner is the player! - Won by having blackjack");
			}
			else if (dealer_blackjack && player_blackjack)
			{
				std::println(R"(Winner is none??! - BOTH BLACKJACK?!)");
			}
			else if (dealer_busted && !player_busted)
			{
				std::println("Winner is the player! - Dealer busted");
			}			
			else if (player_busted && !dealer_busted)
			{
				std::println("Winner is the dealer :( - Player busted");
			}
			else if (dealer_total > player_total)
			{
				std::println("Winner is the dealer :( - {} against {}", dealer_total, player_total);
			}
			else if (dealer_total < player_total)
			{
				std::println("Winner is the player! - {} against {}", player_total, dealer_total);
			}
			else if (dealer_total == player_total)
			{
				std::println(R"(Winner is none??! - IT'S A PUSH :O)");
			}
		}
	}



}
