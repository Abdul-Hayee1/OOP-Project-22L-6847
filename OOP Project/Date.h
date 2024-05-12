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
	// Constructors
	Date();
	Date(int, int, int);
	Date(const Date&);

	// Getters
	int getDay();
	int getMonth();
	int getYear();

	Date& operator=(const Date& obj);
	bool operator==(const Date& other) const;

	// Functions
	void PrintDate(sf::RenderWindow& window);

	~Date();
};

#endif
