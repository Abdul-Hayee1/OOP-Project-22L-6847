#include "Memory.h"

// Constructors
Memory::Memory()
{
	MemoryOfPost = nullptr;
	MemoryDate = nullptr;
}

Memory::Memory(string text, Date* memoryDate, Post* MemoryOfPost)
{
    Text = text;
    MemoryDate = memoryDate;
    this->MemoryOfPost = MemoryOfPost;
}

// Functions
void Memory::ViewMemory(sf::RenderWindow& window)
{
	font.loadFromFile("images/Segoe UI Historic.ttf");
	bool ShowCommentSection = false;

	stringstream ss;
	ss << "Shared a memory at: " << MemoryDate->getDay() << "-" << MemoryDate->getMonth() << "-" << MemoryDate->getYear() << "\n" << "\"" << Text << "\"";
	sf::Text text(ss.str(), font, 24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(270.f, 5.f);

	window.draw(text);

    MemoryOfPost->Display_Post(window,ShowCommentSection);
}


// Destructors
Memory::~Memory()
{
	delete MemoryDate;
}