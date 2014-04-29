#ifndef INPUT_H
#define INPUT_H
#include <vector>
#include <string>

class Input {
    public:
        Input();
        ~Input();
        void setGame(Game *game);
        void setInputFilePath(std::string *file);
        void askForInputFile();
        bool checkInputFile();
        std::vector<std::string> * parseInputFile();
        void parseCreationInput(std::vector<std::string> *creationInput);
        std::vector<std::string> * parseStdInput();
        std::vector<std::string> * getCreationInput(std::vector<std::string> *input);
        std::vector<std::string> * getCommandInput(std::vector<std::string> *input);
        std::vector<int> * tokenizeLine();
        void processSetupLine(std::vector<int> *token_array);
        void createRoom(std::vector<int> *token_array);
        void createCreature(int type, int starting_room);
        void createCreature(std::vector<int> *token_array);
        void setObjectCreator(ObjectCreator *toSet);
        ObjectCreator * getObjectCreator();
        void setObjectManager(ObjectManager *toSet);
        ObjectManager * getObjectManager();
        void setStringHelper(StringHelper *strm);
        StringHelper * getStringHelper();
    private:
        std::string *input_file;
        Game *game;
        ObjectCreator *objc;
        ObjectManager *objm;
        StringHelper *strm;
        int expected_creatures;
        int expected_rooms;
};
#endif
