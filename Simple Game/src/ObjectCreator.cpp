#include "../include/Object.hpp"

ObjectCreator::ObjectCreator() {
	this->store = NULL;
	this->pc_created = false;
	this->created_rooms = 0;
	this->created_creatures = 0;
}

ObjectCreator::~ObjectCreator() {

}

void ObjectCreator::setObjectManager(ObjectManager *obj_man) {
	this->store = obj_man;
}

ObjectManager * ObjectCreator::getObjectManager() {
	return this->store;
}

/*
 * Create a new room based on read input.
 */
Room * ObjectCreator::createRoom(std::vector<int> *token_array) {
	Room *temp = new Room();
	temp->setName(created_rooms);
	temp->setState(token_array->at(0));
	temp->setNeighborName(0, token_array->at(1));
	temp->setNeighborName(1, token_array->at(2));
	temp->setNeighborName(2, token_array->at(3));
	temp->setNeighborName(3, token_array->at(4));
	temp->setObjectManager(this->store);
	std::cout  << "Room Created " << temp->getName() << std::endl;
	created_rooms++;
	return temp;
}
/**
 * Take input out of token array and call
 * create creature
 */
Creature * ObjectCreator::createCreature(std::vector<int> *token_array) {
	return createCreature(token_array->at(0), token_array->at(1));
}

/*
 * Create a new creature and add it to the
 * array.
 */
Creature * ObjectCreator::createCreature(int type, int starting_room) {
	Creature *temp;
	if(type == 0) {
		PC *pc = this->createPC(starting_room);
		//std::cout << "PC Created." << std::endl;
		temp = static_cast<Creature *>(pc);
	} else if(type == 1) {
		Animal *ani = this->createAnimal(this->created_creatures, starting_room);
		//std::cout << "Animal Created Named " << ani->getName() << " starting room " << ani->getCurrentRoomName() << std::endl;
		temp = static_cast<Creature *>(ani);
	} else if(type == 2) {
		NPC * npc = this->createNPC(this->created_creatures, starting_room);
		//std::cout << "NPC Created Named " << npc->getName() << " starting room " << npc->getCurrentRoomName() << std::endl;
		temp = static_cast<Creature *>(npc);
	}
	return temp;
}

Animal * ObjectCreator::createAnimal(int name, int starting_room) {
	std::cout << "ObjectCreator - Animal Found with name " << name << " and room " << starting_room << ". Creating." << std::endl;
	Animal *temp = new Animal();
	temp->setName(name);
	temp->setType(1);
	temp->setCurrentRoomName(starting_room);
	this->created_creatures++;
	return temp;
}

NPC * ObjectCreator::createNPC(int name, int starting_room) {
	std::cout << "ObjectCreator - NPC Found with name " << name << " and room " << starting_room << ". Creating." << std::endl;
	NPC *temp = new NPC();
	temp->setName(name);
	temp->setType(2);
	temp->setCurrentRoomName(starting_room);
	this->created_creatures++;
	return temp;
}

PC * ObjectCreator::createPC(int starting_room) {
	std::cout << "ObjectCreator - PC Found. Creating with starting room " << starting_room << std::endl;
	PC *pc = new PC();
	pc->setType(0);
	pc->setCurrentRoomName(starting_room);
	pc->setRespect(40);
	return pc;
}


