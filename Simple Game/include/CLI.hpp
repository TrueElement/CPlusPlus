/*
 * File Name:
 * Version:
 * Author: Tim Fleece
 * Project:
 */

#ifndef CLI_H
#define CLI_H
#include <iostream>
#include <vector>
#include <string>

class Game;

class CLI {
    public:
        CLI();
        ~CLI();
        void startCLI();
        void processCommandInput(std::vector<std::string> *commandInput);
        void setGame(Game *game);
        void setObjectManager();
        void setStringManip(StringManip *strm);
        Game * getGame();
    private:
        ObjectManager *obj;
        Game *game;
        StringManip *strm;
        std::vector<std::string> *split;
        std::string *split_name;
        std::string *split_command;
        void setSplitStrings();
        void processSplitCommand();
        void processUserCommand(std::string *command_line);
        void processSingleCommand(std::string *command);
        void processMultiCommand(std::vector<std::string> *commands);
        void processCommandPair(std::string *baseCommand, std::string *modifierCommand);
        void commandExternal(std::vector<std::string> *command);
        void commandMove(std::string *direction);
        void commandHelp();
        void commandLook();
        void commandLook(std::string *direction);
        void commandClean();
        void commandDirty();
};
#endif
