#include "Room.h"

Neighbors::Neighbors() : northName(-1), southName(-1), eastName(-1), westName(-1) {
	this->north = NULL;
	this->south = NULL;
	this->east = NULL;
	this->west = NULL;
}

Neighbors::~Neighbors() {

}
 void Neighbors::setNorth(Room *north) {
	this->north = north;
}

void Neighbors::setNorthName(int name) {
	this->northName = name;
}

Room * Neighbors::getNorth() {
	if(this->northName == -1) {
		return NULL;
	} else {
		return this->north;
	}
}

int Neighbors::getNorthName() {
	return this->northName;
}

void Neighbors::setSouth(Room *south) {
	this->south = south;
}

void Neighbors::setSouthName(int name) {
	this->southName = name;
}

Room * Neighbors::getSouth() {
	if(this->southName == -1) {
		return NULL;
	} else {
		return this->south;
	}
}

int Neighbors::getSouthName() {
	return this->southName;
}

void Neighbors::setEast(Room *east) {
	this->east = east;
}

void Neighbors::setEastName(int name) {
	this->eastName = name;
}

Room * Neighbors::getEast() {
	if(this->eastName == -1) {
		return NULL;
	} else {
		return this->east;
	}
}

int Neighbors::getEastName() {
	return this->eastName;
}

void Neighbors::setWest(Room *west) {
	this->west = west;
}

void Neighbors::setWestName(int name) {
	this->westName = name;
}

Room * Neighbors::getWest() {
	if(this->westName == -1) {
		return NULL;
	} else {
		return this->west;
	}
}

int Neighbors::getWestName() {
	return this->westName;
}
