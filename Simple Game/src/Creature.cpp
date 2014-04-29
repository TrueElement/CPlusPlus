#include "Creature.h"
#include "Room.h"

/**
 * Creature Super Class Function Definitions
 */
Creature::Creature() : type(0), currentRoomName(0), name(0), current_room(0) {

}

Creature::~Creature() {

}

int Creature::getType() {
	return this->type;
}

void Creature::setType(int creature_type) {
    this->type = creature_type;
}

Room * Creature::getCurrentRoom() {
    return this->current_room;
}

void Creature::setCurrentRoom(Room *new_room) {
	if(new_room != NULL) {
		this->current_room = new_room;
	}
}
int Creature::getCurrentRoomName() {
    return this->currentRoomName;
}

void Creature::setCurrentRoomName(int room_name) {
	this->currentRoomName = room_name;
}

void Creature::setName(int creature_name) {
	this->name = creature_name;
}

int Creature::getName() {
	return this->name;
}

void Creature::speak(bool pos_neg) {
	std::cout << "Creature of Type ";
	std::cout << this->getType() <<" named ";
	std::cout << this->getName() << " performed a ";
	if (pos_neg == true) {
		std::cout << "positive action." << std::endl;
	} else {
		std::cout << "negative action." << std::endl;
	}

}

void Creature::performAction(bool type) {
    if(type == false) {

    } if(type == true) {

    }
}

bool Creature::move(int direction) {
    if(direction == 0) {
    	return this->moveRoom(this->current_room->getNeighbor(0));
    } else if(direction == 1) {
    	return this->moveRoom(this->current_room->getNeighbor(1));
    } else if(direction == 2) {
    	return this->moveRoom(this->current_room->getNeighbor(2));
    } else if(direction == 3) {
    	return this->moveRoom(this->current_room->getNeighbor(3));
    } else {
    	return false;
    }
}

bool Creature::moveRoom(Room *toMove) {
	if(toMove->isFull()) {
		return false;
	} else {
		this->current_room->removeCreature(this);
		this->currentRoomName = toMove->getName();
		this->current_room = toMove;
		toMove->addCreature(this);
		return true;
	}
}

void Creature::look() {

}

bool Creature::processStateChange() {
	std::cout << "Creature Process State Change" << std::endl;
	return false;
}

/*
 * If type == 0 creature is pc
 * If type == 1 creature is animal
 * If type == 2 creature is npc
 */
void Creature::print() {}

bool Creature::moveOnStateChange() {
	return false;
}
