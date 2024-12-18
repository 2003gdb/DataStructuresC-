#include "colors.h"

Color::Color(unsigned int r, unsigned int g, unsigned int b) {
     this->r = r;
     this->g = g;                                                               
     this->b = b;
}

void Color::setID(std::string id) {
    this->id = id;
}

std::string Color::getID() {
	return(name);
}

void Color::setName(std::string name) {
    this->name = name;
}

std::string Color::getName() {
	return(name);
}

void Color::setHex(std::string hex) {
    this->hex = hex;
}

std::string Color::getHex() {
    return(hex);                                                              
}

void Color::setR(unsigned int r) {
	this->r = r;
}

unsigned int Color::getR() {
    return(r);
}

void Color::setG(unsigned int g) {
    this->g = g;
}

unsigned int Color::getG() {
    return(g);                                                                
}    

void Color::setB(unsigned int b) {
    this->b = b;
}

unsigned int Color::getB() {
    return(b);
}

unsigned int hashFunc(Color& color, unsigned int tableSize){
    return (color.getR() + color.getG() + color.getB()) % tableSize;
}

