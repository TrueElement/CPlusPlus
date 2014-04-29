#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <vector>
#include "Creature.h"
#include "Game.h";
class Neighbors;
class Contents;

class Room {
    public:
		Room();
		~Room();
		void setObjectManager(ObjectManager *objm);
		ObjectManager * getObjectManager();
        void setName(int room_name);
        int getName();
        bool hasPc();
        int getState();
        void setState(int new_state);
        bool modState(int action);
        bool addCreature(Creature *toAdd);
        bool isFull();
        void removeCreature(Creature *toRemove);
        void removeCreatureByName(int name);
        void setNeighbor(int direction, Room *neighbor);
        void setNeighborName(int direction, int neighbor_name);
        int getNeighborName(int direction);
        void setupNeighbors();
        void print();
        void roomStateChange();
        void checkRemoveFromGame(bool remove_animal, Creature *toRemove);
        void allSpeak(bool pos_neg);
        void printState();
        Room * getNeighbor(int direction);
        Creature * getCreatureByName(int name);
        Contents * getContents();
    private:
        void shiftCreatureArray(int removed_index);
        int num_creatures;
        int state;
        int name;
        Neighbors *neighbors;
        Contents *contains;
        ObjectManager *objm;
};

class Neighbors {
    public:
		Neighbors();
		~Neighbors();
		void setNorth(Room *north);
		void setNorthName(int name);
		Room * getNorth();
		int getNorthName();
		void setSouth(Room *south);
		void setSouthName(int name);
		Room * getSouth();
		int getSouthName();
		void setEast(Room *east);
		void setEastName(int name);
		Room * getEast();
		int getEastName();
		void setWest(Room *west);
		void setWestName(int name);
		Room * getWest();
		int getWestName();
    private:
		Room *north;
		Room *south;
		Room *east;
		Room *west;
		int northName;
		int southName;
		int eastName;
		int westName;

};

class Contents {
public:
	Contents();
	~Contents();
	bool add(Animal *toAdd);
	bool add(NPC *toAdd);
	bool add(PC *pc);
	void remove(int name);
	Creature * get(int name);
	void setupVectors();
	int getTotal();
	bool isFull();
	bool hasPC();
	PC * getPC();
	void removePC();
	Creature * getCreatureByIndex(int index);
private:
	static const int MAX_SIZE = 10;
	std::vector<Animal *> *ani;
	std::vector<NPC *> *npc;
	PC *pc;
	bool has_pc;
};
#endif
