/*
 * File Name:
 * Version:
 * Author: Tim Fleece
 * Project:
 */

#ifndef STRING_HELP_H
#define STRING_HELP_H
#include <iostream>
#include<string>

class Game;

class StringHelper {
public:
	StringHelper();
	~StringHelper();
	void setGame(Game *game);
	Game * getGame();
	int getWordCount(const char *line, int length);
	int stringToName(std::string *name);
	std::vector<std::string> * getTokens(std::string *line);
	std::vector<std::string> * getSplitCommand(std::string *split_command);
	bool isSplitCommand(std::string *command);
	void printGivenCreationInput(std::vector<std::string> *creationInput);
	void printGivenInput(std::vector<std::string> *input);
	void printRoomLine(std::string *line);
	void printCreatureLine(std::string *line);
	std::vector<int> * getIntTokenArray(std::vector<std::string> *tokens);
	bool isNumber(std::string *line);
private:
	Game *game;

};
#endif
