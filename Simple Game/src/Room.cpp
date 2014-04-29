#include "Room.h"

Room::Room() {
	this->name = -1;
	this->state = -1;
	this->num_creatures = 0;
	this->contains = new Contents();
	this->neighbors = new Neighbors();
	this->objm = NULL;
}

Room::~Room() {
	delete[] neighbors;
	delete[] contains;
}

void Room::setObjectManager(ObjectManager *objm) {
this->objm = objm;
}

ObjectManager * Room::getObjectManager() {
	return this->objm;
}
/*
 * Get the name of this room.
 * Names are just an int value.
 */
void Room::setName(int room_name) {
    this->name = room_name;
}

/**
 * Return the name of this room.
 * Names are just an int value.
 */
int Room::getName() {
    return this->name;
}

/*
 * Return has_pc boolean
 */
bool Room::hasPc() {
    return this->contains->hasPC();
}

int Room::getState() {
    return state;
}

/*
 * If state = 0 room is clean
 * If state = 1 room is half-dirty
 * If state = 2 room is dirty
 */
void Room::setState(int new_state) {
    this->state = new_state;
}

/*
 * If action = 1 - dirty action performed
 * If action = 0 - clean action performed
 * returns true if state was changed
 * returns false if state was not changed
 */
bool Room::modState(int action) {
    if(action == 0) {
        if(state == 0) {
            return false;
        } else if(state == 1) {
            setState(0);
            roomStateChange();
            return true;
        } else if (state == 2) {
            setState(1);
            roomStateChange();
            return true;
        }
    } else if(action == 1) {
        if(state == 0) {
            setState(1);
            roomStateChange();
            return true;
        } else if(state == 1) {
            setState(2);
            roomStateChange();
            return true;
        } else if(state == 2) {
            return false;
        }
    }
    return false;
}
/*
 * If direction == 0 - set north neighbor
 * If direction == 1 - set south neighbor
 * If direction == 2 - set east neighbor
 * If direction == 3 - set west neighbor
 */
void Room::setNeighbor(int direction, Room *neighbor) {
    if(direction == 0) {
        this->neighbors->setNorth(neighbor);
    } else if (direction == 1) {
        this->neighbors->setSouth(neighbor);
    } else if (direction == 2) {
        this->neighbors->setEast(neighbor);
    } else if (direction == 3) {
        this->neighbors->setWest(neighbor);
    }
}

/*
 * If direction == 0 - set north neighbor name
 * If direction == 1 - set south neighbor name
 * If direction == 2 - set east neighbor name
 * If direction == 3 - set west neighbor name
 */
void Room::setNeighborName(int direction, int neighbor_name) {
    if(direction == 0) {
        this->neighbors->setNorthName(neighbor_name);
    } else if(direction == 1) {
        this->neighbors->setSouthName(neighbor_name);
    } else if(direction == 2) {
        this->neighbors->setEastName(neighbor_name);
    } else if(direction == 3) {
        this->neighbors->setWestName(neighbor_name);
    } else {
        return;
    }
}

int Room::getNeighborName(int direction) {
	if(direction == 0) {
		return this->neighbors->getNorthName();
	} else if(direction == 1) {
		return this->neighbors->getSouthName();
	} else if(direction == 2) {
		return this->neighbors->getEastName();
	} else if(direction == 3) {
		return this->neighbors->getWestName();
	} else {
		return -1;
	}
}

bool Room::addCreature(Creature *toAdd) {
	std::cout << "Room " << this->name << " adding creature ";
	std::cout << toAdd->getName()  << " of type " << toAdd->getType() << std::endl;
	switch (toAdd->getType()) {
	case 0:
		std::cout << "Room " << this->name << " adding pc" << std::endl;
		PC *pc;
			pc = static_cast<PC *>(toAdd);
		return contains->add(pc);
		break;
	case 1:
		std::cout << "Room " << this->name << " adding animal" << std::endl;
		Animal *animal;
			animal = static_cast<Animal *>(toAdd);
		return contains->add(animal);
		break;
	case 2:
		std::cout << "Room " << this->name << " adding npc" << std::endl;
		NPC *npc;
			npc = static_cast<NPC *>(toAdd);
		return contains->add(npc);
	default:
		return false;
	}
}

