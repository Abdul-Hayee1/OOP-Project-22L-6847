#include "Memory.h"

// Constructors
Memory::Memory()
{
	MemoryOfPost = nullptr;
}

Memory::Memory(string Text, Post* memoryOfPost, Date* MemoryDate) : Text(Text), MemoryOfPost(memoryOfPost), MemoryDate(MemoryDate) 
{
	MemoryOfPost = nullptr;
}

// Functions
void Memory::ViewMemory(sf::RenderWindow& window)
{
	bool ShowCommentSection = false;
	/*MemoryOfPost->Display_Post(window, ShowCommentSection);*/
	cout << Text << endl;
}


// Destructors
Memory::~Memory()
{

}   