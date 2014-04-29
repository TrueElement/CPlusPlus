#include "Creature.h"
#include "Room.h"

PC::PC() : respect(40) {

}

PC::~PC() {

}
void PC::decrementRespect() {
	this->respect--;
}

void PC::setRespect(int new_respect) {
    this->respect = new_respect;
}

int PC::getRespect() {
    return this->respect;
}

void PC::modRespect(int modify) {
	this->respect = this->respect + modify;
}

bool PC::move(int direction) {
	switch (direction) {
	case 0:
		return moveNorth();
		break;
	case 1:
		return moveSouth();
		break;
	case 2:
		return moveEast();
		break;
	case 3:
		return moveWest();
		break;
	default:
		return false;
	}
}


bool PC::moveNorth() {
	Room *temp = this->getCurrentRoom();
	Room *north = temp->getNeighbor(0);
	if(north == NULL) {
		std::cout << "There is no room to the north!" << std::endl;
		return false;
	} else {
		if(north->isFull()) {
			std::cout << "The room to the north is full!" << std::endl;
			return false;
		} else {
			north->addCreature(static_cast<Creature *>(this));
			temp->removeCreature(static_cast<Creature *>(this));
			this->setCurrentRoom(north);
			this->setCurrentRoomName(north->getName());
			std::cout << "Move to the north successful!" << std::endl;
			return true;
		}
	}
}

bool PC::moveSouth() {
	Room *temp = this->getCurrentRoom();
	Room *south = temp->getNeighbor(1);
	if(south == NULL) {
		std::cout << "There is no room to the north!" << std::endl;
		return false;
	} else {
		if(south->isFull()) {
			std::cout << "The room to the north is full!" << std::endl;
			return false;
		} else {
			south->addCreature(static_cast<Creature *>(this));
			temp->removeCreature(static_cast<Creature *>(this));
			this->setCurrentRoom(south);
			this->setCurrentRoomName(south->getName());
			std::cout << "Move to the south successful!" << std::endl;
			return true;
		}
	}
}

bool PC::moveEast() {
	Room *temp = this->getCurrentRoom();
	Room *east = temp->getNeighbor(2);
	if(east == NULL) {
		std::cout << "There is no room to the north!" << std::endl;
		return false;
	} else {
		if(east->isFull()) {
			std::cout << "The room to the north is full!" << std::endl;
			return false;
		} else {
			east->addCreature(static_cast<Creature *>(this));
			temp->removeCreature(static_cast<Creature *>(this));
			this->setCurrentRoom(east);
			this->setCurrentRoomName(east->getName());
			std::cout << "Move to the east successful!" << std::endl;
			return true;
		}
	}
}

bool PC::moveWest() {
	Room *temp = this->getCurrentRoom();
	Room *west = temp->getNeighbor(3);
	if(west == NULL) {
		std::cout << "There is no room to the north!" << std::endl;
		return false;
	} else {
		if(west->isFull()) {
			std::cout << "The room to the north is full!" << std::endl;
			return false;
		} else {
			west->addCreature(static_cast<Creature *>(this));
			temp->removeCreature(static_cast<Creature *>(this));
			this->setCurrentRoom(west);
			this->setCurrentRoomName(west->getName());
			std::cout << "Move to the west successful!" << std::endl;
			return true;
		}
	}
}

void PC::look() {
	Room *room = this->getCurrentRoom();
	if(room != NULL) {
		this->getCurrentRoom()->print();
	} else {
		std::cout << "Error. PC Room is NULL" << std::endl;
	}

}

void PC::look(std::string *direction) {
	Room *toLook = NULL;
	if(direction->compare("north") == 0) {
		toLook = this->getCurrentRoom()->getNeighbor(0);
	} else if(direction->compare("south") == 0) {
		toLook = this->getCurrentRoom()->getNeighbor(1);
	} else if(direction->compare("east") == 0) {
		toLook = this->getCurrentRoom()->getNeighbor(2);
	} else if(direction->compare("west") == 0) {
		toLook = this->getCurrentRoom()->getNeighbor(3);
	} else {
		std::cout << direction << " is not a valid direction!" << std::endl;
	}
	if(toLook != NULL) {
		toLook->print();
	} else {
		std::cout << "There is no room to the " << *direction << "!" << std::endl;
	}
}

bool PC::commandClean() {
	Room *current_room = this->getCurrentRoom();
	if(current_room->getState() == 0) {
		std::cout << "The room is already clean!" << std::endl;
		return false;
	} else if(current_room->getState() == 1) {
		std::cout << "The room is now clean!" << std::endl;
		current_room->setState(0);
		current_room->roomStateChange();
		return true;
	} else if(current_room->getState() == 2) {
		std::cout << "The room is now half-dirty!" << std::endl;
		current_room->setState(1);
		current_room->roomStateChange();
		return true;
	} else {
		return false;
	}
}

bool PC::commandDirty() {
	Room *current_room = this->getCurrentRoom();
	if(current_room->getState() == 0) {
		std::cout << "The room is now half-dirty!" << std::endl;
		current_room->setState(1);
		current_room->roomStateChange();
		return true;
	} else if(current_room->getState() == 1) {
		std::cout << "The room is now dirty!" << std::endl;
		current_room->setState(2);
		current_room->roomStateChange();
		return true;
	} else if(current_room->getState() == 2) {
		std::cout << "The room is already dirty!" << std::endl;
		return false;
	} else {
		return false;
	}
}
