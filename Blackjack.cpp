/*
Names: Andrew Foster, Jacob Morgan, and Tom Myers
Date Last Modified: December 9, 2018
Assignment: Final Project - Blackjack
Description: Play a simple game of blackjack against a computer dealer, 
			 with the options of betting and replays (multiple rounds).
File: Blackjack.cpp
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Game {
	public:
		int drawCard(vector<int>&deck) { //
			int card = 0;
			int spot = ((rand() % 52) + 1);

			while (deck[spot] == 0) { //Check if the spot is 0 (card already pulled)
				spot = (rand() % 52);
			}

			card = deck[spot]; //Get card
			deck[spot] = 0; //Make the card in the deck 0 so that it is skipped over (already pulled)

			return card;
		}

		bool playFirstRound(vector<int>deck) { //The first round of blackjack has unique conditions
			gRound = 1;

			cout << "*** Round 1 ***" << endl << endl;
			cout << "The dealer shuffles the deck, deals you two cards, then deals himself two cards." << endl;

			int playerCard1 = drawCard(deck);
			int playerCard2 = drawCard(deck);
			int dealerCard1 = drawCard(deck);
			int dealerCard2 = drawCard(deck);

			playerHand.push_back(playerCard1);
			playerHand.push_back(playerCard2);
			dealerHand.push_back(dealerCard1);
			dealerHand.push_back(dealerCard2);

			cout << "Your first card is a(n)";
			if (playerCard1 == 1) {
				cout << " ace." << endl;
				playerVal += 1;
				playerA += 1;
			}
			else if (playerCard1 > 10) {
				cout << " face card." << endl;
				playerVal += 10;
				playerF += 1;
			}
			else {
				cout << " " << playerCard1 << ".";
				playerVal += playerCard1;
			}
			cout << endl;

			cout << "Your second card is a(n)";
			if (playerCard2 == 1) {
				cout << " ace." << endl;
				playerVal += 1;
				playerA += 1;
			}
			else if (playerCard2 > 10) {
				cout << " face card." << endl;
				playerVal += 10;
				playerF += 1;
			}
			else {
				cout << " " << playerCard2 << ".";
				playerVal += playerCard2;
			}
			cout << endl;

			if ((playerA == 1) && (playerVal == 11)) {
				playerVal = 21;
			}
			if ((playerA == 1) && (playerF == 1)) {
				playerB = 1;
				playerVal = 21;
			}
			if (playerVal == 21) {
				cout << "You have reached 21 points." << endl;
			}

			cout << "The value of your hand is ";
			if (playerB == 1) {
				cout << playerVal << "." << endl;
				cout << "You have BLACKJACK!" << endl;
			}
			else {
				cout << playerVal << "." << endl;
			}
			cout << endl;


			cout << "The dealer reveals their first card: a(n)"; //1st card reveal, if it's an ace or 10/face card, 2nd (hole) card is revealed
			if (dealerCard1 == 1) {
				cout << " ace." << endl;
				dealerA += 1;
				dealerVal += 1;
				if (dealerCard2 == 10) {
					cout << "The dealer reveals their second card: a 10." << endl;
					cout << "The dealer has reached 21 points." << endl;
					dealerVal += 10;
				}
				else if (dealerCard2 > 10) {
					cout << "The dealer reveals their second card: a face card." << endl;
					cout << "The dealer has reached 21 points." << endl;
					dealerF += 1;
					dealerB = 1;
					cout << "The dealer has BLACKJACK!" << endl;
				}
				else {
				}
			}
			else if (dealerCard1 > 10) {
				cout << " face card." << endl;
				dealerVal += 10;
				dealerF += 1;
				if (dealerCard2 == 1) {
					cout << "The dealer reveals their second card: an ace." << endl;
					cout << "The dealer has reached 21 points." << endl;
					dealerA += 1;
					dealerB = 1;
					cout << "The dealer has BLACKJACK!" << endl;
				}
			}
			else if (dealerCard1 == 10) {
				cout << " 10." << endl;
			}
			else {
				cout << " " << dealerCard1 << ".";
				dealerVal += dealerCard1;
			}

			if ((dealerA == 1) && (dealerVal == 11)) {
				dealerVal = 21;
			}
			if ((dealerA == 1) && (dealerF == 1)) {
				dealerB = 1;
				dealerVal = 21;
			}
			if (((playerB == 1) && (dealerB == 1)) || (((playerB == 0) && (dealerB == 0)) && ((playerVal == 21) && (dealerVal == 21)))) {
				cout << "PUSH! Both players have blackjack or a simple 21, a TIE!" << endl; //If both the player and dealer have 1 ace and 1 face card each, they both have a perfect blackjack. Push/tie.
				return 0;
			}
			else if ((playerB == 1) && (dealerB == 0)) {
				cout << "YOU WIN!" << endl;
				payout += wager;
				wins += 1;
				return 0;
			}
			else if ((playerB == 0) && (dealerB == 1)) {
				cout << "The dealer reached true blackjack, but you did not." << endl;
				cout << "You lose." << endl;
				payout -= wager;
				loss += 1;
				return 0;
			}
			else if ((playerVal == 21) && (dealerVal != 21)) {
				cout << "YOU WIN!" << endl;
				payout += wager;
				wins += 1;
				return 0;
			}
			else if ((playerVal != 21) && (dealerVal == 21)) {
				cout << "You lose." << endl;
				payout -= wager;
				loss += 1;
				return 0;
			}
			else {
				cout << endl;
			}
			cout << "*** End of Round 1 ***" << endl << endl;
			return 1;
		}

		void printHand(vector<int>hand) {
			cout << "Your hand: ";
			for (int i = 0; i < hand.size(); i++) {
				if (hand[i] == 1) {
					cout << "an ace";
				}
				else if (hand[i] > 10) {
					cout << "a face card";
				}
				else {
					cout << "a(n) " << hand[i];
				}
				if (i != (hand.size() - 1)) {
					cout << ", ";
				}
			}
			cout << endl;
		}

		bool playNextRound(vector<int>deck) {//Subsequent round loop
			gRound += 1;
			int newCard = 0;
			int spot = gRound - 1;
			
			printHand(playerHand);
			cout << "What's your next move?" << endl;
			cout << "1. Stand (keep your hand), 2. Hit (draw another card), 3. Double (double your bet and draw one last card), 4. Surrender (forfeit half wager and quit)." << endl;
			cin >> choice;
			cout << endl;

			switch (choice) {
				case 1:
					break;
				case 2:
					newCard = drawCard(deck);
					playerHand.push_back(newCard);
					cout << "You were dealt a(n)";
					if (newCard == 1) {
						cout << " ace." << endl;
						playerA += 1;
						playerVal += 1;
					}
					else if (newCard > 10) {
						cout << " face card." << endl;
						playerF += 1;
						playerVal += 10;
					}
					else {
						cout << " " << newCard << "." << endl;
						playerVal += newCard;
					}
					break;
				case 3:
					wager *= 2;
					cout << "Your wager is now $" << wager << "." << endl;
					newCard = drawCard(deck);
					playerHand.push_back(newCard);
					cout << "You were dealt a(n)";
					if (newCard == 1) {
						cout << " ace." << endl;
						playerA += 1;
						playerVal += 1;
					}
					else if (newCard > 10) {
						cout << " face card." << endl;
						playerF += 1;
						playerVal += 10;
					}
					else {
						cout << " " << newCard << "." << endl;
						playerVal += newCard;
					}
					break;
				case 4:
					if (gRound == 2) {
						return 0;
					}
					else {
						cout << "There's no surrender past round 2! Quit instead? (y/n): ";
						cin >> choice;
						if (choice == (89 || 121)) {
							return 0;
						}
						else if (choice == (78 || 110)) {
							break;
						}
						else {
							return 0;
						} 
					}
					break;
				default:
					break;
			}

			cout << "The value of your hand is " << playerVal << "." << endl << endl;

			if ((playerA >= 1) && (playerVal == 11)) {
				playerVal = 21;
			}
			if (playerVal > 21) {
				cout << "You passed 21. BUST!" << endl << endl;
			}
			if (playerVal == 21) {
				cout << "You have reached 21 points." << endl << endl;
			}

			cout << "The dealer reveals their hole card: a(n)";
			if ((dealerHand[spot]) == 1) {
				cout << " ace." << endl;
				dealerVal += 1;
				dealerA += 1;
			}
			else if ((dealerHand[spot]) > 10) {
				cout << " face card." << endl;
				dealerVal += 10;
				dealerF += 1;
			}
			else {
				cout << " " << dealerHand[spot] << "." << endl;
				dealerVal += dealerHand[spot];
			}

			if (dealerVal <= 16) {
				newCard = drawCard(deck);
				dealerHand.push_back(newCard);
				dealerVal += newCard;
				if (dealerVal > 21) {
					cout << "The dealer drew a(n)";
					if (newCard == 1) {
						cout << " ace." << endl;
						dealerA += 1;
					}
					else if (newCard > 10) {
						cout << " face card." << endl;
						dealerF += 1;
					}
					else {
						cout << " " << newCard << "." << endl;
					}
					cout << "The dealer passed 21. BUST!" << endl;
				}
				if (dealerVal == 21) {
					cout << "The dealer has reached 21 points." << endl;
				}
			}

			if ((dealerA >= 1) && (dealerVal == 11)) {
				dealerVal = 21;
			}

			if (dealerVal == 21) {
				cout << "The dealer has reached 21 points." << endl;
			}

			if ((playerVal < 21) && (dealerVal < 21)) {
				cout << "*** End of Round " << gRound << " ***" << endl << endl;
				return 1;
			}

			if ((playerVal > 21) && (dealerVal > 21)) {
				cout << "Both players bust, a TIE!" << endl;
				return 0;
			}

			if ((playerVal == 21) && (dealerVal < 21)) {
				cout << "YOU WIN!" << endl;
				payout += wager;
				wins += 1;
				return 0;
			}

			if ((playerVal < 21) && (dealerVal == 21)) {
				cout << "You lose." << endl;
				payout -= wager;
				loss += 1;
				return 0;
			}

			if ((playerVal <= 21) && (dealerVal > 21)) {
				cout << "YOU WIN!" << endl;
				payout += wager;
				wins += 1;
				return 0;
			}

			if ((playerVal > 21) && (dealerVal <= 21)) {
				cout << "You lose." << endl;
				payout -= wager;
				loss += 1;
				return 0;
			}

			if ((playerVal == 21) && (dealerVal == 21)) {
				if (playerA > dealerA) {
					cout << "Your cards trump the dealers." << endl;
					cout << "YOU WIN!" << endl;
					payout += wager;
					wins += 1;
					return 0;
				}
				else if (dealerA > playerA) {
					cout << "The dealer's cards trump yours." << endl;
					cout << "You lose." << endl;
					payout -= wager;
					loss += 1;
					return 0;
				}
				else if (playerF > dealerF) {
					cout << "Your cards trump the dealers." << endl;
					cout << "YOU WIN!" << endl;
					payout += wager;
					wins += 1;
					return 0;
				}
				else if (dealerF > playerF) {
					cout << "The dealer's cards trump yours." << endl;
					cout << "You lose." << endl;
					payout -= wager;
					loss += 1;
					return 0;
				}
				else {
					cout << "Both players reached 21 points, a TIE!" << endl;
					return 0;
				}
			}

			cout << "*** End of Round " << gRound << " ***" << endl << endl;
			return 1;
		}

		void playGame() {
			char x = 1;
			
			while (x == 1) {
				game += 1; //Set or resest values at the beginning of each game
				gRound = 0;
				choice = 0;
				playerA = 0;
				playerF = 0;
				playerB = 0;
				dealerA = 0;
				dealerF = 0;
				dealerB = 0;
				playerHand.clear();
				dealerHand.clear();

				vector<int>deck(52); //Initialize or reset deck at the beginning of each game
				for (int i = 0; i < baseDeck.size(); i++) {
					deck[i] = baseDeck[i];
				}

				cout << "You currently have $" << payout << "." << endl;
				cout << "Place your bet: ";
				cin >> wager;

				while ((wager > payout) || (wager <= 0)) {
					cout << "ERROR: Enter a positive amount not exceeding your total funds to bet: ";
					cin >> wager;
				}
				cout << endl;

				cout << "*** Game " << game << " Begins! ***" << endl;

				int state = playFirstRound(deck);
				if (state == 0) {
					cout << "*** End of Game " << game << ". ***" << endl;
				}
				if (state == 1) {
					while (state == 1) {
						state = playNextRound(deck);
						if (state == 0) {
							cout << "*** End of Game " << game << ". ***" << endl;
						}
					}
				}

				cout << "Play again? (Y/N): ";
				cin >> x;
				if ((x == 89) || (x == 121)) {
					x = 1;
				}
				else {
					x = 0;
				}
				cout << endl;
			}
		}

		void theGame() { //Function only calls credits once by being separate from playGame
			cout << "-~# Welcome to Andrew Foster and Jacob Morgan's Blackjack game! #~-" << endl; 
			cout << "> Created for Prof. Montjoy's Fall 2018 Computer Science I Class. <" << endl << endl;
			playGame(); 
			cout << "Your final balance was $" << payout << "." << endl;
		}

	private:
		const vector<int>baseDeck = {
		1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, //Standard deck of 52 cards,
		4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, //with assigned values different than their Blackjack values
		7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, //so that the game functions can tell wether or not an ace or face card has been pulled
		10, 10, 10, 10, 11, 11, 11, 11, 
		12, 12, 12, 12, 13, 13, 13, 13 };  	   
	     								  
		int payout = 1000; //How much money the player has
		int wager = 0; //How much the playe ris betting
		int game = 0; //Current game number
		int gRound = 0; //Current round in game
		int choice = 0;
		int wins = 0; //Number of times the player has won
		int loss = 0; //Number of times the player has lost
		int playerA = 0; //Number of aces the player has
		int playerF = 0; //Number of face cards the player has
		int playerB = 0; //If player has true blackjack or not
		int dealerA = 0; //Number of aces the dealer has
		int dealerF = 0; //Number of aces the dealer has
		int dealerB = 0; //If dealer has true blackjack or not
		int playerVal = 0; //Total value of player's hand
		vector<int>playerHand; //Player's hand of cards
		int dealerVal = 0; //Total value of dealer's hand
		vector<int>dealerHand; //Dealer's hand of cards
};

int main() {
	srand(time(0));

	Game Start;
	Start.theGame();

	return 0;
}