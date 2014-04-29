#include "Game.h"

void Input::setInputFilePath(std::string *file) {
    this->input_file = file;
}

void Input::askForInputFile() {
    std::string input;
    std::cout << "Enter Input File Path:";
    std::getline(std::cin,input);
    input_file = &input;
    if(checkInputFile()) {
        parseInputFile();
    } else {
        std::cout << std::endl << "Error opening input file." << std::endl;
        askForInputFile();
    }
}

bool Input::checkInputFile() {
    std::ifstream temp;
    temp.open(input_file->c_str());
    if(temp.fail()) {
        temp.close();
        return false;
    } else {
        temp.close();
        return true;
    }
}

std::vector<std::string> * Input::parseInputFile() {
    std::vector<std::string> *lines = new std::vector<std::string>();
    std::string line;
    std::ifstream temp;
    temp.open(this->input_file->c_str());

    if(temp.fail()) {
        std::cerr << "Input File open failed." << std::endl;
        exit(1);
    }
    while(!temp.eof()) {
    	getline(temp, line);
    	lines->push_back(line);
    }

    return lines;
}
