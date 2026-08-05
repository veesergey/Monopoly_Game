#include "Game.h"
#include "player.h"
#include "Property.h"
#include "card.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<stdlib.h>
#include<time.h>

Game::Game()
{

	srand(int(time(0)));

	//Adds sigils to sigil vector property of game object, for players to choose
	sigilList.push_back("@");
	sigilList.push_back("#");
	sigilList.push_back("$");
	sigilList.push_back("%");
	sigilList.push_back("&");
	sigilList.push_back("*");
	sigilList.push_back("!");
	sigilList.push_back("^");
	sigilList.push_back("~");
	sigilList.push_back("+");
	
	

	//Creates Properties (All spaces)
	Property p0("Go", 0, 0 , true);
	Property p1("Farm", 60, 40, false);
	Property p2("Quest", 0, 0, true);
	Property p3("Cave", 60, 40, false);
	Property p4("RockyR", 200, 0, false);
	Property p5("Smithy", 100, 80, false);
	Property p6("IncomeTax", 0, 0, true);
	Property p7("Inn", 120, 80, false);
	Property p8("Stocks", 0, 0, true);
	Property p9("Torch", 150, 0, false);
	Property p10("Cart", 200, 0, false);
	Property p11("Hamlet", 180, 140, false);
	Property p12("W.Pump", 150, 0, false);
	Property p13("TwnSqr", 0, 0, true);
	Property p14("Church", 260, 140, false);
	Property p15("Scroll", 0, 0, true);
	Property p16("Barn", 260, 160, false);
	Property p17("SmoothR", 200, 0, false);
	Property p18("Mill", 280, 160, false);
	Property p19("LuxTax", 0, 0, true);
	Property p20("Oasis", 280, 160, false);
	Property p21("Sheriff", 0, 0, true);
	Property p22("Tavern", 320, 200, false);
	Property p23("Cart2", 200, 0, false);
	Property p24("Granary", 350, 220, false);
	Property p25("Mansion", 400, 250, false);

	//Adds unowned properties to unowned Properties list. these are properties players can purchase
	unownedProperty.push_back(p1);
	unownedProperty.push_back(p3);
	unownedProperty.push_back(p4);
	unownedProperty.push_back(p5);
	unownedProperty.push_back(p7);
	unownedProperty.push_back(p9);
	unownedProperty.push_back(p10);
	unownedProperty.push_back(p11);
	unownedProperty.push_back(p14);
	unownedProperty.push_back(p16);
	unownedProperty.push_back(p17);
	unownedProperty.push_back(p18);
	unownedProperty.push_back(p19);
	unownedProperty.push_back(p20);
	unownedProperty.push_back(p22);
	unownedProperty.push_back(p23);
	unownedProperty.push_back(p24);
	unownedProperty.push_back(p25);
	
	board.push_back(p0);
	board.push_back(p1);
	board.push_back(p2);
	board.push_back(p3);
	board.push_back(p4);
	board.push_back(p5);
	board.push_back(p6);
	board.push_back(p7);
	board.push_back(p8);
	board.push_back(p9);
	board.push_back(p10);
	board.push_back(p11);
	board.push_back(p12);
	board.push_back(p13);
	board.push_back(p14);
	board.push_back(p15);
	board.push_back(p16);
	board.push_back(p17);
	board.push_back(p18);
	board.push_back(p19);
	board.push_back(p20);
	board.push_back(p21);
	board.push_back(p22);
	board.push_back(p23);
	board.push_back(p24);
	board.push_back(p25);

	welcome();

	createPlayers();

	addPlayersToBoard();
}

void Game::welcome() {
	//Welcomes players
	std::cout << "\nWelcome to Monopoly!" << std::endl;
}

int Game::getHumans()
{
	//gets the number of human players from the user, validates the entry for 1-6 and for the entry being a digit.
	int numHumans;

	std::cout << "Enter the number of human players (1-6): ";

	while (!(std::cin >> numHumans) || numHumans < 1 || numHumans > 6) { //not a number
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Enter the number of human players (1-6): ";

	}

	return numHumans;
}

