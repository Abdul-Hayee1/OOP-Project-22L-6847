#ifndef PAGE_H
#define PAGE_H

#include "User.h"
#include "Post.h"
#include "Date.h"
#include "Activity.h"
#include<string>
#include<SFML/Graphics.hpp>
#include "Globals.h"

using namespace std;

class User;
class Post;
class Date;
class Activity;

class Page {
	string PageID;
	string Owner_Name;
	string Title;
	Post** timeline;
	int LikesOnPage;
	int PostCount;
	const int MAX_POST_LIMIT = 50;
public:
	// Constructors
	Page();
	Page(string, string);

	// Getters
	string getPageID();
	string getTitle();

	//Functions
	void SetTimeline(Post**,const int&);

	// Destructor
};

#endif