#ifndef USER_H
#define USER_H

#include "Page.h"
#include "Post.h"
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<SFML/Graphics.hpp>
#include "Globals.h"

using namespace std;

class Page;

class User {
	string UserID;
	string First_Name;
	string Last_Name;
	Page** LikedPages;
	User** FriendList;
	Post** timeline;
	string* friendIDs; 
	string* liked_PageIDs;
	int friendCount;
	int likedPgsCount;
	int PostCount;
	const int MAX_POST_LIMIT = 50;
	// For SFML
	int HomePostsCount;
	string image_path;
	int CurrentPostIndex;
	int CurrentHomeIndex;
	sf::Texture image;
	sf::Sprite image_sprite;
	sf::Font font;
	sf::Text text, defaultText, post_num_text;
public:
	User();
	User(string, string, string, string*, int, string*, int, string);

	//Getters
	string getUserID();
	string* getfriendIDs();
	string getFirstName();
	string getLastName();
	int getPost_Count();

	// Setters
	void setCurrentPostIndex();

	//Functions
	void Display_Home(sf::RenderWindow&, const sf::Event&, bool);
	void Display_FriendList(sf::RenderWindow&, User**, int);
	void Display_Friend(sf::RenderWindow&, User**, int, int, sf::Vector2f);
	void Display_ProfilePic(sf::RenderWindow&, sf::Vector2f, float);
	void SetTimeline(Post**,const int&);
	void DisplayTimeline(sf::RenderWindow&, const sf::Event&, bool);
	void Display(sf::RenderWindow&, const sf::Vector2f&);

	~User();
};

#endif