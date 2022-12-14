#pragma once

#include "Player.hpp"
#include "Objects.hpp"
#include "Rooms.hpp"
/**
* Represente la Vue du Jeu
* 
*/
class Map {
private:
	Player player_;
	string title_;
	Objects objects_;
	vector<Room> rooms_;
public:
	Map(Rooms rooms, Player player) : player_(player) {
		title_ = "THE ULTIMATE MAZE GAME";
	}


	void startMessage() {
		cout << "<<<<<<<<<<<< Welcome to the " << title_ << ">>>>>>>>>>>>>>" << endl;
		
	}

	void displayCommands() {
		cout << "Use N, S, O or W keys to navigate" << endl
			<< "You can interact with objects via use, look and take commands" << endl
			<< "You can interact with objects by typing: use,'\n' look or take followed by a feature of the object" << endl
			<< "To end the game at anytime, type END " << endl;
		
	}

	void endMessage() {
		cout << "Thank you for playing...see you soon!" << endl;
	}

	void startGame() {
		system("Color 0A");
		startMessage();
		system("Color 01");
		displayCommands();
		system("Color 02");
		player_.getCurrentRoom()->display();
		system("Color 04");
		while (player_.getInput() != "END") {
			if (player_.getInput() == "END")
				break;
			player_.play();
		}
		system("Color 0A");
		endMessage();
	}
};