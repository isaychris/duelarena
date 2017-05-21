// ===============================================================
// Author: iSayChris
// Date: 12/22/2016
//
// Project: Duel Arena
// Version: 1.7
// Description: The best game ever.
//================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

///////////////// STRUCTS //////////////////////
struct skill {
	int level;
} strength, hitpoints;

struct item {
	string name;
	int str_bonus;
	string description;
	int price;
} whip, ags, lightsaber;

struct database {
	item whip = { "Whip", 82, "A weapon from the abyss", 50000 };
	item ags = { "Armadyl godsword", 132, "A beautiful, heavy sword", 75000 };
	item lightsaber = { "Lightsaber", 170, "Come to the dark side...", 100000 };
	item gun = { "Gun", 400, "Whats brackin bluh", 250000 };
	item katana = { "Katana", 250, "Ancient weapon from the hidden village", 500000 };
	item brass = { "Brass Nuckles", 50, "Ouch thats gotta hurt", 30000 };
	item secret = { "Secret", 500, "Hah, got em!", 1000000 };
} database;

struct inventory {
	vector<item> data = { database.whip, database.ags, database.lightsaber };
} inv;

struct player {
	inventory inv;
	item def = database.whip;
	skill strength = { 99 };
	skill hitpoints = { 99 };
	int max = 0;
	int style = 3;
};

struct statistics {
	float wins = 0;
	float loss = 0;
	float winsPerc = 0;
	float lossPerc = 0;
};

/////////////////////////////////////////////


class duelarena {
public:
	duelarena();
	void PrintMenu();
	void myPause();
	void insert(item product);
private:
	//betting & credits
	int avaCredits = 100000;
	int bet = 0;
	int choice;
	void check(string input);
	void credits();

	//statistics
	statistics dice;
	statistics stake;
	statistics diceduel;
	statistics hangman;

	void print_stats(statistics & x);

	//store
	vector<item> store = { database.brass, database.whip, database.ags, database.lightsaber,
		database.gun, database.katana, database.secret };
	void view_store();
	void buy(int item);

	//inventory
	void inventory();

	//cheat codes
	string code;
	void cheatCodes();

	//dicing
	void Play_Dicing();
	void Play_DiceDuel();

	//staking
	player p1;
	player p2;
	string winner;
	void Play_Staking();
	void maxHit(player & p);

	//hangman
	vector<string> wordList = { "WEEABOO", "HANGMAN", "APPLE", "KEYBOARD", "LAPTOP", "ALPABET", "NARUTO" };
	string hidden;
	string word;
	char letter;
	char again = 'y';
	int tries = 5;
	void prompt();
	void Play_Hangman();
	void insertWord(string word);
	void shuffle();
	void guess(char letter);
};

// calculates max hit of default weapon.
void duelarena::maxHit(player &p) {
	p.max = ((1.3 + ((p.strength.level + p.style) / 10) + (p.def.str_bonus / 80) + (((p.strength.level + p.style) * p.def.str_bonus) / 640)));
}

// k/m/b system
void duelarena::check(string input) {
	input.back() = toupper(input.back());

	if (input.back() == 'K') {
		input.pop_back();
		bet = atoi(input.c_str()) * 1000;
		//bet = stoi(input) * 1000;
	}
	else if (input.back() == ('M')) {
		input.pop_back();
		bet = atoi(input.c_str()) * 1000000;
		//bet = stoi(input) * 1000000;
	}
	else if (input.back() == ('B')) {
		input.pop_back();
		bet = atoi(input.c_str()) * 1000000000;
		//bet = stoi(input) * 1000000000;
	}

	else {
		bet = atoi(input.c_str());
		//bet = stoi(input);
	}
}

//credit system
void duelarena::credits() {
	string input;

	cout << "Enter betting amount: ";
	cin >> input;
	check(input);

	if (avaCredits == 0) {
		cout << "You don't have enough coins to continue. # cleaned.";
		cout << " " << endl;
		PrintMenu();
	}

	while (bet > avaCredits) {
		cout << "You don't have enough coins. \nEnter again: ";
		cin >> bet;
	}
}

