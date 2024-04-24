#include "Post.h"

// Constructor
Post::Post()
{
	UsersWhoLiked = nullptr;
	PublishedDate = nullptr;
	activity = nullptr;
	OwnerID = "";
}

Post::Post(Date* pubDate, string desc, string ownerid, string* wholiked, int noOflikes) :PublishedDate(pubDate), description(desc), OwnerID(ownerid), UsersWhoLiked(wholiked), no_of_likes(noOflikes)
{
	activity = nullptr;
}

Post::Post(Date* pubDate, string desc, Activity* act, string ownerid, string* wholiked, int noOflikes) :PublishedDate(pubDate), description(desc), activity(act), OwnerID(ownerid), UsersWhoLiked(wholiked), no_of_likes(noOflikes)
{

}

// Getters
string Post::getOwnerID()
{
	return OwnerID;
}

// Functions
void Post::Display_Post()
{
	cout << "Post Owner: " << OwnerID << endl;
	cout << "Description: " << endl;
	cout << description << endl;
	if (activity != nullptr)
	{
		activity->PrintActivity();
	}
}


// Destructor
Post::~Post()
{

}