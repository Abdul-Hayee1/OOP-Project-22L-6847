#ifndef COMMENTS_H
#define COMMENTS_H

#include "User.h"
#include "Page.h"

using namespace std;

class User;
class Page;

class Comment {
	string description;
	User* Commented_By_User;
	Page* Commented_By_Page;
public:
	Comment(string,User*);
	Comment(string, Page*);

	// Functions
	void Display_Comment();
};

#endif