// prints out the stats of selected game
void duelarena::print_stats(statistics &x) {
	if (x.wins > 0 || x.loss > 0) {
		x.winsPerc = (x.wins / (x.wins + x.loss)) * 100;
		x.lossPerc = (x.loss / (x.wins + x.loss)) * 100;
	}

	cout << " " << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Wins: " << x.wins << " || %" << x.winsPerc << endl;
	cout << "Loss: " << x.loss << " || %" << x.lossPerc << endl;
	cout << "---------------------------------------------" << endl;
	cout << " " << endl;

	cout << "Coins: $" << avaCredits << endl;
	cout << "" << endl;

	credits();
}

//Dicing System
void duelarena::Play_Dicing() {
	char again;

	do {
		int diceRoll = (rand() % 100);
		string plusminus;

		cout << "  __________________________________________   " << endl;
		cout << "<| ======    DUEL ARENA - Dicing     ====== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;
		cout << "Roll a 55 or higher to win your bet. " << endl;

		print_stats(dice);

		cout << "     ____              " << endl;
		cout << "    /\\' .\\    _____    " << endl;
		cout << "   /: \\___\\  / .  /\\   " << endl;
		cout << "   \\' / . / /____/..\\  " << endl;
		cout << "    \\/___/  \\'  '\\  /  " << endl;
		cout << "             \\'__'\\/   " << endl;

		cout << " " << endl;
		cout << "[Rolling dice: " << diceRoll << "]" << endl;
		cout << " " << endl;

		if (diceRoll > 55) {
			cout << "Congratulations, you won the bet!" << endl;
			avaCredits = avaCredits - bet;
			avaCredits = avaCredits + (bet * 2);

			plusminus = "+";

			++dice.wins;
		}
		else {
			cout << "Sorry, you loss the bet!" << endl;
			avaCredits = avaCredits - bet;

			plusminus = "-";

			++dice.loss;
		}

		cout << " " << endl;
		cout << "Spoils = " << plusminus << " " << bet << endl;

		cout << " " << endl;

		cout << "=============================================" << endl;
		cout << "Coins: " << "$" << avaCredits << endl;
		cout << "=============================================" << endl;

		cout << "Play Again? (y/n): ";
		cin >> again;

	} while (again == 'y');
	if (again == 'n') {
		PrintMenu();
	}
}


//Dicing System
void duelarena::Play_DiceDuel() {
	char again;

	do {
		int p1_diceRoll = (rand() % 100);
		int p2_diceRoll = (rand() % 100);

		string plusminus;

		cout << "  __________________________________________   " << endl;
		cout << "<| ======   DUEL ARENA - Dice Duel   ====== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;
		cout << "Roll higher than Player 2 to win your bet. " << endl;

		print_stats(diceduel);

		cout << "     ____              " << endl;
		cout << "    /\\' .\\    _____    " << endl;
		cout << "   /: \\___\\  / .  /\\   " << endl;
		cout << "   \\' / . / /____/..\\  " << endl;
		cout << "    \\/___/  \\'  '\\  /  " << endl;
		cout << "             \\'__'\\/   " << endl;


		cout << " " << endl;
		cout << "[Player 1 rolls: " << p1_diceRoll << "]" << endl;
		cout << "[Player 2 rolls: " << p2_diceRoll << "]" << endl;
		cout << " " << endl;

		if (p1_diceRoll == p2_diceRoll) {
			cout << "You both roll the same number. its a tie!" << endl;
		}

		if (p1_diceRoll > p2_diceRoll) {
			cout << "Congratulations, you won the bet!" << endl;
			avaCredits = avaCredits - bet;
			avaCredits = avaCredits + (bet * 2);

			plusminus = "+";

			++diceduel.wins;

			cout << " " << endl;
			cout << "Spoils = " << plusminus << " " << bet << endl;

			cout << " " << endl;

		}
		else {
			cout << "Sorry, you loss the bet!" << endl;
			avaCredits = avaCredits - bet;

			plusminus = "-";

			++diceduel.loss;

			cout << " " << endl;
			cout << "Spoils = " << plusminus << " " << bet << endl;

			cout << " " << endl;

		}

		cout << "=============================================" << endl;
		cout << "Coins: " << "$" << avaCredits << endl;
		cout << "=============================================" << endl;

		cout << "Play Again? (y/n): ";
		cin >> again;

	} while (again == 'y');
	if (again == 'n') {
		PrintMenu();
	}
}

