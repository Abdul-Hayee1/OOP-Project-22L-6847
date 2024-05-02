#ifndef ACTIVITY_H
#define ACTIVITY_H

#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include "Globals.h";
#include<sstream>

using namespace std;

class Activity {
	int Type;
	string Value;
public:
	Activity();
	Activity(int, string);
	Activity(const Activity&);

	// Functions
	void PrintActivity(sf::RenderWindow&, float Offset);

	~Activity();
};

#endif