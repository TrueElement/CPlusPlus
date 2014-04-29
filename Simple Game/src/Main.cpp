#include "Game.h"
#include "Room.h"
#include "Creature.h"
#include "Test.h"

int main(int argc, char **argv) {
	//Input Arrays
	std::vector<std::string> *input;
	std::vector<std::string> *creationInput;
	std::vector<std::string> *commandInput;

	//Setup Game Objects
	//std::cout << "DEBUG - Main - Setting Up String Manip" << std::endl;
	StringHelper *strm = new StringHelper();

	//std::cout << "DEBUG - Main - Setting Up Object Manager" << std::endl;
	ObjectManager *objm = new ObjectManager();
	objm->setStringHelper(strm);

	//std::cout << "DEBUG - Main - Setting Up Object Creator " << std::endl;
	ObjectCreator *objc = new ObjectCreator();
	objc->setObjectManager(objm);
	objm->setObjectCreator(objc);

	//std::cout << "DEBUG - Main -Setting Up Game " << std::endl;
	Game *game = new Game();
	game->setStringHelper(strm);
	game->setObjectManager(objm);
	objm->setGame(game);

	//std::cout << "DEBUG - Main - Setting Up CLI " << std::endl;
	CLI *cli = new CLI();
	cli->setGame(game);
	cli->setObjectManager();
	cli->setStringHelper(strm);
	game->setCLI(cli);
	objm->setCLI(cli);

	//std::cout << "DEBUG - Main - Setting Up Input " << std::endl;
	Input *inp = new Input();
	inp->setGame(game);
	inp->setObjectCreator(objc);
	inp->setObjectManager(objm);
	inp->setStringHelper(strm);
	objm->setInput(inp);

	if(argc > 1) {
		std::string inputFile(argv[1]);
		inp->setInputFilePath(&inputFile);
		inp->checkInputFile();
		input = inp->parseInputFile();
		creationInput = inp->getCreationInput(input);
		commandInput = inp->getCommandInput(input);
		inp->parseCreationInput(creationInput);
		cli->processCommandInput(commandInput);
		objm->setupRoomNeighborPointers();
		objm->setupCreatureRoomPointers();
		objm->setupPcRoomPointers();
		objm->processInitialRoomState();
		cli->startCLI();
	} else {
		std::cout << "Parsing Initial Input - Main.cpp" << std::endl;
		//Parse Input
		input = inp->parseStdInput();
		creationInput = inp->getCreationInput(input);
		commandInput = inp->getCommandInput(input);

		//std::cout << "Setting Up the Game - Main.cpp" << std::endl;
		//Setup Game
		//std::cout << "Parsing Creation Input - Main.cpp" << std::endl;
		inp->parseCreationInput(creationInput);
		//std::cout << "Setting Creature Room Pointers - Main.cpp" << std::endl;
		objm->setupCreatureRoomPointers();
		//std::cout << "Setting Room Neighbor Pointers - Main.cpp" << std::endl;
		objm->setupRoomNeighborPointers();
		objm->processInitialRoomState();
		//std::cout << "Starting CLI - Main.cpp" << std::endl;
		//Start Game
		//std::cout << "Parsing Initial Command Input - Main.cpp" << std::endl;
		cli->processCommandInput(commandInput);
		cli->startCLI();
	}
}