//Staking System
void duelarena::Play_Staking() {

	char again;

	do {
		string plusminus;
		int i = 0;
		int pid = 1 + (rand() % 2);
		int p1_hit;
		int p2_hit;

		cout << "  __________________________________________   " << endl;
		cout << "<| ======    DUEL ARENA - Staking    ====== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;
		cout << "Player 1 and Player 2 fight to the death." << endl;

		print_stats(stake);

		cout << " " << endl;

		cout << "(1) Player 1" << endl;
		cout << "(2) Player 2" << endl;
		cout << " " << endl;
		cout << "Bet on Player(?): ";
		cin >> choice;

		while (choice > 2 || choice == 0) {
			cout << "Invalid player choice, enter again: ";
			cin >> choice;
		}

		cout << " " << endl;
		cout << "           /\\                            " << endl;
		cout << " _         )( ___________________________      " << endl;
		cout << "(_)///////(**)_______Fight!!!____________>     " << endl;
		cout << "           )(                          " << endl;
		cout << "           \\/                            " << endl;
		cout << " " << endl;

		maxHit(p1);
		maxHit(p2);

		if (pid == 1) {
			while (p1.hitpoints.level > 0 && p2.hitpoints.level > 0) {
				++i;

				if (p1.hitpoints.level > 0 && p2.hitpoints.level > 0) {
					p1_hit = rand() % p1.max;
					cout << "Player 1: Hits = " << left << setw(15) << p1_hit << "HP = " << p1.hitpoints.level << endl;
					p2.hitpoints.level = p2.hitpoints.level - p1_hit;
				}

				if (p1.hitpoints.level > 0 && p2.hitpoints.level > 0) {
					p2_hit = rand() % p2.max;
					cout << "Player 2: Hits = " << left << setw(15) << p2_hit << "HP = " << p2.hitpoints.level << endl;
					p1.hitpoints.level = p1.hitpoints.level - p2_hit;
				}
			}
		}

		else if (pid == 2) {
			while (p1.hitpoints.level > 0 && p2.hitpoints.level > 0) {
				++i;

				if (p1.hitpoints.level > 0 && p2.hitpoints.level > 0) {
					p2_hit = rand() % p2.max;
					cout << "Player 2: Hits = " << left << setw(15) << p2_hit << "HP = " << p2.hitpoints.level << endl;
					p1.hitpoints.level = p1.hitpoints.level - p2_hit;
				}

				if (p1.hitpoints.level > 0 && p2.hitpoints.level > 0) {
					p1_hit = rand() % p1.max;
					cout << "Player 1: Hits = " << left << setw(15) << p1_hit << "HP = " << p1.hitpoints.level << endl;
					p2.hitpoints.level = p2.hitpoints.level - p1_hit;
				}
			}
		}

		if (p1.hitpoints.level <= 0) {
			cout << " " << endl;
			cout << "Player 1 DEFEATED with HP = " << p1.hitpoints.level << endl;
			cout << " " << endl;
			cout << "---------------------------------------------" << endl;
			cout << " " << endl;

			if (choice == 2) {
				cout << "Congratulation, you won the bet!" << endl;
				avaCredits = avaCredits - bet;
				avaCredits = avaCredits + (bet * 2);

				winner = "Player 2";

				plusminus = "+";

				++stake.wins;
			}
			else if (choice == 1) {
				cout << "Sorry, you loss the bet!" << endl;
				avaCredits = avaCredits - bet;

				winner = "Player 2";
				plusminus = "-";

				++stake.loss;
			}
		}

		else if (p2.hitpoints.level <= 0) {
			cout << " " << endl;
			cout << "Player 2 DEFEATED with HP = " << p2.hitpoints.level << endl;
			cout << " " << endl;
			cout << "---------------------------------------------" << endl;
			cout << " " << endl;

			if (choice == 1) {
				cout << "Congratulation, you won the bet!" << endl;
				avaCredits = avaCredits - bet;
				avaCredits = avaCredits + (bet * 2);

				winner = "Player 1";
				plusminus = "+";

				++stake.wins;
			}

			else if (choice == 2) {
				cout << "Sorry, you loss the bet!" << endl;
				avaCredits = avaCredits - bet;

				winner = "Player 1";
				plusminus = "-";

				++stake.loss;
			}
		}

		cout << " " << endl;
		cout << "Winner = " << winner << endl;
		cout << "Spoils = " << plusminus << " " << bet << endl;

		p1.hitpoints.level = 99;
		p2.hitpoints.level = 99;
		choice = 0;

		cout << " " << endl;

		cout << "=============================================" << endl;
		cout << "Coins: " << "$" << avaCredits << endl;
		cout << "=============================================" << endl;

		cout << "Play Again? (y/n): ";
		cin >> again;

	} while (again == 'y');
	if (again == 'n') {
		PrintMenu();
	}
}

