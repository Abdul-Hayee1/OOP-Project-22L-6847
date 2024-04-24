#ifndef SOCIALNETWORKAPP_H
#define SOCIALNETWORKAPP_H

#include "User.h"
#include "Page.h"
#include "Post.h"
#include "Date.h"
#include "Activity.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class User;
class Post;
class Page;
class Activity;
class Date;

class SocialNetworkApp {
	User **users;
	Post **posts;
	Page **pages;
	int MaxUsers;
	int MaxPages;
	int MaxPosts;
public:
	// Constructor
	SocialNetworkApp();

	// Functions
	void Read_UserData_FromFile();
	void Read_PageData_FromFile();
	void Read_PostData_FromFile();
	User* FindUserByID(const string&, User**, int);
	void Run();

	// Destructor
	~SocialNetworkApp();
};


#endif