void Game::createPlayers() {
	//Uses get humans to assign a numHumans Int.
	int numHumans = getHumans();

	//For every human make a player.
	for (int x = 0; x < numHumans; x++) {
		std::string name;
		std::string sigil;
		bool validSigil = false;

		//Name is entered, verified to be under 8 in length.
		while (name.length() > 4 || name.length() < 1) {
			std::cout << "Enter name for player " << (x + 1) << " (Must be under 4 characters): ";
			std::cin >> name;
		}
		//makes sure a valid sigil is picked from a list.
		while (validSigil == false) {
			std::cout << "Available Sigils" << std::endl;
			for (std::string sigil : sigilList) {
				std::cout << sigil << " ";
			}
			std::cout << "\nEnter sigil for " << name << " (Must be 1 character): ";
			std::cin >> sigil;
			std::vector<std::string>::iterator sigilToAssign = find(sigilList.begin(), sigilList.end(), sigil);
			if (sigilToAssign == sigilList.end())
				std::cout << "Not a valid sigil." << std::endl;
			else {
				sigilList.erase(sigilToAssign);
				validSigil = true;
			}

		}
		//adds the created player to the game objects list of players
		playerList.push_back(Player(name, sigil, 1000));
	}
}

void Game::printPlayers(std::vector<Player> &playerList) {
	// This function takes a vector list of players (reference) and prints all the players out, their names, money, and sigil.
	std::cout << "List of Players: " << std::endl;
	for (Player player : playerList) {
		std::cout << "Name: " << player.getName() << std::endl;
		std::cout << "Sigil: " << player.getSigil() << std::endl;
		std::cout << "Money: " << player.getMoney() << std::endl;
	}
}

void printProperties(std::vector<Property> &propertyList) {
	//Takes a vector list reference and prints out all the properties.
	std::cout << "List of Properties: " << std::endl;
	for (Property property : propertyList) {
		std::cout << "---------------------------------------" << std::endl;
		std::cout << "Name: " << property.getName() << std::endl;
		std::cout << "Cost: " << property.getCost() << std::endl;

	}
}

void Game::printTile(Property prop)
{ 
	std::string topLine = "---------------";
	std::cout << topLine << std::endl;
	std::cout << "|  " << std::setw(9) << prop.getName() <<  "  |" << std::endl;
	std::cout << "---------------" << std::endl;
	for (int x = 0; x < 1; x++) {
		std::cout << "|             |" << std::endl;
	}
	std::cout << "| ";
	std::string here;
	for (std::string x : prop.onTile) {
		here += x;
	}
	std::cout << std::setw(10) << here;
	std::cout << "  |" << std::endl;
	for (int x = 0; x < 2; x++) {
		std::cout << "|             |" << std::endl;
	}
	std::cout << topLine;
}

