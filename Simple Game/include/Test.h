#ifndef TEST_H
#define TEST_H
#include "Game.h"
#include "Creature.h"
#include "Room.h"


class creatureTest {
public:
	creatureTest(void);
	~creatureTest(void);
	void startCreatureTest(void);
private:
};

class roomTest {
public:
	roomTest(void);
	~roomTest(void);
	void startRoomTest(void);
private:
};

class inputTest {
public:
	inputTest(void);
	~inputTest(void);
	void startInputTest(void);
	void setInput(Input *inp);
	void setStringManip(StringManip *strm);
private:
	Input *inp;
	StringManip *strm;
};

class objectManagerTest {
public:
	objectManagerTest(void);
	~objectManagerTest(void);
	void setInput(Input *inp);
	void setStringManip(StringManip *strm);
	void startObjectManagerTest(void);
private:
	Input *inp;
	StringManip *strm;
};

class stateChangeTest {
public:
	stateChangeTest();
	~stateChangeTest();
	void startStateChangeTest();
};
#endif
