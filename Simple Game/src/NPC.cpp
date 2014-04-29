#include "Creature.h"
#include "Room.h"

NPC::NPC() {

}

NPC::~NPC() {

}

void NPC::speak(bool pos_neg) {
	if(this->getCurrentRoom()->hasPc()) {
		PC *pc = this->getCurrentRoom()->getObjectManager()->getPC();
		std::cout << "Human " << this->getName();
		if(pos_neg == true) {
			std::cout << " smiles." << std::endl;
			pc->modRespect(1);
		} else {
			std::cout << " grumbles." << std::endl;
			pc->modRespect(-1);

		}
	}
}

void NPC::processInitialState() {
	//std::cout << "NPC " << this->getName() << " processing initial state of ";
	//std::cout << this->getCurrentRoom()->getState() << std::endl;
    bool check = this->checkRoom();
    if(check == false) {
    	//std::cout << "NPC " << this->getName() << " needs to move." << std::endl;
        bool remove = this->moveOnStateChange();
        this->getCurrentRoom()->checkRemoveFromGame(remove,this);
    } else {
    	//std::cout << "NPC " << this->getName() << " doesn't need to move." << std::endl;
    }
}

bool NPC::checkRoom() {
	if(this->getCurrentRoom()->getState() == 0) {
		return false;
	} else if(this->getCurrentRoom()->getState() == 1) {
		return true;
	} else if(this->getCurrentRoom()->getState() == 2) {
		return true;
	} else {
		return false;
	}
}

bool NPC::move(int direction) {
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

bool NPC::moveOnStateChange() {
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

bool NPC::moveRoom(Room *room) {
	if(room != NULL) {
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

bool NPC::processStateChange() {
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

void NPC::enteringRoom() {
    bool check = this->checkRoom();
    if(check == false) {
        this->commandDirty();
    }
}

bool NPC::processCommand(std::string *command) {
	if(command->compare("clean") == 0) {
		this->commandClean();
		return true;
	} else if(command->compare("dirty") == 0) {
		this->commandDirty();
		return true;
	} else {
		std::cout << "NPC " << this->getName() << " doesn't know how to do " << command << std::endl;
		return false;
	}
}

void NPC::print() {
	std::cout << "A human named " << this->getName() << std::endl;
}

void NPC::commandClean() {
    this->getCurrentRoom()->modState(0);
}

void NPC::commandDirty() {
    this->getCurrentRoom()->modState(1);
}

