#ifndef PAGE_H
#define PAGE_H

#include "User.h"
#include "Post.h"
#include "Date.h"
#include "Activity.h"
#include<string>

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
public:
	// Constructors
	Page();
	Page(string, string);

	//Functions
	void SetTimeline(Post**,const int&);

	// Destructor
};

#endif