#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<string>
#include<sstream>
#include<SFML/Graphics.hpp>
#include "Globals.h"

using namespace std;

class Date {
	int Day;
	int Month;
	int Year;
	sf::Font font;
public:
	Date();
	Date(int, int, int);
	Date(const Date&);

	// Functions
	void PrintDate(sf::RenderWindow& window);

	~Date();
};

#endif
