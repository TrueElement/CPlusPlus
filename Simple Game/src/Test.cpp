#include "Test.h"


/**
 * Start Creature Test Function Declaration
 */
creatureTest::creatureTest(void) {

}

creatureTest::~creatureTest(void) {

}

void creatureTest::startCreatureTest(void) {
    Creature *test1;
        test1 = new Creature();
        test1->setName(0);
        test1->setType(1);
    test1->print();
}

/*
 *
 *
 *
 * Start Room Test Function Declaration
 *
 *
 *
 *
 */
roomTest::roomTest(void) {

}

roomTest::~roomTest(void) {

}

void roomTest::startRoomTest(void) {
    Room *testRoom;
        testRoom = new Room();
        testRoom->setName(5);
        testRoom->setState(1);

    Creature *creature0;
        creature0 = new Creature();
        creature0->setName(0);
        creature0->setType(1);
        creature0->setCurrentRoom(testRoom);
        creature0->setCurrentRoomName(testRoom->getName());
    Creature *creature1;
        creature1 = new Creature();
        creature1->setName(0);
        creature1->setType(1);
        creature1->setCurrentRoom(testRoom);
        creature1->setCurrentRoomName(testRoom->getName());

    Creature *creature2;
        creature2 = new Creature();
        creature2->setName(0);
        creature2->setType(1);
        creature2->setCurrentRoom(testRoom);
        creature2->setCurrentRoomName(testRoom->getName());

    Creature *creature3;
        creature3 = new Creature();
        creature3->setName(0);
        creature3->setType(1);
        creature3->setCurrentRoom(testRoom);
        creature3->setCurrentRoomName(testRoom->getName());

    Creature *creature4;
        creature4 = new Creature();
        creature4->setName(0);
        creature4->setType(1);
        creature4->setCurrentRoom(testRoom);
        creature4->setCurrentRoomName(testRoom->getName());

    Creature *creature5;
        creature5 = new Creature();
        creature5->setName(0);
        creature5->setType(1);
        creature5->setCurrentRoom(testRoom);
        creature5->setCurrentRoomName(testRoom->getName());

    Creature *creature6;
        creature6 = new Creature();
        creature6->setName(0);
        creature6->setType(1);
        creature6->setCurrentRoom(testRoom);
        creature6->setCurrentRoomName(testRoom->getName());

    Creature *creature7;
        creature7 = new Creature();
        creature7->setName(0);
        creature7->setType(1);
        creature7->setCurrentRoom(testRoom);
        creature7->setCurrentRoomName(testRoom->getName());

    Creature *creature8;
        creature8 = new Creature();
        creature8->setName(0);
        creature8->setType(1);
        creature8->setCurrentRoom(testRoom);
        creature8->setCurrentRoomName(testRoom->getName());

    Creature *creature9;
        creature9 = new Creature();
        creature9->setName(0);
        creature9->setType(1);
        creature9->setCurrentRoom(testRoom);
        creature9->setCurrentRoomName(testRoom->getName());

    Creature *creature10;
        creature10 = new Creature();
        creature10->setName(0);
        creature10->setType(1);
        creature10->setCurrentRoom(testRoom);
        creature10->setCurrentRoomName(testRoom->getName());

    Creature *creature11;
        creature11 = new Creature();
        creature11->setName(0);
        creature11->setType(1);
        creature11->setCurrentRoom(testRoom);
        creature11->setCurrentRoomName(testRoom->getName());

    Creature *creature12;
        creature12 = new Creature();
        creature12->setName(0);
        creature12->setType(1);
        creature12->setCurrentRoom(testRoom);
        creature12->setCurrentRoomName(testRoom->getName());

    std::cout << "Adding Creature 0 to Room" << std::endl;
    testRoom->addCreature(creature0);


    std::cout << "Adding Creature 1 to Room" << std::endl;
    testRoom->addCreature(creature1);


    std::cout << "Adding Creature 1 to Room" << std::endl;
    testRoom->addCreature(creature1);


    std::cout << "Adding Creature 2 to Room" << std::endl;
    testRoom->addCreature(creature2);


    std::cout << "Adding Creature 3 to Room" << std::endl;
    testRoom->addCreature(creature3);


    std::cout << "Adding Creature 4 to Room" << std::endl;
    testRoom->addCreature(creature4);


    std::cout << "Adding Creature 5 to Room" << std::endl;
    testRoom->addCreature(creature0);


    std::cout << "Adding Creature 6 to Room" << std::endl;
    testRoom->addCreature(creature6);


    std::cout << "Adding Creature 7 to Room" << std::endl;
    testRoom->addCreature(creature7);


    std::cout << "Adding Creature 8 to Room" << std::endl;
    testRoom->addCreature(creature9);


    std::cout << "Adding Creature 9 to Room" << std::endl;
    testRoom->addCreature(creature9);


    std::cout << "Adding Creature 10 to Room" << std::endl;
    testRoom->addCreature(creature10);

    std::cout << "Printing Room: " << std::endl;
    testRoom->print();
}

