#ifndef MEMORY_H
#define MEMORY_H

#include "Post.h"

using namespace std;

class Post;

class Memory {
	string Text;
	Post* MemoryOfPost;
	Date* MemoryDate;
public:
	Memory();
	Memory(string, Post*, Date*);

	// Functions
	void ViewMemory(sf::RenderWindow&);

	~Memory();
};

#endif