void Game::printTopRow(std::vector<Property> board, Player player) {
	//Passes the list of all spaces to be printed. Also the width and height of each space is passed. The width isnt the total width, its basically half the card minus the letters
	//prints the top row.

	//Prints the top part of the cards
	for (int i = 0; i < 127; i++) {
		std::cout << "=";
	}
	std::cout << "\n|";
	//prints the first 9 spaces(the top part, with the name)
	for (int x = 0; x < 9; x++) {
		std::cout << std::setw(7) << board[x].getName() << std::setw(6) << board[x].getOwner() << "|";
	}

	//Prints out stuff to the right of map------------------------------------------------------------------------------------------------------
	std::cout << std::setw(23) << "Current Player";

	std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------";
	
	std::cout << std::setw(22) << "-------------" << std::endl;


	//Starts Next Line of the space
	std::cout << "|"; //Left Side |
	//Prints what player sigils located on tile, for now it just prints empty onTileLists (attribute) or some I added in "monopoly" objects constructor.
	for (int x = 0; x < 9; x++) {
		std::cout << std::setw(6) << board[x].getOnTile() << std::setw(8) << "|" ; //Prints out what is on each tile. Should never be more than 6, therefore its setw is 6.
	}

	//Prints player name to the right of the map-------------------------------------------------------------------------------------------------------
	std::cout << std::setw(15) << "Name: " << std::setw(8) << player.getName();

	//Starts the next line of the space
	std::cout << std::endl; //New Line
	std::cout << "|"; //Left Side |

	//prints the cost
	for (int x = 0; x < 9; x++) {
		std::cout << "C:" << std::setw(3) << board[x].getCost() << std::setw(9) << "|";
	}

	//Prints out player money to the right of the map-------------------------------------------------------------------------------------------------------
	std::cout << std::setw(15) << "Money:" << std::setw(8) << player.getMoney();


	//Starts the next line of the spaces
	std::cout << std::endl; //New Line
	std::cout << "|"; //Left Side |

	//Prints rent of tile
	for (int x = 0; x < 9; x++) {
		std::cout << "R:" << std::setw(3) << board[x].getRent() << std::setw(9) << "|";
	}

	//Gets player pos, passes position board list, to call the properties getName function that returns a string to be printed. PRints out player position basically.
	std::cout << std::setw(15) << "Loc:  " << std::setw(8) << board[player.getPos()].getName();

	//Starts next line of spaces
	std::cout << std::endl; //New Line
	std::cout << "|";
	for (int x = 0; x < 9; x++) {
		std::cout << "U:" << std::setw(6) << board[x].getUpgrade() << std::setw(6) << "|";
	}
	std::cout << std::setw(15) << "Sigil:" << std::setw(8) << player.getSigil();
	std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------";
}

void Game::printMidRow1(std::vector<Property> board, int left, int right, Player player) {
	//The x and y passed is the element that is to be printed. This prints out the middle of the board. Trying to make this function useful for printing the whole middle.

	std::cout << std::endl;
	std::cout << "|" << std::setw(10) << board[left].getName() << std::setw(3) << board[left].getOwner() << "|"; //Prints the top of the lefternmost space name
	std::cout << std::setw(98) << "|" << std::setw(10) << board[right].getName() << std::setw(3) << board[right].getOwner() << "|";//Prints out top of the rightmost space name

	std::cout << std::endl; //Newline
	std::cout << "|" << std::setw(6) << board[left].getOnTile() << std::setw(8) << "|"; //Prints out the players on left tile
	std::cout << std::setw(98) << "|" << std::setw(6) << board[right].getOnTile() << std::setw(8) << "|";//Prints out players on right tile

	std::cout << std::setw(15) << "Owned Properties"; //Prints owned properties to the right of map

	std::cout << std::endl; //NL 
	std::cout << "|" <<"C:" << std::setw(3) << board[left].getCost() << std::setw(9) << "|"; //Prints cost, left tile
	std::cout << std::setw(98) << "|" << "C:" << std::setw(3) << board[right].getCost() << std::setw(9) << "|"; //Prints Cost, right tile

	for (Property prop : player.ownedProperty) {
		std::cout << prop.getName() << "...";
	}

	std::cout << std::endl; //NL
	std::cout << "|" << "R:" << std::setw(3) << board[left].getRent() << std::setw(9) << "|"; //Prints rent, left tile
	std::cout << std::setw(98) << "|" << "R:" << std::setw(3) << board[right].getRent() << std::setw(9) << "|"; //prints rent, right tile
	

	std::cout << std::endl; //If you still dont get that im using this as a new line, stop programming, take a break, reevaluate life choices. Im not saying this is a good way, but its MY WAY
	std::cout << "|" << "U:" << std::setw(6) << board[left].getUpgrade() << std::setw(6) << "|"; //Prints upgrades of left tile
	std::cout << std::setw(98) << "|" << "U:" << std::setw(6) << board[right].getUpgrade() << std::setw(6) << "|"; //prints upgrades of right tile 

	std::cout << "\n---------------" << std::setw(112) << "---------------";
	
	
}

