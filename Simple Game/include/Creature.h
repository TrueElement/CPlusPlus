#ifndef CREATURE_H
#define CREATURE_H
#include <iostream>
class Room;

/*
 * Creature Superclass Declaration
 */
class Creature {
    public:
        Creature();
        ~Creature();
        void print();
        void performAction(bool type);
        void speak(bool pos_neg);
        bool move(int direction);
        bool moveRoom(Room *toMove);
        void look();
        int getName();
        void setName(int creature_name);
        int getType();
        void setType(int creature_type);
        Room * getCurrentRoom();
        void setCurrentRoom(Room *new_room);
        void setCurrentRoomName(int room_name);
        int getCurrentRoomName();
        bool moveOnStateChange();
        bool processStateChange();
        void commandClean();
        void commandDirty();
    private:
        int type;
        int currentRoomName;
        int name;
        Room *current_room;
};

/*
 * Animal Subclass Declaration
 */
class Animal : public Creature {
public:
	Animal();
	~Animal();
	void speak(bool pos_neg);
	void print();
	bool move(int direction);
	bool checkRoom();
	void enteringRoom();
	bool processStateChange();
	bool processCommand(std::string *command);
	bool moveOnStateChange();
	bool moveRoom(Room *room);
	void processInitialState();
    void commandClean();
    void commandDirty();
};

/*
 * NPC Subclass Declaration
 */
class NPC: public Creature {
public:
	NPC();
	~NPC();
	void speak(bool pos_neg);
	void print();
	bool move(int direction);
	bool checkRoom();
	bool processStateChange();
	bool processCommand(std::string *command);
	bool moveOnStateChange();
	void processInitialState();
    bool moveRoom(Room *room);
    void commandClean();
    void commandDirty();
    void enteringRoom();
};

/*
 * PC Subclass Declaration
 */
class PC : public Creature {
    public:
		PC();
		~PC();
        void decrementRespect();
        int getRespect();
        void setRespect(int new_respect);
        void modRespect(int modify);
        void print();
        bool move(int direction);
        void printMoveFail(std::string direction);
        void printMoveSuccess(std::string direction);
        void look();
        void look(std::string *direction);
        bool commandClean();
        bool commandDirty();
    private:
        int respect;
        bool moveNorth();
        bool moveSouth();
        bool moveEast();
        bool moveWest();
};
#endif
