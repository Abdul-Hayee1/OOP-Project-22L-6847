#ifndef USER_H
#define USER_H

#include "Page.h"
#include "Post.h"
#include<iostream>
#include<string>

using namespace std;

class Page;

class User {
	string UserID;
	string First_Name;
	string Last_Name;
	/*Page* LikedPages;
	Page* PagesOwned;*/
	Post** timeline;
	string* friendIDs; 
	string* liked_PageIDs;
	int friendCount;
	int likedPgsCount;
	int PostCount;
public:
	User();
	User(string, string, string, string*, int, string*, int);

	//Getters
	string getUserID();
	string* getfriendIDs();

	//Functions
	void Display_FriendList(User**, int);
	void SetTimeline(Post**,const int&);
	void Display();

};

#endif