void Game::printMidRow2(std::vector<Property> board, int left, int right, Player player) {
	//The x and y passed is the element that is to be printed. This prints out the middle of the board. Trying to make this function useful for printing the whole middle.

	std::cout << std::endl;
	std::cout << "|" << std::setw(10) << board[left].getName() << std::setw(3) << board[left].getOwner() << "|"; //Prints the top of the lefternmost space name
	std::cout << std::setw(98) << "|" << std::setw(10) << board[right].getName() << std::setw(3) << board[right].getOwner() << "|";//Prints out top of the rightmost space name

	std::cout << std::endl; //Newline
	std::cout << "|" << std::setw(6) << board[left].getOnTile() << std::setw(8) << "|"; //Prints out the players on left tile
	std::cout << std::setw(98) << "|" << std::setw(6) << board[right].getOnTile() << std::setw(8) << "|";//Prints out players on right tile

	std::cout << std::setw(15) << "Mortaged Properties"; //Prints owned properties to the right of map
	

	std::cout << std::endl; //NL 
	std::cout << "|" << "C:" << std::setw(3) << board[left].getCost() << std::setw(9) << "|"; //Prints cost, left tile
	std::cout << std::setw(98) << "|" << "C:" << std::setw(3) << board[right].getCost() << std::setw(9) << "|"; //Prints Cost, right tile
	for (Property prop : player.mortagedProperty) {
		std::cout << prop.getName() << "...";
	}
	std::cout << std::endl; //NL
	std::cout << "|" << "R:" << std::setw(3) << board[left].getRent() << std::setw(9) << "|"; //Prints rent, left tile
	std::cout << std::setw(98) << "|" << "R:" << std::setw(3) << board[right].getRent() << std::setw(9) << "|"; //prints rent, right tile

	std::cout << std::endl; //If you still dont get that im using this as a new line, stop programming, take a break, reevaluate life choices. Im not saying this is a good way, but its MY WAY
	std::cout << "|" << "U:" << std::setw(6) << board[left].getUpgrade() << std::setw(6) << "|"; //Prints upgrades of left tile
	std::cout << std::setw(98) << "|" << "U:" << std::setw(6) << board[right].getUpgrade() << std::setw(6) << "|"; //prints upgrades of right tile 

	std::cout << "\n---------------" << std::setw(112) << "---------------";


}

void Game::printMidRow(std::vector<Property> board, int left, int right, Player player) {
	//The x and y passed is the element that is to be printed. This prints out the middle of the board. Trying to make this function useful for printing the whole middle.

	std::cout << std::endl;
	std::cout << "|" << std::setw(10) << board[left].getName() << std::setw(3) << board[left].getOwner() << "|"; //Prints the top of the lefternmost space name
	std::cout << std::setw(98) << "|" << std::setw(10) << board[right].getName() << std::setw(3) << board[right].getOwner() << "|";//Prints out top of the rightmost space name

	std::cout << std::endl; //Newline
	std::cout << "|" << std::setw(6) << board[left].getOnTile() << std::setw(8) << "|"; //Prints out the players on left tile
	std::cout << std::setw(98) << "|" << std::setw(6) << board[right].getOnTile() << std::setw(8) << "|";//Prints out players on right tile

	std::cout << std::endl; //NL 
	std::cout << "|" << "C:" << std::setw(3) << board[left].getCost() << std::setw(9) << "|"; //Prints cost, left tile
	std::cout << std::setw(98) << "|" << "C:" << std::setw(3) << board[right].getCost() << std::setw(9) << "|"; //Prints Cost, right tile
	
	std::cout << std::endl; //NL
	std::cout << "|" << "R:" << std::setw(3) << board[left].getRent() << std::setw(9) << "|"; //Prints rent, left tile
	std::cout << std::setw(98) << "|" << "R:" << std::setw(3) << board[right].getRent() << std::setw(9) << "|"; //prints rent, right tile

	std::cout << std::endl; //If you still dont get that im using this as a new line, stop programming, take a break, reevaluate life choices. Im not saying this is a good way, but its MY WAY
	std::cout << "|" << "U:" << std::setw(6) << board[left].getUpgrade() << std::setw(6) << "|"; //Prints upgrades of left tile
	std::cout << std::setw(98) << "|" << "U:" << std::setw(6) << board[right].getUpgrade() << std::setw(6) << "|"; //prints upgrades of right tile 

	std::cout << "\n---------------" << std::setw(112) << "---------------";


}

