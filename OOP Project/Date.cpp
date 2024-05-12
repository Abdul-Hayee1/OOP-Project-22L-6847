#include "Date.h"

// Constructors
Date::Date() 
{
	Day = 0;
	Month = 0;
	Year = 0;
}

Date::Date(int d, int m, int y) :Day(d), Month(m), Year(y) {}

Date::Date(const Date& obj)
{
	Day = obj.Day;
	Month = obj.Month;
	Year = obj.Year;
}


// Getters
int Date::getDay()
{
	return Day;
}

int Date::getMonth()
{
	return Month;
}

int Date::getYear()
{
	return Year;
}

// Operator Overloading
Date& Date::operator=(const Date& obj)
{
	Day = obj.Day;
	Month = obj.Month;
	Year = obj.Year;

	return *this;
}

bool Date::operator==(const Date& other) const 
{
	return (this->Day == other.Day &&
		this->Month == other.Month &&
		this->Year == other.Year);
}

void Date::PrintDate(sf::RenderWindow& window)
{
	font.loadFromFile("images/Segoe UI Historic.ttf");
	stringstream ss;
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color(101, 103, 107));
	text.setCharacterSize(22);
	text.setPosition(343.f, 162.f);

    ss << "Published : " << Day << "-" << Month << "-" << Year << endl;

	text.setString(ss.str());

	window.draw(text);

}


// Destructor
Date::~Date() {}