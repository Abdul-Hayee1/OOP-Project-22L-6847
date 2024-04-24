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
    timeline = nullptr;
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
                All_Users[j]->Display();
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

void User::Display()
{
    cout << "User ID: " << UserID << endl;
    cout << "User Name: " << First_Name << " " << Last_Name << endl;
 }