void Game::printBotRow(std::vector<Property> board, Player player) {
	//NOTE!!!!!!!!!!!!!!!!!!!!!!!: This code is a copy and paste of the printTopRow function with some stuff changed around.
	std::cout << std::endl;
	for (int i = 0; i < 127; i++) {
		std::cout << "-";
	}
	std::cout << "\n|";
	
	//prints the first 9 spaces(the top part, with the name)
	for (int x = 21; x > 12; x--) {
		std::cout << std::setw(7) << board[x].getName() << std::setw(6) << board[x].getOwner() << "|";
	}
	std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	//Starts Next Line of the space
	std::cout << "|"; //Left Side |
					  //Prints what player sigils located on tile, for now it just prints empty onTileLists (attribute) or some I added in "monopoly" objects constructor.
	for (int x = 21; x > 12; x--) {
		std::cout << std::setw(6) << board[x].getOnTile() << std::setw(8) << "|"; //Prints out what is on each tile. Should never be more than 6, therefore its setw is 6.
	}

	//Starts the next line of the space
	std::cout << std::endl; //New Line
	std::cout << "|"; //Left Side |

					  //prints the cost
	for (int x = 21; x > 12; x--) {
		std::cout << "C:" << std::setw(3) << board[x].getCost() << std::setw(9) << "|";
	}
	//Starts the next line of the spaces
	std::cout << std::endl; //New Line
	std::cout << "|"; //Left Side |

					  //Prints rent of tile
	for (int x = 21; x > 12; x--) {
		std::cout << "R:" << std::setw(3) << board[x].getRent() << std::setw(9) << "|";
	}

	//Starts next line of spaces
	std::cout << std::endl; //New Line
	std::cout << "|";
	for (int x = 21; x > 12; x--) {
		std::cout << "U:" << std::setw(6) << board[x].getUpgrade() << std::setw(6) << "|";
	}
	std::cout << "\n-------------------------------------------------------------------------------------------------------------------------------";
}

void Game::printBoard(std::vector<Property> board, Player player) {
	printTopRow(board, player);
	printMidRow1(board, 25, 9, player);
	printMidRow2(board, 24, 10, player);
	printMidRow(board, 23, 11, player);
	printMidRow(board, 22, 12, player);
	printBotRow(board, player);
	
}  

void Game::addPlayersToBoard() {
	for (Player player : playerList) {
		std::string sigil = player.getSigil();
		int space = player.getPos();
		board[space].addToTile(sigil);
	}
}

