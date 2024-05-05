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

void Date::PrintDate(sf::RenderWindow& window)
{
	font.loadFromFile("images/Segoe UI Historic.ttf");
	stringstream ss;
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color(101, 103, 107));
	text.setCharacterSize(22);
	text.setPosition(300.f, 165.f);

    ss << "Posted on : " << Day << "-" << Month << "-" << Year << endl;

	text.setString(ss.str());

	window.draw(text);

}


// Destructor
Date::~Date() {}