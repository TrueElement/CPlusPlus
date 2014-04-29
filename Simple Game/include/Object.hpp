/*
 * File Name:
 * Version:
 * Author: Tim Fleece
 * Project:
 */

#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>

class ObjectManager {
    public:
        ObjectManager();
        ~ObjectManager();
        void setGame(Game *game);
        Game * getGame();
        void setInput(Input *inp);
        Input * getInput();
        void setCLI(CLI *cli);
        CLI * getCLI();
        void setObjectCreator(ObjectCreator *objc);
        ObjectCreator * getObjectCreator();
        void setStringHelper(StringHelper *strm);
        StringHelper * getStringHelper();
        Room * getRoomByName(int name);
        Creature * getCreatureByName(int name);
        void addCreature(Creature *toAdd);
        void addRoom(Room *toAdd);
        void setupRoomNeighborPointers();
        void setupCreatureRoomPointers();
        void setupPcRoomPointers();
        void roomStateChange(int name);
        PC * getPC();
        void setPC(PC *pc);
        bool creatureExists(int name);
        bool commandCreature(int name, std::string *command);
        Animal * convertCreatureToAnimal(Creature *toConvert);
        NPC * convertCreatureToNPC(Creature *toConvert);
        void removeCreatureFromGame(Creature *toRemove);
        void removeAnimalFromGame(Animal *toRemove);
        void removeNpcFromGame(NPC *toRemove);
        void processInitialRoomState();
        void printAnimals();
        void printNpcs();
    private:
        void checkRoomNull(Room *room);
        ObjectCreator *objc;
        Game *game;
        Input *input;
        CLI *cli;
        StringHelper *strm;
        std::vector<Animal *> *animals;
        std::vector<NPC *> *npcs;
        std::vector<Room *> *rooms;
        PC *pc;
        int room_count;
        int creature_count;
};


class ObjectCreator {
public:
	ObjectCreator();
	~ObjectCreator();
	Room * createRoom(std::vector<int> *token_array);
	Creature * createCreature(std::vector<int> *token_array);
	Creature * createCreature(int type, int name);
	Animal * createAnimal(int name, int starting_room);
	NPC * createNPC(int name, int starting_room);
	PC * createPC(int starting_room);
	ObjectManager * getObjectManager();
	void setObjectManager(ObjectManager *obj_man);
	int getNumCreatedRooms();
	int getNumCreatedCreatures();

private:
	bool pc_created;
	int created_rooms;
	int created_creatures;
	ObjectManager *store;

};

#endif