void Game::playerTurns() {

	//While there is more than one player (while there is no winner)
	while (playerList.size() > 1) {
		//For each player..give the menu...to do stuff.
		for (Player &player : playerList) {
			std::cout << "-------------------------------" << std::endl;
			int choice = 0;
			bool canEndTurn = false;
			bool canMove = true;
			checkPlayers(playerList);
			
			while (choice != 5 || canEndTurn != true) {
				pauseConsole();
				clearScreen();
				printBoard(board, player);
				std::cout << std::endl; //New Line
				if (player.getPos() == 4 || player.getPos() == 10 || player.getPos() == 17 || player.getPos() == 23) {
					std::cout << "0. Travel RailRoad." << std::endl;
				}
				std::cout << "1. Move." << std::endl;
				std::cout << "2. Buy property. (" << board[player.getPos()].getName() << ")" << std::endl;
				std::cout << "3. Sell property." << std::endl;
				std::cout << "4. Buy hotel. ($200)" << std::endl;
				std::cout << "5. End Turn." << std::endl;
				std::cout << "6. See all players, money, sigils, and their properties" << std::endl;
				std::cout << "7. Cheat Menu. " << std::endl;
				std::cout << "8. Unmortage a property" << std::endl;
				std::cout << "9. Trade Properties" << std::endl;
				std::cout << "----------------------------" << std::endl;
				std::cout << player.getName() << ", What would you like to do?:";
				std::cin >> choice;
				int choice2 = 0;

				switch (choice) {
				case 0: //travel railroad. only prints the option when on railroad
					if (canMove) {
						clearScreen();
						printBoard(board, player);
						travelRailRoad(player);
						canEndTurn = true;
						canMove = false;
					}
					else {
						clearScreen();
						printBoard(board, player);
						std::cout << std::endl;
						std::cout << "\nYou already moved once this turn!" << std::endl;
					}
					
					break;
				case 1: //Move
					if (canMove) {
						clearScreen();
						printBoard(board, player);
						movePlayer(player);
						checkNewTile(board, playerList, player);
						canEndTurn = true;
						canMove = false;
					}
					else {
						clearScreen();
						printBoard(board, player);
						std::cout << std::endl;
						std::cout << "\nYou already moved once this turn!" << std::endl;
					}
					break;
				case 2: //buy property
					clearScreen();
					printBoard(board, player);
					std::cout << std::endl;
					player.buyProp(unownedProperty, board);
					break;
				case 3: // sell property
					clearScreen();
					printBoard(board, player);
					std::cout << std::endl;
					//Dont change the above

					player.sellProperty(unownedProperty, board);

					break;
				case 4: //upgrade prop
					clearScreen();
					printBoard(board, player);
					std::cout << std::endl;
					player.buyHotel(board);
					break;
				case 5: //end turn
					clearScreen();
					printBoard(board, player);
					std::cout << std::endl;
					if (canEndTurn) {
						std::cout << "Ending Turn." << std::endl;
					}
					else if (!canEndTurn) {
						clearScreen();
						printBoard(board, player);
						std::cout << std::endl;
						choice = 0;
						std::cout << player.getName() << " has not moved yet! Must move to end turn." << std::endl;
					}
						
					break;
				case 7: //cheat menu
					clearScreen();
					printBoard(board, player);
					std::cout << std::endl;
					std::cout << "Cheat Menu" << std::endl;
					std::cout << "1. Set Money" << std::endl;
					std::cout << "2. Set Position" << std::endl;
					std::cout << "What would you like to do?: ";
					std::cin >> choice2;

					switch (choice2) {

					case 1: 
						int newMoney;
						std::cout << "Whats the new money amount?: ";
						std::cin >> newMoney;
						player.setMoney(newMoney);
						break;
					case 2:
						int newPos;
						for (int i = 0; i < 5; i++) {
							std::cout << board[i].getName() << "..." << i << "   ";
						}
						std::cout << std::endl;
						for (int i = 5; i < 10; i++) {
							std::cout << board[i].getName() << "..." << i << "   ";
						}
						std::cout << std::endl;
						for (int i = 10; i < 15; i++) {
							std::cout << board[i].getName() << "..." << i << "   ";
						}
						std::cout << std::endl;
						for (int i = 15; i < 20; i++) {
							std::cout << board[i].getName() << "..." << i << "   ";
						}
						std::cout << std::endl;
						for (int i = 20; i < 25; i++) {
							std::cout << board[i].getName() << "..." << i << "   ";
						}
						std::cout << std::endl;
						std::cout << "Enter new position: ";
						std::cin >> newPos;
						movePlayerManual(player, newPos);
						checkNewTile(board, playerList, player);
						break;
					default: 
						std::cout << "Not a valid choice." << std::endl;
						break;
					}


					break;
				case 6: //print all players and money
					for (Player player : playerList) {
						std::cout << "\nName:" << player.getName() << std::endl;
						std::cout << "Sigil:" << player.getSigil() << std::endl;
						std::cout << "Money: " << player.getMoney() << std::endl;
						std::cout << "Properties:";
						for (Property prop : player.ownedProperty) {
							std::cout << prop.getName() << "...";
						}
						std::cout << "\n-------------------------------------" << std::endl;
					}
					break;
				case 8:
					if (player.mortagedProperty.size() == 0) {
						std::cout << "You have no mortaged properties." << std::endl;
					}
					else if (player.mortagedProperty.size() > 0) {
						for (Property prop : player.mortagedProperty) {
							std::cout << prop.getName() << ":$" << prop.getCost() << std::endl;
						}
						std::string toUnmortage;
						std::cout << "Which property do you want to unmortage?:";
						std::cin >> toUnmortage;
						int x = 0;
						for (Property prop : player.mortagedProperty) {
							if (toUnmortage == prop.getName() && player.getMoney() >= prop.getCost()) {
								player.unMortageProp(prop);
								board[player.getPos()].mortageStatus = false;
								player.ownedProperty.push_back(prop);
								player.mortagedProperty.erase(player.mortagedProperty.begin() + x);
							}x++;
						}

					}
				}

			}


		}
	}
}

