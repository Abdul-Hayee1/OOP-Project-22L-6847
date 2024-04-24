#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<string>

using namespace std;

class Date {
	int Day;
	int Month;
	int Year;
public:
	Date();
	Date(int, int, int);
	Date(const Date&);

	// Functions
	void PrintDate();

	~Date();
};

#endif
