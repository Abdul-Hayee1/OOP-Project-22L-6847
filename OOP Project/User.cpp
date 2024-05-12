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
    memories = nullptr;
    friendCount = 0;
    likedPgsCount = 0;
    PostCount = 0;
    MemoryCount = 0;
    CurrentPostIndex = 0;
    CurrentHomeIndex = 0;
    HomePostsCount = 0;
    Home = nullptr;
}

User::User(string userid, string fn, string ln, string* friendIds, int fdcount, string* likedpgids, int likedPgCount, string img_path) : UserID(userid), First_Name(fn), Last_Name(ln), friendIDs(friendIds), friendCount(fdcount), liked_PageIDs(likedpgids), likedPgsCount(likedPgCount), image_path(img_path)
{
    timeline = new Post * [MAX_POST_LIMIT];
    FriendList = new User * [friendCount];
    LikedPages = new Page * [likedPgsCount];
    PostCount = 0;
    MemoryCount = 0;
    image.loadFromFile(image_path);
    image_sprite.setTexture(image);
    CurrentPostIndex = 0;
    CurrentHomeIndex = 0;
    HomePostsCount = 0;
    Home = new Post * [MAX_POST_LIMIT];
    memories = nullptr;
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

Post* User::getTimeline(int index)
{
    return timeline[index];
}

int User::getHomePostsCount()
{
    return HomePostsCount;
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

    memories = new Memory * [PostCount];
}

void User::DisplayTimeline_PostIDs(sf::RenderWindow& window)
{
    font.loadFromFile("images/Segoe UI Historic.ttf");
    stringstream ss;

    ss << "Timeline Posts:\n";
    for (int i = 0; i < PostCount; i++)
    {
        ss << timeline[i]->getPostID();
        ss << "\n";
    }

    sf::Text text(ss.str(), font, 26);
    text.setFillColor(sf::Color::Black);
    text.setPosition(540.f, 420.f);

    window.draw(text);
}

void User::SetFriends_and_Pages(User** users, Page** pages, const int& MaxUsers, const int& MaxPages)
{
    for (int i = 0; i < friendCount; i++)
    {
        for (int j = 0; j < MaxUsers; j++)
        {
            if (friendIDs[i] == users[j]->getUserID())
            {
                FriendList[i] = users[j];
                break;
            }
        }
    }

    for (int i = 0; i < likedPgsCount; i++)
    {
        for (int j = 0; j < MaxPages; j++)
        {
            if (liked_PageIDs[i] == pages[j]->getPageID())
            {
                LikedPages[i] = pages[j];
                break;
            }
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
    font.loadFromFile("images/Segoe UI Historic.ttf");
    post_num_text.setFont(font);
    post_num_text.setFillColor(sf::Color(101, 103, 107));
    post_num_text.setPosition(1000.f, 550.f);
    post_num_text.setCharacterSize(28);
    stringstream ss;

    int totalItemCount = MemoryCount + PostCount;

    bool isMemory = (CurrentPostIndex < MemoryCount);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Right)
        {
            if (CurrentPostIndex < totalItemCount - 1)
            {
                CurrentPostIndex++;
            }
          
            if (CurrentPostIndex >= MemoryCount && CurrentPostIndex < totalItemCount)
            {
                isMemory = false;
            }
        }
        else if (event.key.code == sf::Keyboard::Left)
        {
            if (CurrentPostIndex > 0)
            {
                CurrentPostIndex--;
            }

            if (CurrentPostIndex < MemoryCount)
            {
                isMemory = true;
            }
        }
    }

    ss << CurrentPostIndex + 1 << " of " << totalItemCount;
    post_num_text.setString(ss.str());

    if (isMemory == true)
    {
        if (memories != nullptr)
        {
            memories[CurrentPostIndex]->ViewMemory(window);
        }
    }
    else if(isMemory == false)
    {
        int postIndex = CurrentPostIndex - MemoryCount;
        timeline[postIndex]->Display_Post(window, ShowCommentSection);
    }

    window.draw(post_num_text);
}

void User::addMemory(string Text, Date* MemoryDate, string postID)
{
    bool found = false;
    for (int i = 0; i < PostCount; i++)
    {
        if (timeline[i]->getPostID() == postID)
        {
            memories[MemoryCount++] = new Memory(Text, MemoryDate, timeline[i]);

            found = true;
            break;
        }
    }
}

void User::SetHome(Date* CurrentDate)
{
    for (int i = 0; i < friendCount; i++)
    {
        for (int j = 0; j < FriendList[i]->getPost_Count(); j++)
        {
            Date* postDate = FriendList[i]->getTimeline(j)->getPublishedDate();

            if ((*postDate == *CurrentDate) || (postDate->getDay() == CurrentDate->getDay() - 1 &&
                postDate->getMonth() == CurrentDate->getMonth() &&
                postDate->getYear() == CurrentDate->getYear()))
            {
                Home[HomePostsCount++] = FriendList[i]->getTimeline(j);
            }
        }
    }

    for (int i = 0; i < likedPgsCount; i++)
    {
        for (int j = 0; j < LikedPages[i]->getPost_Count(); j++)
        {
            Date* postDate = LikedPages[i]->getTimeline(j)->getPublishedDate();

            if ((*postDate == *CurrentDate) || (postDate->getDay() == CurrentDate->getDay() - 1 &&
                postDate->getMonth() == CurrentDate->getMonth() &&
                postDate->getYear() == CurrentDate->getYear()))
            {
                Home[HomePostsCount++] = LikedPages[i]->getTimeline(j);
            }
        }
    }
}



void User::Display_Home(sf::RenderWindow& window, const sf::Event& event, bool ShowCommentSection)
{
    font.loadFromFile("images/Segoe UI Historic.ttf");

    sf::Text defaultText("No New Posts.", font, 35);
    defaultText.setFillColor(sf::Color(101, 103, 107));
    defaultText.setPosition(530.f, 330.f);
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

        window.draw(post_num_text);
    }

    if (HomePostsCount != 0)
    {
        Home[CurrentHomeIndex]->Display_Post(window, ShowCommentSection);
    }
    else if (HomePostsCount == 0)
    {
        window.draw(defaultText);
    }

    ss << CurrentHomeIndex + 1 << " of " << HomePostsCount;
    post_num_text.setString(ss.str());
}

// Destructor
User::~User()
{
    if (memories != nullptr) 
    {
        for (int i = 0; i < MemoryCount; i++)
        {
            delete memories[i];
        }
        delete[] memories;
    }

    if (timeline != nullptr) 
    {
        for (int i = 0; i < PostCount; i++) 
        {
            delete timeline[i];
        }
        delete[] timeline;
    }

    if (Home != nullptr) 
    {
        for (int i = 0; i < HomePostsCount; i++) 
        {
            delete Home[i];
        }
        delete[] Home;
    }

    delete[] FriendList;
    delete[] LikedPages;
    delete[] friendIDs;
    delete[] liked_PageIDs;
}