void pause() {
	cout << "Press [Enter] to continue." << endl;
	cin.get();
}

//Cheat System
void duelarena::cheatCodes() {
	cout << "  __________________________________________   " << endl;
	cout << "<| ========        Add Code        ======== |>" << endl;
	cout << "<|__________________________________________|> " << endl;
	cout << "" << endl;

	cout << " " << endl;
	cout << "Redeemable codes:" << endl;
	cout << "---------------------------------------------" << endl;
	cout << " - 'money1' = 10k" << endl;
	cout << " - 'money2' = 100k" << endl;
	cout << " - 'bank' = 1M" << endl;
	cout << " - 'cash' = 10M" << endl;
	cout << " - 'showmethemoney' = 100M" << endl;
	cout << " - 'strpot1' = increases max hit of p1 by 15." << endl;
	cout << " - 'strpot2' = increases max hit of p2 by 15." << endl;
	cout << " - 'hacker1' = sets p1 hp to 9999" << endl;
	cout << " - 'hacker2' = sets p2 hp to 9999" << endl;
	cout << " - 'gun' = adds gun to p1 inventory" << endl;
	cout << "---------------------------------------------" << endl << endl;

	cout << "Enter code: ";
	cin >> code;

	cout << " " << endl;

	if (code == "money1") {
		avaCredits = avaCredits + 10000;
		cout << "[You successfully redeem 'money1' for 10,000 coins]" << endl;
	}
	else if (code == "money2") {
		avaCredits = avaCredits + 100000;
		cout << "[You successfully redeem 'money2' for 100,000 coins]" << endl;
	}
	else if (code == "bank") {
		avaCredits = avaCredits + 1000000;
		cout << "[You successfully redeem 'bank' for 1,000,000 coins]" << endl;
	}
	else if (code == "cash") {
		avaCredits = avaCredits + 10000000;
		cout << "[You successfully redeem 'cash' for 10,000,000 coins]" << endl;
	}
	else if (code == "showmethemoney") {
		avaCredits = avaCredits + 100000000;
		cout << "[You successfully redeem 'showmethemoney' for 100,000,000 coins]" << endl;
	}
	else if (code == "strpot1") {
		p1.max = p1.max + 15;
		cout << "[Player 1 max hit increased by 15]" << endl;
	}
	else if (code == "strpot2") {
		p2.max = p2.max + 15;
		cout << "[Player 2 max hit increased by 15]" << endl;
	}
	else if (code == "hacker1") {
		p1.hitpoints.level = 9999;
		cout << "[Player 1 hp set to 9999]" << endl;
	}
	else if (code == "hacker2") {
		p2.hitpoints.level = 9999;
		cout << "[Player 2 hp set to 9999]" << endl;
	}
	else if (code == "gun") {
		p1.inv.data.push_back(database.gun);
		cout << "[Added gun to Player 1 inventory]" << endl;
	}
	else if (code == "secret") {
		p1.inv.data.push_back(database.secret);
		cout << "[Added secret to Player 1 inventory]" << endl;
	}

	else {
		cout << "You entered an invalid code, please try again." << endl;
	}

	cout << " " << endl;
	cout << "---------------------------------------------" << endl;

	PrintMenu();

}

