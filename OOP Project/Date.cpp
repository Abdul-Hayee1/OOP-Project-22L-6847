#include "Date.h"

// Constructor
Date::Date() 
{
	Day = 0;
	Month = 0;
	Year = 0;
}

Date::Date(int d, int m, int y) :Day(d), Month(m), Year(y)
{

}

Date::Date(const Date& obj)
{
	Day = obj.Day;
	Month = obj.Month;
	Year = obj.Year;
}

void Date::PrintDate()
{
	cout << "Date: " << Day << " " << Month << " " << Year << endl;
}


// Destructor
Date::~Date() {}