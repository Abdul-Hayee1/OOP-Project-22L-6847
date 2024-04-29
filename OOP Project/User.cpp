#include "User.h"

User::User()
{
    UserID = "";
    First_Name = "";
    Last_Name = "";
    friendIDs = nullptr;
    liked_PageIDs = nullptr;
    timeline = nullptr;
    friendCount = 0;
    likedPgsCount = 0;
    PostCount = 0;
}

User::User(string userid, string fn, string ln, string* friendIds, int fdcount, string* likedpgids, int likedPgCount) : UserID(userid), First_Name(fn), Last_Name(ln), friendIDs(friendIds), friendCount(fdcount), liked_PageIDs(likedpgids), likedPgsCount(likedPgCount)
{
    timeline = new Post * [MAX_POST_LIMIT];
    PostCount = 0;
}

//Getters
string User::getUserID()
{
    return UserID;
}

string* User::getfriendIDs()
{
    return friendIDs;
}

string User::getFirstName()
{
    return First_Name;
}

string User::getLastName()
{
    return Last_Name;
}

//Functions
void User::Display_FriendList(User** All_Users, int MaxUsers)
{
    cout << "Friend List:" << endl;
    for (int i = 0; i < friendCount; i++)
    {
        for (int j = 0; j < MaxUsers; j++)
        {
            if (All_Users[j]->UserID == friendIDs[i])
            {
                cout << "\nFriend # " << i + 1 << endl;
                /*All_Users[j]->Display(window);*/
            }
        }
    }
}

void User::SetTimeline(Post** AllPosts, const int& MaxPosts)
{
    for (int i = 0; i < MaxPosts; i++)
    {
        if (AllPosts[i]->getOwnerID() == UserID)
        {
            timeline[PostCount++] = AllPosts[i];
        }
    }
}

void User::Display(sf::RenderWindow& window, const sf::Vector2f& position)
{
    font.loadFromFile("images/Arial.ttf");
    text.setFont(font);
    text.setCharacterSize(22);
    text.setFillColor(sf::Color::White);

    stringstream ss;
    ss << "User ID: " << UserID << " " << "     Name: " << First_Name << " " << Last_Name;
    string userInfo = ss.str();

    text.setString(userInfo);

    text.setPosition(position);

    window.draw(text);
 }