#ifndef MEMORY_H
#define MEMORY_H

#include "Post.h"
#include "Date.h"

using namespace std;

class Post;
class Date;

class Memory {
	string Text;
	Post* MemoryOfPost;
	Date* MemoryDate;
	sf::Font font;
public:
	Memory();
	Memory(string, Date*, Post*);

	// Functions
	void ViewMemory(sf::RenderWindow&);

	~Memory();
};

#endif