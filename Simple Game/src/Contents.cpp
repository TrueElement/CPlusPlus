#include "Room.h"

Contents::Contents(void) : has_pc(false) {
	this->ani = new std::vector<Animal *>();
	this->npc = new std::vector<NPC *>();
	this->pc = NULL;
}

Contents::~Contents() {

}
bool Contents::add(Animal *toAdd) {
	if(this->isFull()) {
		return false;
	} else {
		ani->push_back(toAdd);
		return true;
	}
}

bool Contents::add(NPC *toAdd) {
	if(this->isFull()) {
		return false;
	} else {
		npc->push_back(toAdd);
		return true;
	}
}

bool Contents::add(PC *pc) {
	if(this->isFull()) {
		return false;
	} else {
		this->pc = pc;
		this->has_pc = true;
		return true;
	}

}

void Contents::remove(int name) {
	unsigned int i = 0;
	bool found = false;
	for(i = 0; i < ani->size(); i++) {
		if(ani->at(i)->getName() == name) {
			std::cout << "Animal Removed" << std::endl;
			ani->erase(ani->begin() + i);
			found = true;
			break;
		}
	}

	if(found == false) {
		for(i = 0; i < npc->size(); i++) {
			if(npc->at(i)->getName() == name) {
				std::cout << "NPC Removed" << std::endl;
				npc->erase(npc->begin() + i);
				break;
			}
		}
	}
}

Creature * Contents::get(int name) {
	unsigned int i = 0;
	for(i = 0; i < ani->size(); i++) {
		if(ani->at(i)->getName() == name) {
			return dynamic_cast<Creature *>(ani->at(i));
		}
	}

	for(i = 0; i < (npc->size()); i++) {
		if(npc->at(i)->getName() == name) {
			return dynamic_cast<Creature *>(npc->at(i));
		}
	}
	return NULL;
}

void Contents::setupVectors() {
	this->ani = new std::vector<Animal *>();
	this->npc = new std::vector<NPC *>();
}

int Contents::getTotal() {
	int total = 0;
	total = total + ani->size();
	total = total + npc->size();
	return total;
}

bool Contents::isFull() {
	if(this->getTotal() == MAX_SIZE) {
		return true;
	} else {
		return false;
	}
}

Creature * Contents::getCreatureByIndex(int index) {
	unsigned int uindex = index;
	if(index > getTotal()) {
		return NULL;
	} else {
		if(uindex < ani->size()) {
			return static_cast<Creature *>(ani->at(index));
		} else if(uindex < npc->size()) {
			unsigned int npcindex = index - ani->size();
			if(npcindex < npc->size()) {
				return static_cast<Creature *>(npc->at(npcindex));
			} else {
				return NULL;
			}
		}
		return NULL;
	}
}

PC * Contents::getPC() {
	return this->pc;
}

void Contents::removePC() {
	this->has_pc = false;
	this->pc = NULL;
}

bool Contents::hasPC() {
	return this->has_pc;
}
