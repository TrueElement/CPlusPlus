#include "Creature.h"
#include "Room.h"

Animal::Animal() {

}

Animal::~Animal() {

}

void Animal::speak(bool pos_neg) {
	if(this->getCurrentRoom()->hasPc()) {
		PC *pc = this->getCurrentRoom()->getObjectManager()->getPC();
		std::cout << "Animal " << this->getName();
		if(pos_neg == true) {
			std::cout << " licks face." << std::endl;
			pc->modRespect(1);
		} else {
			std::cout << " growls." << std::endl;
			pc->modRespect(-1);

		}
	}
}

/*
 * if state == 0 room is clean
 * if state == 1 room is half-dirty
 * if state == 2 room is dirty
 *
 * method returns true if room is good
 * method returns false if room is not good
 */
bool Animal::checkRoom() {
	if(this->getCurrentRoom()->getState() == 0) {
		return true;
	} else if(this->getCurrentRoom()->getState() == 1) {
		return true;
	} else if(this->getCurrentRoom()->getState() == 2) {
		return false;
	} else {
		return false;
	}
}

bool Animal::move(int direction) {
	std::cout << "Animal " << this->getName() << "moving." << std::endl;
	Room *currentRoom = this->getCurrentRoom();
	switch(direction) {
	case 0:
		return this->moveRoom(currentRoom->getNeighbor(0));
		break;
	case 1:
		return this->moveRoom(currentRoom->getNeighbor(1));
		break;
	case 2:
		return this->moveRoom(currentRoom->getNeighbor(2));
		break;
	case 3:
		return this->moveRoom(currentRoom->getNeighbor(3));
		break;
	default:
		return false;
	}
}
void Animal::processInitialState() {
	//std::cout << "Animal " << this->getName() << " processing initial state of ";
	//std::cout << this->getCurrentRoom()->getState() << std::endl;
	bool check = this->checkRoom();
	if(check == false) {
		//std::cout << "Animal " << this->getName() << " needs to move" << std::endl;
		bool remove = this->moveOnStateChange();
		this->getCurrentRoom()->checkRemoveFromGame(remove, this);
	} else {
		//std::cout << "Animal " << this->getName() << " doesn't need to move." << std::endl;
	}
}

void Animal::enteringRoom() {
	bool check = this->checkRoom();
	if(check == false) {
		this->commandClean();
	}
}
bool Animal::moveOnStateChange() {
	srand(time(NULL));
	int dir = rand() % 4;
	Room *currentRoom = this->getCurrentRoom();
	if(currentRoom->getNeighbor(dir) != NULL && currentRoom->getNeighbor(dir)->isFull() == false) {
		this->moveRoom(currentRoom->getNeighbor(dir));
		return true;
	} else if(currentRoom->getNeighbor(0)->isFull() == false) {
		this->moveRoom(currentRoom->getNeighbor(0));
		return true;
	} else if (currentRoom->getNeighbor(1)->isFull() == false) {
		this->moveRoom(currentRoom->getNeighbor(1));
		return true;
	} else if(currentRoom->getNeighbor(2)->isFull() == false) {
		this->moveRoom(currentRoom->getNeighbor(2));
		return true;
	} else if(currentRoom->getNeighbor(3)->isFull() == false) {
		this->moveRoom(currentRoom->getNeighbor(3));
		return true;
	} else {
		return false;
	}
}

bool Animal::processStateChange() {
	if(this->checkRoom() == false) {
		this->speak(false);
		bool move = this->moveOnStateChange();
		if(move == false) {
			return false;
		} else {
			return true;
		}
	} else {
		return true;
	}
}

bool Animal::processCommand(std::string *command) {
	if(command->compare("clean") == 0) {
		this->commandClean();
		return true;
	} else if(command->compare("dirty") == 0) {
		this->commandDirty();
		return true;
	} else {
		std::cout << "Animal " << this->getName() << " doesn't know how to do " << command << std::endl;
		return false;
	}
}

void Animal::print() {
	std::cout << "A animal named " << this->getName() << std::endl;
}

bool Animal::moveRoom(Room *room) {
	if(room != NULL) {
		std::cout << "Animal " << this->getName() << " moving rooms." << std::endl;
		Room *current = this->getCurrentRoom();
		current->removeCreatureByName(this->getName());
		this->setCurrentRoomName(room->getName());
		this->setCurrentRoom(room);
		room->addCreature(static_cast<Creature *>(this));
		this->enteringRoom();
		return true;
	} else {
		return false;
	}
}

void Animal::commandClean() {
	this->getCurrentRoom()->modState(0);
}

void Animal::commandDirty() {
	this->getCurrentRoom()->modState(1);
}




