#include "Post.h"

// Constructor
Post::Post()
{
	UsersWhoLiked = nullptr;
	PublishedDate = nullptr;
	activity = nullptr;
	comments = nullptr;
	no_of_likes = 0;
	CommentCount = 0;
	OwnerID = "";
}

Post::Post(string postid, Date* pubDate, string desc, string ownerid, string* wholiked, int noOflikes) :PostID(postid), PublishedDate(pubDate), description(desc), OwnerID(ownerid), UsersWhoLiked(wholiked), no_of_likes(noOflikes)
{
	comments = new Comment * [MAX_COMMENT_LIMIT];
	activity = nullptr;
	CommentCount = 0;
}

Post::Post(string postid, Date* pubDate, string desc, Activity* act, string ownerid, string* wholiked, int noOflikes) :PostID(postid), PublishedDate(pubDate), description(desc), activity(act), OwnerID(ownerid), UsersWhoLiked(wholiked), no_of_likes(noOflikes)
{
	comments = new Comment * [MAX_COMMENT_LIMIT];
	CommentCount = 0;
}

// Getters
string Post::getOwnerID()
{
	return OwnerID;
}
	
string Post::getPostID()
{
	return PostID;
}

// Functions
void Post::AddComment(string description,User* user)
{
	if (CommentCount != MAX_COMMENT_LIMIT)
	{
		comments[CommentCount++] = new Comment(description,user);
	}
	else
	{
		cout << "Max Comment Limit Reached." << endl;
	}
}

void Post::AddComment(string description, Page* page)
{
	if (CommentCount != MAX_COMMENT_LIMIT)
	{
		comments[CommentCount++] = new Comment(description, page);
	}
	else
	{
		cout << "Max Comment Limit Reached." << endl;
	}
}


void Post::Display_Post()
{
	cout << "_____________________________________________________________________" << endl;
	cout << "Post Owner: " << OwnerID << endl;
	cout << "Description: " << endl;
	cout << description << endl;
	if (activity != nullptr)
	{
		activity->PrintActivity();
	}

	cout << "\nComment Section:" << endl;

	if (CommentCount != 0)
	{
		for (int i = 0; i < CommentCount; i++)
		{
			cout << "Comment # " << i + 1 << " : " << endl;
			comments[i]->Display_Comment();
		}
	}
	else
	{
		cout << "No Commments." << endl;
	}

	cout << "________________________________________________________________________" << endl;
}


// Destructor
Post::~Post()
{

}