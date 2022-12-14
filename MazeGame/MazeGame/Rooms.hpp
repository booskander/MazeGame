#pragma once
#include "Location.hpp"
#include "Objects.hpp"
typedef shared_ptr<Location> Room;
/*
Represente le modele des donnes
*/
struct Rooms {
	/*
Initialisation des variables
*/
	Room Kitchen = make_shared<Location>("Kitchen", "This is a Kitchen. The floor is made out of grey wood.");
	Room Entrance = make_shared<Location>("Entrance", "This is the entrance of the house. There is a shoe rack on the side of the door.");
	Room MainHall = make_shared<Location>("Main Hall", "This is the Main Hallway. There is a big red carpet covering the floor.");
	Room LivingRoom = make_shared<Location>("Living Room", "This is the Living Room. There is a 60 inch TV on the wall.");
	Room SmallBedroom = make_shared<Location>("Small Bedroom", "This is the Bedroom. It isn't particulary big but it does the job.");
	Room Grenier = make_shared<Location>("Attic", "This is an Attic. It is used as a storage room.");
	Room RRoom = make_shared<Location>("R room", "This is a strange room, all the walls are covered with dry blood");
	Objects objectList;
	/*
	Construction du graphe des relations
	*/
	void setGraph() {
		Kitchen->addNeighbor(make_pair("South", MainHall));
		MainHall->addNeighbor(make_pair("West", SmallBedroom));
		MainHall->addNeighbor(make_pair("South", Entrance));
		MainHall->addNeighbor(make_pair("North", Kitchen));
		SmallBedroom->addNeighbor(make_pair("East", MainHall));
		Entrance->addNeighbor(make_pair("East", LivingRoom));
		Entrance->addNeighbor(make_pair("North", MainHall));
		LivingRoom->addNeighbor(make_pair("West", Entrance));
		SmallBedroom->addObject(objectList.ladder_);
		MainHall->addObject(objectList.piano_);
		MainHall->addObject(objectList.greenKey_);
		Grenier->addObject(objectList.ladder_);
	}


	Rooms() {
		setGraph();
	}
};