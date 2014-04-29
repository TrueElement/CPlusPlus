#include "../include/CLI.hpp"

CLI::CLI(void) {
	this->game = NULL;
	this->obj = NULL;
	this->split = new std::vector<std::string>();
	this->split_command = new std::string();
	this->split_name = new std::string();
	this->strm = NULL;
}

CLI::~CLI(void) {
	delete[] split;
	delete[] split_command;
	delete[] split_name;
}

Game * CLI::getGame(void) {
	return this->game;
}

void CLI::setGame(Game *game) {
	this->game = game;
}

void CLI::setStringManip(StringManip *strm) {
	this->strm = strm;
}

void CLI::setObjectManager() {
	if(this->game != NULL) {
		this->obj = this->game->getObjectManager();
	}
}

void CLI::processCommandInput(std::vector<std::string> *commandInput) {
	unsigned int i = 0;
	std::string *command;
	std::string line;
	for(i = 0; i < commandInput->size(); i++) {
		line = commandInput->at(i);
		if(line.compare("\0") != 0) {
			command = &line;
			processUserCommand(command);
		} else {
			continue;
		}

	}
}

void CLI::startCLI() {
	bool continue_game = true;
	std::string *command = new std::string();
	std::cout << "Welcome to the game. Type help for a list of commands" << std::endl;
	std::cout << "Typing \"exit\" at any time quits the game." << std::endl;
	std::cout << "Commands are case sensitive" << std::endl;
	while(continue_game) {
		std::cout << "Enter a command:";
		std::getline(std::cin,*command);
		processUserCommand(command);
	}
}
/*
 * Possible Commands:
 * 1. Exit
 * 2. Help
 * 3. Move
 * 4. Look
 * 5. Split Command
 */
void CLI::processUserCommand(std::string *command_line) {
	//std::cout << "DEBUG - CLI - Processing User Command " << command_line->c_str() << std::endl;
	int command_count = strm->getWordCount(command_line->c_str(), command_line->size());
	if(strm->isSplitCommand(command_line)) {
		//std::cout << "DEBUG - CLI - Split Command Detected " << std::endl;
		std::vector<std::string> *split = strm->getSplitCommand(command_line);
		this->commandExternal(split);
	} else if(command_count == 1) {
		//std::cout << "DEBUG - CLI - Single Command Detected" << std::endl;
		this->processSingleCommand(command_line);
	} else {
		//std::cout << "DEBUG - CLI - Multi Command Detected" << std::endl;
		std::vector<std::string> *commands = strm->getTokens(command_line);
		processMultiCommand(commands);
	}
}



void CLI::processSingleCommand(std::string *command) {
	//std::cout << "DEBUG - CLI - Processing Single Command" << std::endl;
	if(command->compare("exit") == 0) {
		this->getGame()->exitGame();
	} else if(command->compare("help") == 0) {
		this->commandHelp();
	} else if(command->compare("look") == 0) {
		this->commandLook();
	} else if(command->compare("clean") == 0) {
		this->commandClean();
	} else if(command->compare("dirty") == 0) {
		this->commandDirty();
	} else if(command->compare("dani") == 0) {
		this->obj->printAnimals();
	} else if(command->compare("dnpc") == 0) {
		this->obj->printNpcs();
	}
}

void CLI::processMultiCommand(std::vector<std::string> *commands) {
	//std::cout << "DEBUG - CLI - Processing Multi Command" << std::endl;
	strm->printGivenInput(commands);
	std::string *baseCommand = new std::string();
	std::string *modifierCommand = new std::string();
	unsigned int i = 0;
	for(i = 0; i < commands->size(); i++) {
		if(baseCommand->empty()) {
			baseCommand = &(commands->at(i));
			modifierCommand = &(commands->at(i+1));
			continue;
		} else {
			this->processCommandPair(baseCommand, modifierCommand);
			baseCommand->clear();
			modifierCommand->clear();
			continue;
		}
	}
}

void CLI::processCommandPair(std::string *baseCommand, std::string *modifierCommand) {
	//std::cout << "DEBUG - CLI - Processing Command Pair" << std::endl;
	if(baseCommand->compare("move") == 0) {
		//std::cout << "DEBUG - CLI - Base Command move detected " << std::endl;
		this->commandMove(modifierCommand);
	} else if(baseCommand->compare("look") == 0) {
		//std::cout << "DEBUG - CLI - Base Command look detected" << std::endl;
		this->commandLook(modifierCommand);
	}
}



void CLI::commandMove(std::string *direction) {
	bool moved = false;
	PC *pc = obj->getPC();
	if(direction->compare("north") == 0) {
		moved = pc->move(0);
	} else if(direction->compare("south") == 0) {
		moved = pc->move(1);
	} else if(direction->compare("east") == 0) {
		moved = pc->move(2);
	} else if(direction->compare("west") == 0) {
		moved = pc->move(3);
	} else {
		std::cout << direction << " is not a valid direction." << std::endl;
		return;
	}
}

void CLI::processSplitCommand() {
	//std::cout << "DEBUG - CLI - Processing Split Command. Calling Command External." << std::endl;
	//this->commandExternal(this->split_name, this->split_command);
	this->split->clear();
	this->split_name->clear();
	this->split_command->clear();
}

void CLI::setSplitStrings() {
	std::cout << "DEBUG - CLI - Setting Split Strings" << std::endl;
	*split_name = split->at(0);
	*split_command = split->at(1);
}

void CLI::commandExternal(std::vector<std::string> *command) {
	int creature_name = atoi(command->at(0).c_str());
	Creature *temp = obj->getCreatureByName(creature_name);
	if(temp == NULL) {
		std::cout << "There is no one named " << command->at(0) <<"!" << std::endl;
		return;
	} else {
		if(temp->getType() == 1) {
			Animal *ani = obj->convertCreatureToAnimal(temp);
				ani->processCommand(&(command->at(1)));
		} else if(temp->getType() == 2) {
			NPC *npc = obj->convertCreatureToNPC(temp);
				npc->processCommand(&(command->at(1)));
		}
	}

}

void CLI::commandHelp() {
	std::cout << "Possible Commands are:" << std::endl;
	std::cout << "   help - print this message" << std::endl;
	std::cout << "   look - print the current contents of this room" << std::endl;
	std::cout << "   move (direction) - move to the room in the specified direction." << std::endl;
	std::cout << "      Possible directions are: north south east west" << std::endl;
	std::cout << "   clean - clean the current room" << std::endl;
	std::cout << "   dirty - make the current room more dirty" << std::endl;
	std::cout << "   (name):(action) - Make creature named (name) perform action (action)" << std::endl;
	std::cout << "      Possible actions are: move, clean, dirty" << std::endl;
}

void CLI::commandLook() {
	PC *pc = obj->getPC();
	pc->look();
}

void CLI::commandLook(std::string *direction) {
	obj->getPC()->look(direction);
}

void CLI::commandClean() {
	obj->getPC()->commandClean();
}

void CLI::commandDirty() {
	obj->getPC()->commandDirty();
}

