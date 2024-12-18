#pragma once

#include <iostream>
#include <string>

class Color {
private:
    std::string id;
    std::string name;
    std::string hex;
    unsigned int r;
    unsigned int g;
    unsigned int b;

public:
    Color() : id("black"), name("Black"), hex("#000000"), r(0), g(0), b(0) {}
    Color(unsigned int r, unsigned int g, unsigned int b);

    void setID(std::string id);
    std::string getID();
    void setName(std::string name);
    std::string getName();
    void setHex(std::string hex);
    std::string getHex();
    void setR(unsigned int r);
    unsigned int getR();
    void setG(unsigned int g);
    unsigned int getG();
    void setB(unsigned int b);
    unsigned int getB();

    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }

    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "Name: " << color.name << " hex: "  << color.hex;
        return os;
    }
};                                                                                      

unsigned int hashFunc(Color&, unsigned int tableSize);