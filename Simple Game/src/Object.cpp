#include "../include/Object.hpp"

Room * ObjectCreator::createRoom(int *token_array) {
	Room *temp = new Room();
	temp->setName(created_rooms);
	temp->setState(token_array[0]);
	temp->setNeighborName(0, token_array[1]);
	temp->setNeighborName(1, token_array[2]);
	temp->setNeighborName(2, token_array[3]);
	temp->setNeighborName(3, token_array[4]);
	created_rooms++;
	return temp;
}
/**
 * Take input out of token array and call
 * create creature
 */
Creature * ObjectCreator::createCreature(int *token_array) {
	return createCreature(token_array[0], token_array[1]);
}

/*
 * Create a new creature and add it to the
 * array.
 */
Creature * ObjectCreator::createCreature(int type, int starting_room) {
	Creature *temp = new Creature();
	temp->setType(type);
	temp->setCurrentRoomName(starting_room);
	temp->setName(created_creatures);
	created_creatures++;
	return temp;
}

Animal * ObjectCreator::createAnimal(int name, int starting_room) {
	return 0;
}

NPC * ObjectCreator::createNPC(int name, int starting_room) {
	return 0;
}

PC * ObjectCreator::createPC(int starting_room) {
	return 0;
}

/*
 *
 *
 * Start ObjectManager Function Declarations
 *
 *
 */

/* Set the room array instance value to an array of the
* size of expected rooms.
*/
void ObjectManager::setupRoomArray() {
	if(this->room_count != 0) {
		this->rooms = new Room * [room_count];
	}
}
/*
* Set the creature array instance value to an array
* of the size of expected creatures.
*/
void ObjectManager::setupCreatureArray() {
	if(this->creature_count != 0) {
		this->creatures = new Creature * [creature_count];
	}
}

void ObjectManager::setupRoomNeighborPointers() {
	Room *temp;
	for(int i = 0; i < this->room_count; i++) {
		temp = rooms[i];
		for(int j = 0; j < 4; j++) {
			switch (j) {
			case 0:
					temp->setNeighbor(0, getRoomByName(temp->getNeighborName(0)));
				break;
			case 1:
					temp->setNeighbor(1, getRoomByName(temp->getNeighborName(1)));
				break;
			case 2:
					temp->setNeighbor(2, getRoomByName(temp->getNeighborName(2)));
				break;
			case 3:
					temp->setNeighbor(3, getRoomByName(temp->getNeighborName(3)));
				break;
			}
		}
	}
}

void ObjectManager::setupCreatureRoomPointers() {
	Creature *temp;
	for(int i = 0; i < this->creature_count; i++) {
		temp = this->creatures[i];
		temp->setCurrentRoom(this->getRoomByName(temp->getCurrentRoomName()));
	}
}

Room * ObjectManager::getRoomByName(int name) {
	Room *temp  = NULL;
	for(int i = 0; i < this->room_count; i++) {
		temp = this->rooms[i];
		if(temp->getName() == name) {
			break;
		} else {
			continue;
		}
	}
	return temp;
}

Creature * ObjectManager::getCreatureByName(int name) {
	Creature *temp = NULL;
	for(int i = 0; i < this->creature_count; i++) {
		temp = this->creatures[i];
		if(temp->getName() == name) {
			break;
		} else {
			continue;
		}
	}
	return temp;
}




