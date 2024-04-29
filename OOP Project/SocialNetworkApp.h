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
#include<iomanip>
#include<sstream>
#include<SFML/Graphics.hpp>
#include "Globals.h"

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
	int MaxComments;
	string Current_User;
	int Current_User_Index;
	sf::Texture bg_image1, bg_image2, white_logo, blue_logo, blue_button;
	sf::Sprite bg_sprite1, bg_sprite2, wlogo_sprite, blogo_sprite, button_sprite;
	sf::Font font;
public:
	// Constructor
	SocialNetworkApp();

	// Setters
	void SetCurrentUser_Index();

	// Functions
	void Read_UserData_FromFile();
	void Read_PageData_FromFile();
	void Read_PostData_FromFile();
	void Read_CommentData_FromFile();
	User* FindUserByID(const string&, User**, int);
	void View_Post_By_ID(const string&);
	void View_Likes_By_ID(const string&);
	void Display_CurrentUser(sf::RenderWindow&);
	void Run();

	// Destructor
	~SocialNetworkApp();
};


#endif