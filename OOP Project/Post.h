#ifndef POST_H	
#define POST_H

#include "User.h"
#include "Date.h"
#include "Activity.h"
#include<iostream>
#include<string>

using namespace std;

class Date;
class User;
class Activity;

class Post {
	string description;
	int no_of_likes;
	string* UsersWhoLiked;
	Date *PublishedDate;
	Activity *activity;
	string OwnerID;
	const int MAX_COMMENT_LIMIT = 10;
public:
	// Constructor
	Post();
	Post(Date*, string, string, string*, int);
	Post(Date*, string, Activity*, string, string*, int);

	// Getters
	string getOwnerID();

	// Functions
	void Display_Post();

	// Destructor
	~Post();
};

#endif