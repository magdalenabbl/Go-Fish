#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Function to initialize the deck with cards.
void initializeDeck(vector<string>& deck)
{
	const string values[] = {
		"2", "3", "4", "5", "6", "7", "8", "9",
		"10", "J", "Q", "K", "A"
	};
	// Add 13 cards (one suit) for each of the four suits.
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 13; ++j)
		{
			deck.push_back(values[j]);
		}
	}
}

// Function to shuffle the deck.

void shuffleDeck(vector<string>& deck)
{
	srand(static_cast<unsigned> (time(0)));

	for (int i = 0; i < static_cast<int> (deck.size()); ++i)
	{
		// Swap cards at random positions.
		int randIndex = rand() % deck.size();
		string temp = deck[i];
		deck[i] = deck[randIndex];
		deck[randIndex] = temp;
	}
}

// Function to deal cards to players.

void dealCards(vector<string>& deck, vector<string>& hand, int numCards)
{
	// Transfer the top cards from the deck to the player's hand.
	for (int i = 0; i < numCards && !deck.empty(); ++i)
	{
		hand.push_back(deck.back());
		deck.pop_back();
	}
}
// Function to display the cards in a hand.
void showHand(const vector<string>& hand)
{
	// Print all the cards in the hand to the screen.
	for (int i = 0; i < static_cast<int> (hand.size()); ++i)
	{
		cout << hand[i] << " ";
	}
	cout << endl;
}

// Function to check if the hand contains a specific card.
bool hasCard(const vector<string>& hand, const string& cardType)
{
	// Iterate through the hand and look for a card of the specified type.
	for (int i = 0; i < static_cast<int> (hand.size()); ++i)
	{
		if (hand[i] == cardType)
		{
			return true;
		}
	}
	return false;
}
// Function to remove specific cards from one hand and transfer them to another.
void removeCards(
	vector<string>& fromHand,
	vector<string>& toHand,
	const string& cardType
)
{
	vector<string> newHand;

	for (int i = 0; i < static_cast<int> (fromHand.size()); ++i)
	{
		if (fromHand[i] == cardType)
		{
			toHand.push_back(fromHand[i]);
		}
		else
		{
			newHand.push_back(fromHand[i]);
		}
	}
	fromHand = newHand;
}
// Function to collect sets of four identical cards.

void collectSets(
	vector<string>& hand,
	vector<string>& sets,
	const string& playerName
)
{
	const string values[] = {
		"2", "3", "4", "5", "6", "7", "8", "9",
		"10", "J", "Q", "K", "A"
	};

	for (int v = 0; v < 13; ++v)
	{
		int count = 0;
		// Count the cards of the same value in the hand.
		for (int i = 0; i < static_cast<int> (hand.size()); ++i)
		{
			if (hand[i] == values[v])
			{
				count++;
			}
		}

		if (count == 4)
		{
			cout << playerName << " has collected all four "
				<< values[v] << "s!" << endl;
			// The player must confirm the collection.
			if (playerName == "Player")
			{
				string input;

				while (true)
				{
					cout << "Player, type '*' to confirm: ";
					cin >> input;

					if (input == "*")
					{
						sets.push_back(values[v]);
						vector<string> newHand;

						for (int i = 0; i < static_cast<int> (hand.size()); ++i)
						{
							if (hand[i] != values[v])
							{
								newHand.push_back(hand[i]);
							}
						}
						hand = newHand;

						cout << "Player has given the "
							<< values[v] << " cards."
							<< endl;
						break;
					}
					else
					{
						cout << "Player did not confirm correctly."
							<< endl;
					}
				}
			}
			else
			{
				sets.push_back(values[v]);
				vector<string> newHand;

				for (int i = 0; i < static_cast<int> (hand.size()); ++i)
				{
					if (hand[i] != values[v])
					{
						newHand.push_back(hand[i]);
					}
				}
				hand = newHand;
			}
		}
	}
}
// Function to draw a card if the hand is empty.
bool drawIfEmpty(
	vector<string>& hand,
	vector<string>& deck,
	const string& playerName
)
{
	if (hand.empty() && !deck.empty())
	{
		hand.push_back(deck.back());
		deck.pop_back();
		cout << playerName << " draws a card from the deck."
			<< endl;
		return true;
	}
	return false;
}
// Function to check if the first phase of the game is over.
bool checkEndOfFirstPhase(
	const vector<string>& playerHand,
	const vector<string>& computerHand,
	const vector<string>& deck
)
{
	// The first phase ends when both hands and the deck are empty.
	return playerHand.empty() && computerHand.empty() && deck.empty();
}

