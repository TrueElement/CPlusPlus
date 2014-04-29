#include "Game.h"
#include "Room.h"

ObjectManager::ObjectManager() : room_count(0), creature_count(0) {
	this->rooms = new std::vector<Room *>();
	this->animals = new std::vector<Animal *>();
	this->npcs = new std::vector<NPC *>();
	this->pc = NULL;
	this->game = NULL;
	this->cli = NULL;
	this->objc = NULL;
	this->input = NULL;
	this->strm = NULL;
}

ObjectManager::~ObjectManager() {
	delete rooms;
	delete animals;
	delete npcs;
	delete pc;
	delete cli;
	delete objc;
	delete input;
}

void ObjectManager::setGame(Game *game) {
	this->game = game;
}

Game * ObjectManager::getGame() {
	return this->game;
}

void ObjectManager::setCLI(CLI *cli) {
	this->cli = cli;
}

CLI * ObjectManager::getCLI() {
	return this->cli;
}

void ObjectManager::setObjectCreator(ObjectCreator *objc) {
	this->objc = objc;
}

ObjectCreator * ObjectManager::getObjectCreator() {
	return this->objc;
}

void ObjectManager::setInput(Input *inp) {
	this->input = inp;
}

void ObjectManager::setStringManip(StringManip *strm) {
	this->strm = strm;
}

StringManip * ObjectManager::getStringManip() {
	return this->strm;
}
void ObjectManager::setupRoomNeighborPointers() {
	//std::cout << "DEBUG - ObjectManager - Setting Up Room Neighbor Pointers " << std::endl;
	Room *current;
	Room *neighbor;
	int name;
	for(int i = 0; i < this->room_count; i++) {
		current = this->rooms->at(i);
		for(int j = 0; j < 4; j++) {
			name = current->getNeighborName(j);
			neighbor = this->getRoomByName(name);
			current->setNeighbor(j, neighbor);
		}
	}
}

void ObjectManager::setupCreatureRoomPointers() {
	//std::cout << "DEBUG - ObjectManager - Setting Up Creature Room Pointers" << std::endl;
	unsigned int i = 0;
	Creature *temp;
	Animal *ani;
	NPC *npc;
	Room *room;
	for(i = 0; i < this->animals->size(); i++) {
		ani = this->animals->at(i);
		if(ani->getCurrentRoom() == NULL) {
			//std::cout << "Attempting to Set Animal " << ani->getName() << " room " << ani->getCurrentRoomName() << std::endl;
			room = this->getRoomByName(ani->getCurrentRoomName());
			//this->checkRoomNull(room);
			//std::cout << "Room " << room->getName() << " state " << room->getState() << std::endl;
			//std::cout <<"End Animal Setup" << std::endl;
			ani->setCurrentRoom(room);
			temp = static_cast<Creature *>(ani);
			room->addCreature(temp);
		}
	}

	room = NULL;
	for(i = 0; i < this->npcs->size(); i++) {
		npc = this->npcs->at(i);
		if(npc->getCurrentRoom() == NULL) {
			//std::cout << "Attempting to Set NPC " << npc->getName() << " room " << npc->getCurrentRoomName() << std::endl;
			room = this->getRoomByName(npc->getCurrentRoomName());
			//this->checkRoomNull(room);
			//std::cout << "Room " << room->getName() << " state " << room->getState() << std::endl;
			//std::cout << "End NPC Setup" << std::endl;
			npc->setCurrentRoom(room);
			temp = static_cast<Creature *>(npc);
			room->addCreature(temp);
		}
	}
}

void ObjectManager::setupPcRoomPointers() {
	std::cout << "Setting PC Room Pointer" << std::endl;
	int name = this->pc->getCurrentRoomName();
	Room *room = this->getRoomByName(name);
	this->checkRoomNull(room);
	this->pc->setCurrentRoom(room);
	room->addCreature(static_cast<Creature *>(this->pc));
	std::cout << "End Setting PC Room Pointer" << std::endl;
}

Room * ObjectManager::getRoomByName(int name) {
	//std::cout << "DEBUG - ObjectManager - Attempting to Get Room By Name" << std::endl;
	Room *temp = NULL;
	for(int i = 0; i < this->room_count; i++) {
		temp = this->rooms->at(i);
		if(temp->getName() == name) {
			//std::cout << "DEBUG - ObjectManager - getRoomByName - Room Found " << temp->getName() << std::endl;
			break;
		} else {
			continue;
		}
	}
	return temp;
}

Creature * ObjectManager::getCreatureByName(int name) {
	//std::cout << "DEBUG - ObjectManager - Attempting to get Creature by Name" << std::endl;
	Creature *temp = NULL;
	bool found = false;
	unsigned int i = 0;
	for(i = 0; i < this->animals->size(); i++) {
		temp = dynamic_cast<Creature *>(animals->at(i));
		if(temp->getName() == name) {
			found = true;
			break;
		}
	}
	if(found == false) {
		for(i = 0; i < this->npcs->size(); i++) {
			temp = dynamic_cast<Creature *>(npcs->at(i));
			if(temp->getName() == name) {
				break;
			}
		}
	}
	return temp;
}

void ObjectManager::setPC(PC *pc) {
	this->pc = pc;
}

PC *  ObjectManager::getPC() {
	return this->pc;
}

void ObjectManager::addCreature(Creature *toAdd) {
	//std::cout << "DEBUG - ObjectManager - Adding Creature" << std::endl;
	if(toAdd->getType() == 0) {
		//std::cout << "DEBUG - ObjectManager - Adding PC" << std::endl;
		this->pc = static_cast<PC *>(toAdd);
	} else if(toAdd->getType() == 1) {
		//std::cout << "DEBUG - ObjectManager - Adding Animal " << std::endl;
		Animal *temp = static_cast<Animal *>(toAdd);
		this->animals->push_back(temp);
		this->creature_count++;
	} else if(toAdd->getType() == 2) {
		//std::cout << "DEBUG - ObjectManager - Adding NPC " << std::endl;
		NPC *temp = static_cast<NPC *>(toAdd);
		this->npcs->push_back(temp);
		this->creature_count++;
	} else {
		return;
	}
}

