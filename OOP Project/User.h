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
	/*Page* LikedPages;
	Page* PagesOwned;*/
	Post** timeline;
	string* friendIDs; 
	string* liked_PageIDs;
	int friendCount;
	int likedPgsCount;
	int PostCount;
	const int MAX_POST_LIMIT = 50;
	/*sf::Text idText, FName_Text, LName_Text;*/
	sf::Font font;
	sf::Text text;
public:
	User();
	User(string, string, string, string*, int, string*, int);

	//Getters
	string getUserID();
	string* getfriendIDs();
	string getFirstName();
	string getLastName();

	//Functions
	void Display_FriendList(User**, int);
	void SetTimeline(Post**,const int&);
	void Display(sf::RenderWindow&, const sf::Vector2f&);

};

#endif