int Game::diceRoll() {

	int diceRoll = rand() % 5 + 1; //random number between 1-5

	return diceRoll;
}

void Game::movePlayer(Player& player) {
	int oldPos = player.getPos();
	int dice1 = diceRoll();
	int dice2 = diceRoll();
	int total = dice1 + dice2;
	int newPos = oldPos + total;

	if (newPos <= 25) {
		newPos = newPos;
	}
	else if (newPos > 25) {
		newPos = newPos - 26;
		player.addMoney(200);
	}
	else
		std::cout << "ERROR WITH GAME::MOVEPLAYER FUNCTION." << std::endl;


	std::cout << "Old Position: " << oldPos << std::endl;
	std::cout << "Dice Roll1: " << dice1 << std::endl;
	std::cout << "Dice Roll2: " << dice2 << std::endl;
	std::cout << "total:" << total << std::endl;
	std::cout << "New Pos:" << newPos << std::endl;

	player.setPos(newPos);

	board[oldPos].takeOffTile(player.getSigil());
	board[newPos].addToTile(player.getSigil());
	
	std::cout << player.getName() << " has moved " << total << " spaces.";
	std::cout << "Position: " << newPos << std::endl;

}

void Game::movePlayerManual(Player& player, int newPos) {
	int oldPos = player.getPos();

	player.setPos(newPos);

	board[oldPos].takeOffTile(player.getSigil());
	board[newPos].addToTile(player.getSigil());

	std::cout << player.getName() << " has moved from " << board[oldPos].getName() << " to " << board[newPos].getName() << std::endl;
	
	
}

void Game::checkNewTile(std::vector<Property>& board, std::vector<Player>& playerList, Player& curPlayer) {
	//Checks the new tile the player landed on. If its owned/sheriff/community/chest etc, do something. 
	std::string curPos = board[curPlayer.getPos()].getName();
	if (curPos == "Sheriff") {
		movePlayerManual(curPlayer, 8);
		std::cout << curPlayer.getName() << " pays $50 to leave the Stockade!" << std::endl;
		curPlayer.subMoney(50);
	}
	else if (curPos == "Scroll") {
		std::cout << "Supposed to do the scroll thing!" << std::endl;
	}
	else if (curPos == "Quest") {
		std::cout << "Supposed to do the quest things." << std::endl;
	}
	else if (board[curPlayer.getPos()].getIsOwned() == true && board[curPlayer.getPos()].getRent() != 0 && board[curPlayer.getPos()].mortageStatus == false) {
		std::cout << board[curPlayer.getPos()].getName() << " is owned by " << board[curPlayer.getPos()].getOwner() << ". ";
		std::string personToPay = board[curPlayer.getPos()].getOwner();
		std::cout << curPlayer.getName() << " must pay " << personToPay << ".";
		int payAmount = board[curPlayer.getPos()].getRent();
		curPlayer.subMoney(payAmount); //subtracts the money of the current player...the cost of the spaces rent.
		//To find the owner of the space in the player list
		for (Player &player : playerList) {
			if (player.getName() == board[curPlayer.getPos()].getOwner()) {
				std::cout << "\n" << curPlayer.getName() << " paid " << board[curPlayer.getPos()].getOwner() << "$" << board[curPlayer.getPos()].getRent() << std::endl;
				player.addMoney(payAmount);
			}
		}
	}
	else if (curPos == "LuxTax") {
		std::cout << curPlayer.getName() << " has landed on Luxury Tax! Must pay a flat rate of $100 to the bank!" << std::endl;
		curPlayer.subMoney(100);
	}
	else if (curPos == "IncomeTax") {
		int totalAssets = 0;
		int totalHotels = 0;
		totalAssets += curPlayer.getMoney();

		for (Property prop : curPlayer.ownedProperty) {
			totalAssets += prop.getCost();
			totalAssets += prop.getRent();
		}
		

		int toPay = totalAssets / 10; //Hotel cost included here. 

		int choice = 0;

		while (choice != 1 && choice != 2) {
			std::cout << curPlayer.getName() << " has landed on Income Tax. Must pay 200 cash or 10% of total Assets (" << toPay << ")." << std::endl;
			std::cout << "1. Pay $200" << std::endl;
			std::cout << "2. Pay 10% (" << toPay << ")" << totalAssets << std::endl;
			std::cin >> choice;

			switch (choice) {
			case 1: {
				curPlayer.subMoney(200);
				std::cout << "Paid $200" << std::endl;
				break;
			}
			case 2: {
				curPlayer.subMoney(toPay);
				std::cout << "Paid 10% (" << toPay << ")." << std::endl;
				break;
			}
			default:
				std::cout << "Invalid Option" << std::endl;
			}
		}
	}
}
		

	