void secondPhase(
	vector<string>& playerSets,
	vector<string>& computerSets
)
{
	cout << "\n=== Second Phase: Asking for collections ===" << endl;
	bool isPlayerTurn = true;

	if (computerSets.empty())
	{
		cout << "Your sets: " << endl;
		cout << "\nYou have collected all the collections! You win!" << endl;
		return;
	}
	else if (playerSets.empty())
	{
		cout << "\nComputer has collected all the collections! Computer wins!"
			<< endl;
		return;
	}

	while (!playerSets.empty() && !computerSets.empty())
	{
		if (isPlayerTurn)
		{
			cout << "Enter the type of collection you want to ask for (e.g., 'A', '7'): ";
			string collectionType;
			cin >> collectionType;

			vector<string> Set = {
				"2", "3", "4", "5", "6", "7", "8", "9",
				"10", "J", "Q", "K", "A"
			};

			if (!hasCard(Set, collectionType))
			{
				cout << "That's not a card. Try again." << endl;
				continue;
			}

			for (size_t i = 0; i < computerSets.size(); ++i)
			{
				if (computerSets[i] == collectionType)
				{
					cout << "Computer gives you the collection of "
						<< collectionType << "s!" << endl;
					playerSets.push_back(computerSets[i]);
					computerSets.erase(computerSets.begin() + i);
					continue;
				}
				else
				{
					isPlayerTurn = false;
				}
			}

			if (isPlayerTurn == false)
			{
				cout << "Computer does not have the collection of "
					<< collectionType << "s. Your turn ends."
					<< endl;
			}
		}
		else
		{
			cout << "\nComputer's turn..." << endl;

			if (!computerSets.empty())
			{
				cout << "Your sets: " << endl;
				showHand(playerSets);

				const vector<string> values = {
					"2", "3", "4", "5", "6", "7", "8", "9",
					"10", "J", "Q", "K", "A"
				};

				string computerRequest = values[rand() % values.size()];

				cout << "Computer asks for the collection of "
					<< computerRequest << "s." << endl;
				

				bool found = false;

				for (size_t i = 0; i < playerSets.size(); ++i)
				{
					if (playerSets[i] == computerRequest)
					{
						found = true;
						string input;

						while (true)
						{
							cout << "Player, type '*' to give your collection: ";
							cin >> input;

							if (input == "*")
							{
								computerSets.push_back(playerSets[i]);
								playerSets.erase(playerSets.begin() + i);
								cout << "Player has given the "
									<< computerRequest
									<< " cards." << endl;
								break;
							}
							else
							{
								cout << "Player did not confirm correctly."
									<< endl;
							}
						}

						cout << "You give the collection of "
							<< computerRequest
							<< "s to the Computer."
							<< endl;
						break;
					}
				}

				if (!found)
				{
					cout << "You do not have the collection of "
						<< computerRequest
						<< "s. Computer's turn ends." << endl;
					isPlayerTurn = true;
				}
			}
		}
	}
}

void playerTurn(
	vector<string>& playerHand,
	vector<string>& computerHand,
	vector<string>& deck,
	vector<string>& playerSets,
	vector<string>& computerSets
)
{
	while (playerHand.empty() && !deck.empty())
	{
		cout << "Your hand is empty. Drawing a card from the deck..."
			<< endl;
		playerHand.push_back(deck.back());
		deck.pop_back();
		cout << "You drew a " << playerHand.back() << "." << endl;
	}

	cout << "Your turn. Your hand: ";
	showHand(playerHand);
	collectSets(playerHand, playerSets, "Player");

	while (playerHand.empty() && !deck.empty())
	{
		cout << "Your hand is empty. Drawing a card from the deck..."
			<< endl;
		playerHand.push_back(deck.back());
		deck.pop_back();
		cout << "You drew a " << playerHand.back() << "." << endl;
	}

	while (true)
	{
		if (
			(playerHand.empty() && deck.empty())
			|| (computerHand.empty() && deck.empty())
			)
		{
			cout << "Your hand is empty, and the deck is empty! "
				<< "Moving to the second phase of the game."
				<< endl;
			cout << "Ask for a collection" << endl;
			secondPhase(playerSets, computerSets);

			if (playerSets.empty())
			{
				cout << "End of the game! ";
				cout << "\nComputer has collected all the collections! "
					<< "Computer wins!" << endl;
				string input;

				while (true)
				{
					cout << "Player, type '*' to end the game: ";
					cin >> input;

					if (input == "*")
					{
						return;
					}
					else
					{
						cout << "Player did not confirm correctly."
							<< endl;
					}
					return;
				}
				return;
			}

			if (computerSets.empty())
			{
				cout << "End of the game! ";
				string input;

				while (true)
				{
					cout << "Player, type '*' to end the game: ";
					cin >> input;

					if (input == "*")
					{
						return;
					}
					else
					{
						cout << "Player did not confirm correctly."
							<< endl;
					}
					return;
				}
				return;
			}
		}

		if (playerHand.empty() && !deck.empty())
		{
			cout << "Your hand is empty. Drawing a card from the deck..."
				<< endl;
			playerHand.push_back(deck.back());
			deck.pop_back();
			cout << "You drew a " << playerHand.back() << "." << endl;
		}

		if (!playerHand.empty())
		{
			cout << "Enter the type of card you want to ask for (e.g., '2', 'K'): ";
		}

		string cardType;
		cin >> cardType;

		if (!hasCard(playerHand, cardType))
		{
			cout << "You cannot ask for a card you do not have. Try again."
				<< endl;
			continue;
		}

		if (hasCard(computerHand, cardType))
		{
			cout << "Computer gives you all " << cardType << " cards."
				<< endl;
			removeCards(computerHand, playerHand, cardType);
			collectSets(playerHand, playerSets, "Player");

			while (playerHand.empty() && !deck.empty())
			{
				cout << "Your hand is empty. Drawing a card from the deck..."
					<< endl;
				playerHand.push_back(deck.back());
				deck.pop_back();
				cout << "You drew a " << playerHand.back() << "."
					<< endl;
			}
		}
		else
		{
			cout << "Computer does not have any " << cardType
				<< " cards. Drawing from deck." << endl;
			if (!deck.empty())
			{
				string drawnCard = deck.back();
				deck.pop_back();
				cout << "You drew a " << drawnCard << "." << endl;
				playerHand.push_back(drawnCard);

				if (drawnCard == cardType)
				{
					cout << "You drew the card you asked for! Continue your turn."
						<< endl;
					collectSets(playerHand, playerSets, "Player");
					continue;
				}
			}
			break;
		}
	}
}

