#include "../include/Game.h"

/*
 * Start Game Function Declarations
 */
Game::Game() {
	this->cmd = 0;
	this->store = 0;
	this->strm = NULL;
}

Game::~Game() {

}

void Game::startGame() {
	cmd->startCLI();
}

void Game::exitGame() {
	std::cout << "Exiting Game. Thanks for Playing!" << std::endl;
	std::cout << "Final Respect was: " << this-store->getPC()->getRespect() << std::endl;
	exit(0);
}

void Game::setObjectManager(ObjectManager *obj) {
	this->store = obj;
}

ObjectManager * Game::getObjectManager() {
	return this->store;
}

void Game::setCLI(CLI *cli) {
	this->cmd = cli;
}

CLI * Game::getCLI() {
	return this->cmd;
}

void Game::setStringHelper(StringHelper *strm) {
	this->strm = strm;
}

StringHelper * Game::getStringHelper() {
	return this->strm;
}
