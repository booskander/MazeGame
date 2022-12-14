#include "Map.hpp"
#include "Rooms.hpp"

int main() {
	Rooms rooms;
	Player player{ rooms.Entrance, rooms };
	Map maze{rooms, player };

	maze.startGame();


	
	return 0;
}