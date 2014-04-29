#include "../include/Input.hpp"

Input::Input() : input_file(0), expected_creatures(-1), expected_rooms(-1) {
	this->game = NULL;
	this->objc = NULL;
	this->objm = NULL;
	this->strm = NULL;
}

Input::~Input() {

}

void Input::setObjectCreator(ObjectCreator *toSet) {
	this->objc = toSet;
}

ObjectCreator * Input::getObjectCreator() {
	return this->objc;
}

void Input::setObjectManager(ObjectManager *toSet) {
	this->objm = toSet;
}

ObjectManager * Input::getObjectManager() {
	return this->objm;
}

void Input::setGame(Game *game) {
	this->game = game;
}

void Input::setStringHelper(StringHelper *strm) {
	this->strm = strm;
}

StringHelper * Input::getStringHelper() {
	return this->strm;
}

void Input::createCreature(std::vector<int> *token_array) {
	Creature *temp = this->objc->createCreature(token_array);
	this->objm->addCreature(temp);
}

void Input::createRoom(std::vector<int> *token_array) {
	//std::cout << "DEBUG - Input - Attempting to create room." << std::endl;
	Room *temp = this->objc->createRoom(token_array);
	//std::cout << "DEBUG - Input - Adding room to Object Manager." << std::endl;
	this->objm->addRoom(temp);
}

void Input::processSetupLine(std::vector<int> *token_array) {
	if(token_array->size() == 1) {
		if(this->expected_rooms == -1) {
			this->expected_rooms = token_array->at(0);
			std::cout << "DEBUG - Input - Expecting  " << this->expected_rooms << " rooms." << std::endl;
		} else if(this->expected_creatures == -1) {
			this->expected_creatures = token_array->at(0);
			std::cout << "DEBUG - Input - Expecting " << this->expected_creatures << " creatures." << std::endl;
		} else {
			std::cerr << "Bad Input. Rooms and Creatures have already been set.";
			exit(1);
		}
	} else if(token_array->size() == 2) {
		//std::cout << "DEBUG - Input - Calling Create Creature" << std::endl;
		createCreature(token_array);
	} else if(token_array->size() == 5) {
		//std::cout << "DEBUG - Input - Calling Create Room " << std::endl;
		createRoom(token_array);
	}
}

std::vector<std::string> * Input::parseStdInput() {
	std::cout << "Starting Input Parse from stdin" << std::endl;
	std::vector<std::string> *input = new std::vector<std::string>();
	std::string line;
	while(std::getline(std::cin, line)) {
		if(line.empty()) {
			break;
		} else {
			input->push_back(line);
		}
	}
	std::cout << "Finished Input Parse from stdin. Returning." << std::endl;
	return input;
}


void Input::parseCreationInput(std::vector<std::string> *creationInput) {
	unsigned int i = 0;
	int token_count = 0;
	std::vector<int> *token_array;
	std::string line;
	std::vector<std::string> *tokens;

	for(i = 0; i < creationInput->size(); i++) {
		line = creationInput->at(i);
		token_count = this->strm->getWordCount(line.c_str(), line.size());
		tokens = this->strm->getTokens(&line);
		token_array = this->strm->getIntTokenArray(tokens);
		processSetupLine(token_array);
	}
}

std::vector<std::string> * Input::getCreationInput(std::vector<std::string> *input) {
	std::vector<std::string> *creationInput = new std::vector<std::string>();
	std::string line;
	unsigned int i = 0;
	int tokens = 0;
	int expected_rooms = -1;
	int expected_creatures = -1;
	int found_rooms = 0;
	int found_creatures = 0;
	bool inRoom = false;
	for(i = 0; i < input->size(); i++) {
		if(expected_rooms == found_rooms) {
			if(expected_creatures == found_creatures) {
				break;
			}
		}
		line = input->at(i);
		tokens = strm->getWordCount(line.c_str(), line.size());
		if(tokens == 1) {
			if(inRoom == false) {
				inRoom = true;
				expected_rooms = atoi(line.c_str());
				creationInput->push_back(line);
			} else {
				inRoom = false;
				expected_creatures = atoi(line.c_str());
				creationInput->push_back(line);
			}
		} else {
			if(inRoom) {
				found_rooms++;
				creationInput->push_back(line);
			} else {
				found_creatures++;
				creationInput->push_back(line);
			}
		}
	}
	return creationInput;
}

std::vector<std::string> * Input::getCommandInput(std::vector<std::string> *input) {
	std::vector<std::string> *commandInput = new std::vector<std::string>();
	std::string line;
	unsigned int i = 0;
	int tokens = 0;
	int expected_rooms = -1;
	int expected_creatures = -1;
	int found_rooms = 0;
	int found_creatures = 0;
	bool inRoom = false;
	for(i = 0; i < input->size(); i++) {
		if(expected_rooms == found_rooms) {
			if(expected_creatures == found_creatures) {
				line = input->at(i);
				commandInput->push_back(line);
				continue;
			}
		}
		line = input->at(i);
		tokens = strm->getWordCount(line.c_str(), line.size());
		if(tokens == 1) {
			if(inRoom == false) {
				inRoom = true;
				expected_rooms = atoi(line.c_str());
			} else {
				inRoom = false;
				expected_creatures = atoi(line.c_str());
			}
		} else {
			if(inRoom) {
				found_rooms++;
			} else {
				found_creatures++;
			}
		}
	}
	return commandInput;
}


