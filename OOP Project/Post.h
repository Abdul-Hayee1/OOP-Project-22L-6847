#ifndef POST_H	
#define POST_H

#include "User.h"
#include "Page.h"
#include "Date.h"
#include "Activity.h"
#include "Comments.h"
#include<iostream>
#include<string>

using namespace std;

class Date;
class User;
class Page;
class Activity;
class Comment;

class Post {
	string PostID;
	string description;
	int no_of_likes;
	string* UsersWhoLiked;
	Date *PublishedDate;
	Activity *activity;
	string OwnerID;
	Comment** comments;
	int CommentCount;
	const int MAX_COMMENT_LIMIT = 10;
	const int MAX_LIKE_LIMIT = 10;
public:
	// Constructor
	Post();
	Post(string, Date*, string, string, string*, int);
	Post(string, Date*, string, Activity*, string, string*, int);

	// Getters
	string getOwnerID();
	string getPostID();

	// Functions
	void AddComment(string,User*);
	void AddComment(string, Page*);
	void Display_Post();

	// Destructor
	~Post();
};

#endif