#ifndef GAME_H
#define GAME_H
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstring>
#include "Creature.h"
class ObjectManager;
class ObjectCreator;
class CLI;
class Input;
class StringHelper;

class Game {
    public:
        Game();
        ~Game();
        void startGame();
        void exitGame();
        void setObjectManager(ObjectManager *obj_man);
        ObjectManager * getObjectManager();
        void setCLI(CLI *cli);
        CLI * getCLI();
        void setStringHelper(StringHelper *strm);
        StringHelper * getStringHelper();
    private:
        ObjectManager *store;
        CLI *cmd;
        StringHelper *strm;
};
#endif
