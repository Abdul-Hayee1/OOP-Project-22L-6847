#include "Activity.h"

// Constructor
Activity::Activity() 
{
	Type = 0;
	Value = "";
}

Activity::Activity(int type, string value) : Type(type), Value(value) {}

Activity::Activity(const Activity& obj)
{
	Type = obj.Type;
	Value = obj.Value;
}



// Functions
void Activity::PrintActivity(sf::RenderWindow& window, float xOffset)
{
	sf::Font font;
	font.loadFromFile("images/Segoe UI Historic.ttf");
	sf::Text text;
	text.setCharacterSize(20);
	text.setFont(font);
	text.setFillColor(sf::Color(101, 103, 107));

	stringstream input;

	if (Type == 1)
	{
		input << "is feeling";
	}
	else if (Type == 2)
	{
		input << "is thinking about";
	}
	else if (Type == 3)
	{
		input << "is making";
	}
	else if (Type == 4)
	{
		input << "is celebrating";
	}

	input << Value << ".";

	text.setString(input.str());
	text.setPosition(xOffset, 126.f);

	window.draw(text);

}

// Destructor
Activity::~Activity() {}