#include "User.h"

User::User()
{
    UserID = "";
    First_Name = "";
    Last_Name = "";
    friendIDs = nullptr;
    liked_PageIDs = nullptr;
    timeline = nullptr;
    FriendList = nullptr;
    LikedPages = nullptr;
    friendCount = 0;
    likedPgsCount = 0;
    PostCount = 0;
    CurrentPostIndex = 0;
    CurrentHomeIndex = 0;
    HomePostsCount = 0;
}

User::User(string userid, string fn, string ln, string* friendIds, int fdcount, string* likedpgids, int likedPgCount, string img_path) : UserID(userid), First_Name(fn), Last_Name(ln), friendIDs(friendIds), friendCount(fdcount), liked_PageIDs(likedpgids), likedPgsCount(likedPgCount), image_path(img_path)
{
    timeline = new Post * [MAX_POST_LIMIT];
    FriendList = new User * [friendCount];
    LikedPages = new Page * [likedPgsCount];
    PostCount = 0;
    image.loadFromFile(image_path);
    image_sprite.setTexture(image);
    CurrentPostIndex = 0;
    CurrentHomeIndex = 1;
    HomePostsCount = 0;
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

int User::getPost_Count()
{
    return PostCount;
}

// Setters
void User::setCurrentPostIndex()
{
    CurrentPostIndex = 0;
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
    int yOffset = 60;

    stringstream displayString;

    window.draw(icon_sprite);
    window.draw(defaultText);
    window.draw(menu_bg_sprite);

    sf::Texture line;
    sf::Sprite line_sprite;
    line.loadFromFile("images/friend_list_line.png");
    line_sprite.setTexture(line);
    line_sprite.setScale(1.5f, 0.7f);

    for (int i = 0; i < friendCount; i++)
    {
        for (int j = 0; j < MaxUsers; j++)
        { 
            if (All_Users[j]->UserID == friendIDs[i])
            {
                Display_Friend(window, All_Users, j, i, textPosition);

                line_sprite.setPosition(textPosition.x - 15, textPosition.y + 33);
                window.draw(line_sprite);
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
}

void User::Display_ProfilePic(sf::RenderWindow& window, sf::Vector2f position, float scaleFactor)
{
    image_sprite.setPosition(position);
    image_sprite.setScale(scaleFactor, scaleFactor);
    window.draw(image_sprite);
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

void User::DisplayTimeline(sf::RenderWindow& window, const sf::Event& event, bool ShowCommentSection)
{
    post_num_text.setFont(font);
    post_num_text.setFillColor(sf::Color(101, 103, 107));
    post_num_text.setPosition(1000.f, 550.f);
    post_num_text.setCharacterSize(28);
    stringstream ss;

    if (ShowCommentSection == false)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Right)
            {
                if (CurrentPostIndex < PostCount - 1)
                    CurrentPostIndex++;
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                if (CurrentPostIndex > 0)
                    CurrentPostIndex--;
            }
        }
    }
        ss << CurrentPostIndex + 1 << " of " << PostCount;
        post_num_text.setString(ss.str());

        window.draw(post_num_text);
        timeline[CurrentPostIndex]->Display_Post(window, ShowCommentSection);
}

void User::Display_Home(sf::RenderWindow& window, const sf::Event& event, bool ShowCommentSection)
{
    post_num_text.setFont(font);
    post_num_text.setFillColor(sf::Color(101, 103, 107));
    post_num_text.setPosition(1000.f, 550.f);
    post_num_text.setCharacterSize(28);
    stringstream ss;

    if (ShowCommentSection == false)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Right)
            {
                if (CurrentHomeIndex < HomePostsCount - 1)
                    CurrentHomeIndex++;
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                if (CurrentHomeIndex > 0)
                    CurrentHomeIndex--;
            }
        }
    }

    for (int i = 0; i < friendCount; i++)
    {
        /*FriendList[i]->DisplayTimeline();*/
    }

    ss << CurrentHomeIndex << " of " << HomePostsCount;
    post_num_text.setString(ss.str());
    window.draw(post_num_text);

}

// Destructor
User::~User()
{
    delete[] timeline;
}