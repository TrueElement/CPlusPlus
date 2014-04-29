#include "../include/StringHelper.hpp"

StringHelper::StringHelper() {
	this->game = NULL;
}
void StringHelper::setGame(Game *game) {
	this->game = game;
}

Game * StringHelper::getGame() {
	return this->game;
}
int StringHelper::getWordCount(const char *line, int length) {
	if(line == NULL) {
		return 0;
	}

	bool in_space = true;
	int num_words = 0;
	char cmp;
	for(int i = 0; i < length; i++){
		cmp = line[i];
		if(std::isspace(cmp)) {
			in_space = true;
		} else if(in_space) {
			num_words++;
			in_space = false;
		}
	}
	return num_words;
}

std::vector<std::string> * StringHelper::getTokens(std::string *line) {
	std::istringstream iss(*line);
	std::vector<std::string> *tokens = new std::vector<std::string>();
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
			std::back_inserter<std::vector<std::string> >(*tokens));
	return tokens;

}

std::vector<std::string> * StringHelper::getSplitCommand(std::string *split_command) {
	std::vector<std::string> *split = new std::vector<std::string>();
	std::string temp;
	const char *cstr = split_command->c_str();
	int length = strlen(cstr);
	for(int i = 0; i < length+2; i++) {
		char ati = cstr[i];
		if(ati != ':' && ati != '\0') {
			temp.push_back(ati);
			continue;
		} else {
			split->push_back(temp);
			temp.clear();
			if(ati == '\0') {
				break;
			}
			continue;
		}
	}

	return split;

}

bool StringHelper::isSplitCommand(std::string * command) {
	size_t found;
	found = command->find(':');
	if(found != std::string::npos) {
		return true;
	} else {
		return false;
	}
}

int StringHelper::stringToName(std::string *name) {
	int name_int = atoi(name->c_str());
	ObjectManager *obj = this->game->getObjectManager();
	if(obj->creatureExists(name_int)) {
		return name_int;
	} else {
		return -1;
	}
}

void StringHelper::printGivenCreationInput(std::vector<std::string> *input) {
	int tokens = 0;
	unsigned int i = 0;
	std::string line;
	bool inRooms = false;
	for(i = 0; i < input->size(); i++) {
		line = input->at(i);
		tokens = this->getWordCount(line.c_str(), line.size());
		if(tokens == 1) {
			if(inRooms == false) {
				inRooms = true;
				std::cout << "Given Input for " << line << " rooms." << std::endl;
			} else {
				inRooms = false;
				std::cout << "Given Input for " << line << " creatures." << std::endl;
			}
		} else {
			if(inRooms == true) {
				this->printRoomLine(&line);
			} else {
				this->printCreatureLine(&line);
			}
		}
	}
}

void StringHelper::printGivenInput(std::vector<std::string> *input) {
	unsigned int i = 0;
	for(i = 0; i < input->size(); i++) {
		std::cout << input->at(i) << std::endl;
	}
}

void StringHelper::printRoomLine(std::string *line) {
	std::vector<std::string> *tokens = this->getTokens(line);
	std::cout << "  Detected " << tokens->size() << " input tokens for room." << std::endl;
	std::cout << "     Room state is: " << tokens->at(0) << std::endl;
	std::cout << "     Room Neighbor to North is: " << tokens->at(1) << std::endl;
	std::cout << "     Room Neighbor to South is: " << tokens->at(2) << std::endl;
	std::cout << "     Room Neighbor to East is: " << tokens->at(3) << std::endl;
	std::cout << "     Room Neighbor to West is: " << tokens->at(4) << std::endl;
}

void StringHelper::printCreatureLine(std::string *line) {
	std::vector<std::string> *tokens = this->getTokens(line);
	std::cout << "  Detected " << tokens->size() << " input tokens for creature." << std::endl;
	std::cout << "     Creature Type is: " << tokens->at(0) << std::endl;
	std::cout << "     Creature Location is: " << tokens->at(1) << std::endl;

}

std::vector<int> * StringHelper::getIntTokenArray(std::vector<std::string> *tokens) {
	std::vector<int> *tokenVector = new std::vector<int>();
	std::string token;
	int token_int;
	unsigned int i = 0;
	for(i = 0; i < tokens->size(); i++) {
		token = tokens->at(i);
		token_int = atoi(token.c_str());
		tokenVector->push_back(token_int);
	}
	return tokenVector;
}

bool StringHelper::isNumber(std::string *line) {
	return isdigit(atoi(line->c_str()));
}