//inventory system
void duelarena::inventory() {
	int id;

	char input = 'y';
	cout << "  __________________________________________   " << endl;
	cout << "<| ========        Inventory       ======== |>" << endl;
	cout << "<|__________________________________________|> " << endl;
	cout << "" << endl;
	cout << "View your inventory here." << endl << endl;


	cout << "Player 1 inventory:" << endl;
	for (int i = 0; i < p1.inv.data.size(); i++) {
		cout << " - slot [" << i << "]: ";
		cout << p1.inv.data[i].name << endl;
	}

	cout << endl;
	cout << "Current weapon equiped:" << endl;
	cout << " - " << p1.def.name << endl;


	cout << " " << endl;
	cout << "Would you like to equip an item? [y/n]: ";
	cin >> input;

	if (input == 'y') {
		cout << endl;
		cout << "Equip item [?]: ";
		cin >> id;

		while (id < 0 || id > p1.inv.data.size()) {
			cout << "Incorrect input. try again: ";
			cin >> id;
			cout << endl;
		}

		p1.def = p1.inv.data[id];
		cout << " - " << p1.inv.data[id].name << " has been equiped." << endl;
	}

	cout << endl;
	cout << "---------------------------------------------" << endl;

	PrintMenu();
}

//inserts item into store
void duelarena::insert(item product) {
	store.push_back(product);
}

//buy helper.
void duelarena::buy(int item) {
	char input = 'y';
	double change;

	cout << " - item: " << store[item].name << endl;
	cout << " - description: '" << store[item].description << "'" << endl;
	cout << " - str bonus: " << store[item].str_bonus << endl;
	cout << " - price: $" << store[item].price << endl << endl;

	cout << "Purchase item? [y/n]: ";
	cin >> input;

	if (input == 'y') {
		if (avaCredits > store[item].price || avaCredits < avaCredits) {
			avaCredits = avaCredits - store[item].price;
			p1.inv.data.push_back(store[item]);

			cout << " - " << store[item].name << " added to inventory ..." << endl;
			cout << " - Current wallet = " << avaCredits << endl << endl;
		}
		else {
			cout << "not enough money for this purchase ..." << endl;
		}
	}
}

void duelarena::prompt() {
	cout << endl;
	cout << "Would you like to play again? [y/n]: ";
	cin >> again;
}

void duelarena::insertWord(string word) {
	wordList.push_back(word);
}

void duelarena::shuffle() {
	random_shuffle(wordList.begin(), wordList.end());
}

void duelarena::guess(char letter) {
	if (word.find(letter) != -1) {
		for (int i = 0; i < word.length(); i++) {
			if (word.at(i) == letter) {
				hidden.at(i) = letter;
			}
		}
	}

	else {
		tries--;
		cout << " - Incorrect. Tries left: " << tries << endl;
	}
}

void duelarena::Play_Hangman() {
	int i = 0;
	char again = 'y';
	string plusminus;
	shuffle();

	while (again == 'y' && i < wordList.size()) {
		tries = 5;

		cout << "  __________________________________________   " << endl;
		cout << "<| ======          HANGMAN           ====== |>" << endl;
		cout << "<|__________________________________________|> " << endl;
		cout << " " << endl;
		cout << "Guess the word correctly and win your bet. " << endl;

		word = wordList[i++];
		hidden = string(word.size(), '_');

		print_stats(hangman);


		while (tries > 0) {

			cout << "Your word is: " << hidden << endl << endl;
			//cout << "Your word is: " << word << endl << endl;

			cout << "Guess letter: ";
			cin >> letter;
			cin.ignore(32767, '\n');

			letter = toupper(letter);
			guess(letter);

			if (hidden == word) {
				cout << " - The word was: " << word << endl;
				cout << " - Congrats, You win the game! " << endl;

				avaCredits = avaCredits + bet;
				plusminus = "+";
				++hangman.wins;
				break;
			}

			else if (tries == 0) {
				cout << " - The word was: " << word << endl;
				cout << " - Oh dear, you are dead. " << endl;

				avaCredits = avaCredits - bet;
				plusminus = "-";
				++hangman.loss;
				break;
			}
		}

		cout << " " << endl;
		cout << "Spoils = " << plusminus << " " << bet << endl;

		cout << " " << endl;

		cout << "=============================================" << endl;
		cout << "Coins: " << "$" << avaCredits << endl;
		cout << "=============================================" << endl;

		cout << "Play Again? (y/n): ";
		cin >> again;
	}

	cout << " " << endl;
	cout << "---------------------------------------------" << endl;

	PrintMenu();
}