void ObjectManager::addRoom(Room *toAdd) {
	this->rooms->push_back(toAdd);
	this->room_count++;
}

bool ObjectManager::creatureExists(int name) {
	//std::cout << "DEBUG - ObjectManager - Creature Exists Called " << std::endl;
	NPC *npc;
	Animal *animal;
	unsigned int i = 0;
	for(i = 0; i < this->animals->size(); i++) {
		animal = this->animals->at(i);
		if(animal->getName() == name) {
			return true;
		}
	}

	for(i = 0; i < this->npcs->size(); i++) {
		npc = this->npcs->at(i);
		if(npc->getName() == name) {
			return true;
		}
	}
	return false;
}

void ObjectManager::roomStateChange(int name) {
	//std::cout << "DEBUG - ObjectManager - Room State Change - Attempting to Get Room." << std::endl;
	Room *temp = this->getRoomByName(name);
	if(temp != NULL) {
		//std::cout << "ObjectManager - Room Found. Calling State Change" << std::endl;
		temp->roomStateChange();
	}
}

bool ObjectManager::commandCreature(int name, std::string *command) {
	//std::cout << "DEBUG - ObjectManager - Start Command Creature" << std::endl;
	Creature *temp = NULL;
	Animal *animal = NULL;
	NPC *npc = NULL;
	bool toReturn = false;
	if(creatureExists(name)) {
		//std::cout << "DEBUG - ObjectManager - Creature found." << std::endl;
		temp = getCreatureByName(name);
		if(temp->getType() == 1) {
			//std::cout << "DEBUG - ObjectManager - Converting Creature to Animal" << std::endl;
			animal = this->convertCreatureToAnimal(temp);
		} else if(temp->getType() == 2) {
			//std::cout << "DEBUG - ObjectManager - Converting Creatrue to NPC" << std::endl;
			npc = this->convertCreatureToNPC(temp);
		}
	} else {
		//std::cout << "DEBUG - ObjectManager - Creature Not Found." << std::endl;
		return false;
	}

	if(animal != NULL) {
		//std::cout << "DEBUG - ObjectManager - Trying to Command Animal" << std::endl;
		toReturn = animal->processCommand(command);
	} else if(npc != NULL) {
		//std::cout << "DEBUG - ObjectManager - Trying to Command NPC" << std::endl;
		toReturn = npc->processCommand(command);
	} else {
		//std::cout << "DEBUG - ObjectManager - Creature Not Converted Correctly." << std::endl;
		return false;
	}
	//std::cout << "DEBUG - ObjectManager - Creature Commanded. Returning." << std::endl;
	return toReturn;
}

Animal * ObjectManager::convertCreatureToAnimal(Creature *toConvert) {
	return static_cast<Animal *>(toConvert);
}

NPC * ObjectManager::convertCreatureToNPC(Creature *toConvert) {
	return static_cast<NPC *>(toConvert);
}

void ObjectManager::removeCreatureFromGame(Creature *toRemove) {
	if(toRemove->getType() == 1) {
		this->removeAnimalFromGame(static_cast<Animal *>(toRemove));
	} else if(toRemove->getType() == 2) {
		this->removeNpcFromGame(static_cast<NPC *>(toRemove));
	}

}

void ObjectManager::removeAnimalFromGame(Animal *toRemove) {
	unsigned int i = 0;
	Animal *temp;
	for(i = 0; i < animals->size(); i++) {
		temp = animals->at(i);
		if(temp->getName() == toRemove->getName()) {
			animals->erase(animals->begin() + i);
			break;
		}
	}
	delete[] toRemove;
}

void ObjectManager::removeNpcFromGame(NPC *toRemove) {
	unsigned int i = 0;
	NPC *temp;
	for(i = 0; i < animals->size(); i++) {
		temp = npcs->at(i);
		if(temp->getName() == toRemove->getName()) {
			npcs->erase(npcs->begin() + i);
			break;
		}
	}
	delete[] toRemove;
}

void ObjectManager::processInitialRoomState() {
	std::cout << "Processing Initial Room State" << std::endl;
	unsigned int i = 0;
	Animal *ani;
	for(i = 0; i < animals->size(); i++) {
		ani = animals->at(i);
		ani->processInitialState();
	}
	NPC *npc;
	for(i = 0; i < npcs->size(); i++) {
		npc = npcs->at(i);
		npc->processInitialState();
	}
}

void ObjectManager::checkRoomNull(Room *room) {
	if(room == NULL) {
		std::cout << "Room Null" << std::endl;
	} else {
		std::cout << "Room Not Null" << std::endl;
	}
}

void ObjectManager::printAnimals() {
	unsigned int i = 0;
	Animal *ani;
	for(i = 0; i < this->animals->size(); i++) {
		ani = animals->at(i);
		std::cout << "Animal named " << ani->getName() << " with room name " << ani->getCurrentRoomName();
		std::cout << " and actual room " << ani->getCurrentRoom()->getName() << std::endl;
	}
}

void ObjectManager::printNpcs() {
	unsigned int i = 0;
	NPC *npc;
	for(i = 0; i < this->npcs->size(); i++) {
		npc = npcs->at(i);
		std::cout << "NPC named " << npc->getName() << " with room name " << npc->getCurrentRoomName();
		std::cout << " and actual room " << npc->getCurrentRoom()->getName() << std::endl;
	}
}