/*
 *
 *
 *
 *
 *
 *
 *
 *
 * Start Input Test Class Declaration
 *
 *
 *
 *
 *
 *
 */
inputTest::inputTest() {
	this->inp = NULL;
	this->strm = NULL;
}

void inputTest::setInput(Input *inp) {
	this->inp = inp;
}

void inputTest::setStringManip(StringManip *strm) {
	this->strm = strm;
}

void inputTest::startInputTest() {
	std::cout << "---Starting Input Test---" << std::endl;

	std::cout << "-----Start Getting Input-----" << std::endl;

	std::cout << "Getting Input from stdin" << std::endl;
	std::vector<std::string> *input = this->inp->parseStdInput();
	std::cout << "Finished Getting Input from stdin" << std::endl;

	std::cout << "Getting Creation Input from Input" << std::endl;
	std::vector<std::string> *creationInput = this->inp->getCreationInput(input);
	std::cout << "Finished Getting Creation Input" << std::endl;

	std::cout << "Getting Command Input from Input" << std::endl;
	std::vector<std::string> *commandInput = this->inp->getCommandInput(input);
	std::cout << "Finished Getting Command Input" << std::endl;

	std::cout << "-----End Getting Input-----" << std::endl;

	std::cout << "-----Start Printing Input-----" << std::endl;

	std::cout << "Printing All Input Vector" << std::endl;
	this->strm->printGivenInput(input);
	std::cout << "Done Printing All Input Vector" << std::endl;

	std::cout << "Printing Creation Input Vector" << std::endl;
	this->strm->printGivenCreationInput(creationInput);
	std::cout << "Done Printing Creation Input Vector" << std::endl;

	std::cout << "Printing Command Input Vector" << std::endl;
	this->strm->printGivenInput(commandInput);
	std::cout << "Done Printing Command Input Vector" << std::endl;

	std::cout << "-----End Printing Input-----" << std::endl;
}



/*
 *
 *
 *
 *
 *
 *
 *
 *
 * Start Object Manager Test
 *
 *
 *
 *
 *
 */

objectManagerTest::objectManagerTest() {
	this->inp = NULL;
	this->strm = NULL;
}

void objectManagerTest::setInput(Input *inp) {
	this->inp = inp;
}

void objectManagerTest::setStringManip(StringManip *strm) {
	this->strm = strm;
}

void objectManagerTest::startObjectManagerTest() {
	std::vector<std::string> *input;
	std::vector<std::string> *creationInput;
	std::cout << "-----Starting Object Manager Test-----" << std::endl;

	std::cout << "Reading Input" << std::endl;
	input = this->inp->parseStdInput();
	std::cout << "Getting Creation Input" << std::endl;
	creationInput = this->inp->getCreationInput(input);
	std::cout << "Finished Reading Input" << std::endl;

	std::cout << "Starting Creation Input Parse" << std::endl;
	this->inp->parseCreationInput(creationInput);
	std::cout << "Finished Creation Input Parse" << std::endl;

}




/*
 *
 *
 *
 *
 *
 * State Change Test
 *
 *
 *
 *
 *
 */
stateChangeTest::stateChangeTest() {

}

void stateChangeTest::startStateChangeTest() {
	Animal *ani = new Animal();
		ani->setName(0);
		ani->setType(1);
		ani->processStateChange();

	NPC *npc = new NPC();
		npc->setName(1);
		npc->setType(2);
		npc->processStateChange();

	Creature *temp;
		temp = static_cast<Creature *>(ani);
		std::cout << "Attempting Casted Print 1" << std::endl;
		temp->processStateChange();
		std::cout << "Getting Casted Animal Type" << std::endl;
		std::cout << temp->getType() << std::endl;

	Creature *temp2;
		temp2 = static_cast<Creature *>(npc);
		std::cout << "Attempting Casted Print 2" << std::endl;
		temp2->processStateChange();
		std::cout << "Getting Casted NPC Type" << std::endl;
		std::cout << temp2->getType() << std::endl;
		std::cout << std::endl;

	Animal *ani1 = static_cast<Animal *>(temp);
		std::cout << "Attempting Recasted Print 1" << std::endl;
		ani1->processStateChange();
		std::cout << std::endl;
	NPC *npc1 = static_cast<NPC *>(temp2);
		std::cout << "Attempting Recasted Print 2" << std::endl;
		npc1->processStateChange();
		std::cout << std::endl;


}