bool Room::isFull() {
	if(contains->isFull()) {
		return true;
	} else {
		return false;
	}
}

void Room::removeCreatureByName(int name) {
	this->removeCreature(this->getCreatureByName(name));
}

void Room::removeCreature(Creature * toRemove) {
	std::cout << "Removing Creature " << toRemove->getName() << " type " << toRemove->getType();
	std::cout << " from room " << this->name << std::endl;
	if(toRemove->getType() == 0) {
		this->contains->removePC();
	} else if(toRemove->getType() == 1) {
		this->contains->remove(toRemove->getName());
	} else if(toRemove->getType() == 2) {
		this->contains->remove(toRemove->getName());
	}
	std::cout << "End Room Remove" << std::endl;

}

Creature * Room::getCreatureByName(int name) {
	return this->contains->get(name);
}

void Room::setupNeighbors(void) {
	this->neighbors = new Neighbors();
}

Room * Room::getNeighbor(int direction) {
	switch (direction) {
	case 0:
		return this->neighbors->getNorth();
		break;
	case 1:
		return this->neighbors->getSouth();
		break;
	case 2:
		return this->neighbors->getEast();
		break;
	case 3:
		return this->neighbors->getWest();
		break;
	default:
		return NULL;
	}
}

Contents * Room::getContents() {
	return this->contains;
}

void Room::roomStateChange() {
	Creature *temp;
	bool remove_animal = false;
	for(int i = 0; i < contains->getTotal(); i++) {
		temp = contains->getCreatureByIndex(i);
		if(temp != NULL && temp->getType() == 1) {
			Animal *ani = static_cast<Animal *>(temp);
			remove_animal = ani->processStateChange();
		} else if(temp != NULL && temp->getType() == 2) {
			NPC *npc = static_cast<NPC *>(temp);
			remove_animal = npc->processStateChange();
		}
	}
}

void Room::checkRemoveFromGame(bool remove_animal, Creature *toRemove) {
	if(remove_animal == false) {
		this->allSpeak(false);
		this->removeCreature(toRemove);
		this->objm->removeCreatureFromGame(toRemove);
	} else {
		return;
	}
}

void Room::allSpeak(bool pos_neg) {
	Creature *temp;
	Animal *ani;
	NPC *npc;
	for(int i = 0; i < this->contains->getTotal(); i++) {
		temp = this->contains->getCreatureByIndex(i);
		if(temp->getType() == 1) {
			ani = static_cast<Animal *>(temp);
			ani->speak(pos_neg);
		} else if(temp->getType() == 2) {
			npc = static_cast<NPC *>(temp);
			ani->speak(pos_neg);
		}
	}
}

/*
 * if state == 0 room is clean
 * if state == 1 room is half-dirty
 * if state == 2 room is dirty
 */
void Room::print() {
	std::cout << "Room " << this->getName() << " containing " << contains->getTotal() << " creatures." << std::endl;
	this->printState();
	if(this->hasPc()) {
		std::cout << "You are in this room." << std::endl;
	}
	std::cout << "Creatures in this Room: " << std::endl;
	for(int i = 0; i < this->contains->getTotal(); i++) {
		Creature *temp = contains->getCreatureByIndex(i);
		if(temp == NULL) {
			break;
		}
		if(temp->getType() == 1) {
			Animal *ani = static_cast<Animal *>(temp);
			ani->print();
		} else if(temp->getType() == 2) {
			NPC *npc = static_cast<NPC *>(temp);
			npc->print();
		}
	}
}

void Room::printState() {
	if(this->state == 0) {
		std::cout << "This room is clean." << std::endl;
	} else if(this->state == 1) {
		std::cout << "This room is half-dirty." << std::endl;
	} else if(this->state == 2) {
		std::cout << "This room is dirty." << std::endl;
	}
}