void computerTurn(
	vector<string>& computerHand,
	vector<string>& playerHand,
	vector<string>& deck,
	vector<string>& computerSets,
	vector<string>& playerSets
)
{
	if (checkEndOfFirstPhase(playerHand, computerHand, deck))
	{
		return;
	}

	if (computerHand.empty() && deck.empty())
	{
		cout << "Computer's hand is empty, and the deck is empty! "
			<< "Moving to the second phase of the game." << endl;
		secondPhase(computerSets, playerSets);

		if (computerSets.empty() || playerSets.empty())
		{
			cout << "End of the game! ";
			cout << "\nComputer have collected all the collections! Computer wins!"
				<< endl;
			string input;

			while (true)
			{
				cout << "Player, type '*' to end the game: ";
				cin >> input;

				if (input == "*")
				{
					return;
				}
				else
				{
					cout << "Player did not confirm correctly."
						<< endl;
				}
				return;
			}
			return;
		}
	}

	while (computerHand.empty() && !deck.empty())
	{
		cout << "Computer's hand is empty. Drawing a card from the deck..."
			<< endl;
		computerHand.push_back(deck.back());
		deck.pop_back();
		cout << "Computer drew a " << computerHand.back() << "." << endl;
	}

	collectSets(computerHand, computerSets, "Computer");
	cout << "Computer's turn." << endl;
	collectSets(computerHand, computerSets, "Computer");

	if (!computerHand.empty())
	{
		string cardType = computerHand[rand() % computerHand.size()];
		cout << "Computer asks for: " << cardType << endl;

		if (hasCard(playerHand, cardType))
		{
			cout << "Player gives all " << cardType
				<< " cards to the Computer." << endl;
			string input;

			while (true)
			{
				cout << "Player, type '*' to give your cards to the Computer: ";
				cin >> input;

				if (input == "*")
				{
					collectSets(computerHand, computerSets, "Computer");
					removeCards(playerHand, computerHand, cardType);
					cout << "Player has given the "
						<< cardType << " cards." << endl;
					break;
				}
				else
				{
					cout << "Player did not confirm correctly." << endl;
				}
			}

			while (computerHand.empty() && !deck.empty())
			{
				cout << "Computer's hand is empty. Drawing a card from the deck..."
					<< endl;
				computerHand.push_back(deck.back());
				deck.pop_back();
				cout << "Computer drew a " << computerHand.back() << "."
					<< endl;
			}
		}
		else
		{
			cout << "Player does not have any " << cardType
				<< " cards. Computer draws from deck." << endl;
			if (!deck.empty())
			{
				string drawnCard = deck.back();
				deck.pop_back();
				cout << "Computer drew a " << drawnCard << "." << endl;
				computerHand.push_back(drawnCard);

				if (drawnCard == cardType)
				{
					cout << "Computer drew the card it asked for! Continuing its turn."
						<< endl;
					return;
				}
			}
		}
	}
}

int main()
{
	vector<string> deck;
	vector<string> playerHand;
	vector<string> computerHand;
	vector<string> playerSets;
	vector<string> computerSets;

	initializeDeck(deck);
	shuffleDeck(deck);
	dealCards(deck, playerHand, 22);
	dealCards(deck, computerHand, 22);

	while (!checkEndOfFirstPhase(playerHand, computerHand, deck))
	{
		playerTurn(playerHand, computerHand, deck, playerSets, computerSets);

		if (checkEndOfFirstPhase(playerHand, computerHand, deck))
		{
			break;
		}
		computerTurn(computerHand, playerHand, deck, computerSets, playerSets);
	}
	return 0;
}