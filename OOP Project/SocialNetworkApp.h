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
	Date* CurrentDate;
	int MaxUsers;
	int MaxPages;
	int MaxPosts;
	int MaxComments;
	const int MAX_LIKES_ON_POST = 10;
	string Current_User;
	int Current_User_Index;
	sf::Texture bg_image1, bg_image2, white_logo, blue_logo, blue_button, back_button, post_bg, comment_bg, view_likes_bg, add_commentBox, logout;
	sf::Sprite bg_sprite1, bg_sprite2, wlogo_sprite, blogo_sprite, button_sprite, back_button_sprite, post_bg_sprite, comment_bg_sprite, likes_bg_sprite, add_commentBox_sprite, logout_button_sprite;
	sf::Font font, font1;
	int Choice;
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
	void Display_CurrentUser(sf::RenderWindow&);                                          // 1-
	void View_Likes_By_ID(sf::RenderWindow&, const string&);                              // 4-
	void View_Post_By_ID(sf::RenderWindow&, const string&, bool);                         // 6-
	void View_Page_By_ID(sf::RenderWindow&,const sf::Event&, const string&, bool);        // 10-
	void Display_UserMenu(sf::RenderWindow&) const;
	void Run();

	// Destructor
	~SocialNetworkApp();
};


#endif