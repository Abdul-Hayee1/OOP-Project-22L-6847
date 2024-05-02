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
void User::Display_FriendList(sf::RenderWindow& window, User** All_Users, int MaxUsers)
{
    sf::Texture friend_icon, Menu_bg;
    friend_icon.loadFromFile("images/friend_icon.png");
    sf::Sprite icon_sprite, menu_bg_sprite;
    icon_sprite.setTexture(friend_icon);
    icon_sprite.setScale(0.34f, 0.34f);
    icon_sprite.setPosition(220.f, 114.f);

    Menu_bg.loadFromFile("images/3d_bg3.png");
    menu_bg_sprite.setTexture(Menu_bg);
    menu_bg_sprite.setScale(1.f, 1.12f);
    menu_bg_sprite.setPosition(175.f, 165.f);

    font.loadFromFile("images/Segoe UI Historic.ttf");
    defaultText.setString("Friends");
    defaultText.setFont(font);
    defaultText.setCharacterSize(33);
    defaultText.setFillColor(sf::Color::Black);
    defaultText.setPosition(305.f, 129.f);

    sf::Vector2f textPosition(270.f, 220.f);
    int yOffset = 50;

    stringstream displayString;

    window.draw(icon_sprite);
    window.draw(defaultText);
    window.draw(menu_bg_sprite);

    for (int i = 0; i < friendCount; i++)
    {
        for (int j = 0; j < MaxUsers; j++)
        {
            if (All_Users[j]->UserID == friendIDs[i])
            {
                Display_Friend(window, All_Users, j, i, textPosition);

                textPosition.y += yOffset;
            }
        }
    }
}

void User::Display_Friend(sf::RenderWindow& window, User** users, int index, int frCount, sf::Vector2f position)
{
    sf::Text text;
    stringstream displayString;
    font.loadFromFile("images/Segoe UI Historic.ttf");
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color(0, 100, 209));
    text.setPosition(position);

    displayString << frCount + 1 << ".  " << users[index]->getUserID() << setw(4) << right << " :  " << users[index]->getFirstName() << " " << users[index]->getLastName();
    text.setString(displayString.str());

    window.draw(text);

    sf::Texture line;
    sf::Sprite line_sprite;
    line.loadFromFile("images/friend_list_line.png");
    line_sprite.setTexture(line);
    /*line_sprite.setScale(1.34f,0.8f);*/

    line_sprite.setPosition(position);

    window.draw(line_sprite);
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
    ss << "User ID:  " << setw(15) << left << UserID << setw(8) << "Name:  " << First_Name << " " << Last_Name;
    string userInfo = ss.str();

    text.setString(userInfo);

    text.setPosition(position);

    window.draw(text);
 }