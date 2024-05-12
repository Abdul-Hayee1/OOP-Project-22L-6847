#ifndef COMMENTS_H
#define COMMENTS_H

#include "User.h"
#include "Page.h"
#include<SFML/Graphics.hpp>
#include "Globals.h"

using namespace std;

class User;
class Page;

class Comment {
	string description;
	User* Commented_By_User;
	Page* Commented_By_Page;
	sf::Font font;
public:
	// Constructors
	Comment(string,User*);
	Comment(string, Page*);

	// Functions
	void Display_Comment(sf::RenderWindow&, sf::Vector2f&, sf::Vector2f&, sf::Vector2f&, sf::Vector2f&, float);

	// Destructor
	~Comment();
};

#endif