// store system
void duelarena::view_store() {
	cout << "  __________________________________________   " << endl;
	cout << "<| ========          Store         ======== |>" << endl;
	cout << "<|__________________________________________|> " << endl;
	cout << "" << endl;
	cout << "Welcome to the General Store!" << endl;
	cout << "" << endl;

	int select;

	cout << "Coins = $" << avaCredits << endl;
	cout << endl;
	cout << left;
	cout << setw(9) << "code" << setw(20) << "item" << setw(8) << "str" << "price" << endl;
	cout << "----------------------------------------------" << endl;

	if (!store.empty()) {
		for (int i = 0; i < store.size(); i++) {
			cout << left;
			cout << " " << setw(8) << i << setw(20) << store[i].name << setw(8) << store[i].str_bonus << "$" << store[i].price << endl;
		}

		cout << endl;
		cout << "Enter [code]: ";
		cin >> select;

		while (select < 0 || select > store.size() - 1) {
			cout << "invalid choice, Enter [code]:";
			cin >> select;
			cout << endl;
		}
		buy(select);
	}

	else {
		cout << "empty" << endl;
	}

	cout << " " << endl;
	cout << "---------------------------------------------" << endl;

	PrintMenu();
}

duelarena::duelarena()
{

}

void duelarena::PrintMenu()
{
	int myChoice = 0;

	cout << " " << endl;
	cout << "  __________________________________________   " << endl;
	cout << "<| ========        Main Menu       ======== |>" << endl;
	cout << "<|__________________________________________|> " << endl;
	cout << " " << endl;
	cout << "(1): [Play] Dicing." << endl;
	cout << "(2): [Play] Dice Duel." << endl;
	cout << "(3): [Play] Staking." << endl;
	cout << "(4): [Play] Hangman." << endl;
	cout << "(5): [View] Inventory." << endl;
	cout << "(6): [Buy] Store." << endl;
	cout << "(7): [Add] Code." << endl;
	cout << "(8): About." << endl;
	cout << "(9): Exit." << endl;
	cout << " " << endl;
	cout << "---------------------------------------------" << endl;
	cout << " " << endl;
	cout << "Enter menu(?): ";
	cin >> myChoice;

	while (myChoice > 9 || myChoice < 0) {
		cout << "Invalid choice. Enter Menu(?): ";
		cin >> myChoice;
	}

	switch (myChoice)
	{
	case 1:

		Play_Dicing();

		break;
	case 2:

		Play_DiceDuel();

		break;
	case 3:

		Play_Staking();

		break;
	case 4:
		Play_Hangman();
		break;

	case 5:
		inventory();
		break;

	case 6:
		view_store();
		break;

	case 7:
		cheatCodes();
		break;

	case 8:

		cout << "  __________________________________________   " << endl;
		cout << "<| Created by iSayChris - Version 1.7       |>" << endl;
		cout << "<|__________________________________________|> " << endl;

		cout << " " << endl;
		cout << "---------------------------------------------" << endl;
		cout << "" << endl;

		myPause();

		PrintMenu();

		break;
	}
}

void duelarena::myPause()
{
	cout << "Press [Enter] to go back to Main Menu." << endl;
	cin.clear();
	cin.sync();
	cin.get();
}


int main()
{
	duelarena o;

	cout << " " << endl;
	cout << "// Gambling Simulator 2016" << endl;
	cout << "// Created by iSayChris" << endl;
	cout << "// Version : 1.7" << endl;

	srand(unsigned(time(NULL)));
	o.PrintMenu();

	return 0;
}