void Game::travelRailRoad(Player curPlayer) {
	std::string curPos = board[curPlayer.getPos()].getName();
	if (curPos == "Cart" || curPos == "Cart2" || curPos == "RockyR" || curPos == "SmoothR") {
		int choice = 0;
		while (choice != 1 && choice != 2) {
			std::cout << "Would you like to pay $100 to go to a different railroad? 1 for yes 2 for no:";
			std::cin >> choice;
			int toGo = 0;
			if (choice == 1) {
				while (toGo != 1 && toGo != 2 && toGo != 3 && toGo != 4) {

					std::cout << "What RR do you want to go to? \nRockyR = 1\nCart = 2\nSmoothR = 3\nCart2 = 4 \nChoice:";
					std::cin >> toGo;

					switch (toGo) {
					case 1:
						movePlayerManual(curPlayer, 4);
						break;
					case 2:
						movePlayerManual(curPlayer, 10);
						break;
					case 3:
						movePlayerManual(curPlayer, 17);
						break;
					case 4:
						movePlayerManual(curPlayer, 23);
						break;
					default:
						std::cout << "Not a valid choice." << std::endl;
						break;
					}
				}
			}
		}
	}
}

void Game::victory() {
	std::cout << "Congratulations! " << playerList[0].getName() << " has won!" << std::endl;
}

void Game::checkPlayers(std::vector<Player>& playerList) {
	int counter = 0;
	for (Player &player : playerList) {
		if (player.getMoney() < 0 && player.ownedProperty.size() == 0) {
			playerList.erase(playerList.begin() + counter);
			std::cout << player.getName() << " does not have any money or properties. They have lost." << std::endl;
		}
		else if (player.getMoney() < 0 && player.ownedProperty.size() > 0) {
			std::cout << "You are bankrupt! Mortage whatever property you need to get your balance above zero." << std::endl;
			while (player.getMoney() < 0 && player.ownedProperty.size() > 0) {
				std::string propToMortage;
				for (Property prop : player.ownedProperty) {
					if (prop.mortageStatus == false) {
						std::cout << prop.getName() << ":" << prop.getCost();
					}
				}
				std::cout << "\nType in a property to mortage:";
				std::cin >> propToMortage;
				int x = 0;
				for (Property prop : player.ownedProperty) {
					if (propToMortage == prop.getName()) {
						player.mortageProperty(prop);
						board[player.getPos()].mortageStatus = true;
						player.mortagedProperty.push_back(prop);
						player.ownedProperty.erase(player.ownedProperty.begin() + x);
					}x++;
				}
			}

		}
		counter++;
	}

}