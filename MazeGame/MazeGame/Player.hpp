#pragma once
#include "Location.hpp"
#include <vector>
#include "Object.hpp"
#include "Rooms.hpp"
#include <sstream>
#include <iterator>
/*
* Represente le controlleur et toute la logique du jeu
*/
typedef shared_ptr<Location> Room;
typedef shared_ptr<Object> InterObject;
typedef vector<Room> WorldMap;

class Player {
private:
	WorldMap knownRooms_;
	Rooms allRooms_;
	Room currentRoom_;
	ObjectList bag_;
	string input_;
	vector<string> basicCommands_;
	Room updateLocation(string key) {
		if (currentRoom_->getNeighbor(key) != nullptr)
			currentRoom_ = currentRoom_->getNeighbor(key);
		return currentRoom_;
	}
public:
	void defineInput(const string& text) {
		input_ = text;
	}
	void setLocation(Room& room) {
		currentRoom_ = room;
	}
	Player(Room room, Rooms rooms) : currentRoom_(room), allRooms_(rooms) {
		basicCommands_.push_back("S");
		basicCommands_.push_back("N");
		basicCommands_.push_back("W");
		basicCommands_.push_back("E");
		basicCommands_.push_back("n");
		basicCommands_.push_back("s");
		basicCommands_.push_back("w");
		basicCommands_.push_back("e");

		knownRooms_.push_back(allRooms_.Kitchen);
		knownRooms_.push_back(allRooms_.MainHall);
		knownRooms_.push_back(allRooms_.SmallBedroom);
		knownRooms_.push_back(allRooms_.LivingRoom);
	}
	void display() {
		currentRoom_->display();
		if (!bag_.empty()) 
			displayObjects();
	}

	vector<string> splitString(string a) {

		stringstream ss(a);
		istream_iterator<std::string> begin(ss);
		istream_iterator<std::string> end;
		vector<std::string> tokens(begin, end);
		return tokens;
	}

	Room getCurrentRoom() {
		return this->currentRoom_;
	}
	void setInput() {
		cout << "> ";
		getline(cin, input_);
		if (input_.size() > 1 && input_ != "END") {
			std::transform(input_.begin(), input_.end(), input_.begin(),
				[](unsigned char c) { return std::tolower(c); });
		}
	}
	const string& getInput() {
		return input_;
	}

	void navigate(const char& direction) {
		Room temp = currentRoom_;
		switch (direction)
		{
		case 'S':
				updateLocation("South");
			break;

		case 'N':
				 updateLocation("North");
			break;
		case 'E':
				updateLocation("East");
			break;
		case 'W':
				updateLocation("West");
			break;
		default:
			cout << "Cannot go there" << endl;
			break;
		}
		if (temp == currentRoom_)
			cout << "Cannot go there" << endl;
		display();
	}


	void displayObjects() {
		cout << "You have: " << endl;
		for (auto&& obj : bag_)
			cout << '-' << obj->getName() << endl ;
	}

	bool isValidInput(const string& input) {
		for (auto&& str : basicCommands_)
			if (str == input)
				return true;
		return false;
	}


	InterObject getObject(ObjectList objs, string substr) {
		if (substr.size() < 3)
			return nullptr;
		for (auto&& obj : objs) {
			vector<string> temp;
			temp.push_back(obj->getName());
			vector<string> temp2 = splitString(obj->getDescription());
			for (auto&& el : temp2)
				if (el.size() > 2)
					temp.push_back(el);
			for (auto&& i : splitString(substr))
				for (auto&& j : temp)
					if (i == j)
						return obj;
			// la complexite est horrible je sais, mais le vector bag_ ne depasse ps une taille de 2
		}
		return nullptr;
	}

	InterObject getBagObject() {
		return getObject(bag_, input_);
	}

	InterObject getRoomObject() {
		return getObject(currentRoom_->getObjects(), input_);
	}
	void takeObject() {
		auto obj = getRoomObject();
		if (obj == nullptr) {
			cout << "Pardon take what?" << endl;
		}
		if (obj == nullptr)
			return;
		if (obj->canBeTaken())
			bag_.push_back(obj);
		obj->take();
		if (!bag_.empty())
			displayObjects();
	}

	void addConnection(const string& direction, Room& source, Room& destination) {
		source->addNeighbor(make_pair(direction, destination));
	}

	void useObject() {
		auto obj = getRoomObject();
		if (currentRoom_->getName() != "Main Hall") {
			if (!bag_.empty() && getBagObject() != nullptr) {
				cout << "You should probably use it somewhere else ;)..." << endl;
				return;
			}
		}
		if (obj == nullptr) {
			cout << "Pardon use what?" << endl;
			return;
		}
		if (obj->getName() == "green key") {
			if (currentRoom_->getName() == "Main Hall") {
				if (!bag_.empty())
					obj = getBagObject();
				if (!obj->isUsed() && obj->isTaken()) {
					obj->use();
					knownRooms_.push_back(allRooms_.RRoom);
					addConnection("East", currentRoom_, allRooms_.RRoom);
					addConnection("West", allRooms_.RRoom, currentRoom_);
					display();
					return;
				}
				else if (!obj->isTaken()) {
					cout << "You should probably take it first..." << endl;
					return;
				}
				else {
					cout << "R room is alerady unlocked!" << endl;
					return;
				}
			}
			if (obj->isTaken()) {
				cout << "There is nowhere in this room where you can use this" << endl;
				return;
			}
		}
		if (obj->getName() == "ladder") {
			if (currentRoom_->getName() == "Small Bedroom") {
				obj->setAction("You go up the ladder");
				obj->setDescription("A ladder going down");
				obj->use();
				setLocation(allRooms_.Grenier);
				display();
				return;
			}
			if (currentRoom_->getName() == "Attic") {
				obj->setAction("You go down the ladder");
				obj->setDescription("A ladder going up to a trap");
				obj->use();
				setLocation(allRooms_.SmallBedroom);
				display();
				return;
			}
		}
		obj->use();
	}


	bool containSpace(const string& a) {
		for (auto&& el : a)
			if (el == ' ')
				return true;
		return false;
	}

	bool isValid() {
		for (auto&& el : basicCommands_) {
			if (input_ == el)
				return true;
		}
		return false;
	}


	void lookObject() {
		InterObject  obj = getRoomObject();
		if (obj == nullptr) {
			cout << "Pardon look what?" << endl;
		}
		if (obj != nullptr)
			getRoomObject()->look();
	}

	void play() {
		setInput();
		if (input_ == "END") {
			return;
		}

		if (isValid() && input_.size() == 1) {
			navigate(toupper(input_[0]));
			return;
		}
		if (input_ == "use") {
			if (currentRoom_->getObjects().size() > 0 || !bag_.empty())
				cout << " what do you want to use ? " << endl;
			else
				cout << "There is nothing to use here" << endl;
			return;
		}
		if (input_ == "look") {
			display();
			return;
		}
		if (input_ == "take") {
			if (currentRoom_->getObjects().size() > 0)
				cout << "what do you want to take?" << endl;
			else
				cout << "There is nothing to take here" << endl;
			return;
		}

		if (containSpace(getInput())) {
			if (splitString(input_)[0] == "look")
			{
				lookObject();
				return;
			}
			if (splitString(input_)[0] == "use")
			{
				if (splitString(input_).size() > 1)
					useObject();
				return;
			}
			if (splitString(input_)[0] == "take")
			{
				takeObject();
				return;
			}
		}
		cout << "I do not know that" << endl;
	}
};