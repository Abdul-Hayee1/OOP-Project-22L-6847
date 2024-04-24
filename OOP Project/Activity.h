#ifndef ACTIVITY_H
#define ACTIVITY_H

#include<iostream>
#include<string>

using namespace std;

class Activity {
	int Type;
	string Value;
public:
	Activity();
	Activity(int, string);
	Activity(const Activity&);

	// Functions
	void PrintActivity();

	~Activity();
};

#endif