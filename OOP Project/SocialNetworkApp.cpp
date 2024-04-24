#include "SocialNetworkApp.h"

// Constructor
SocialNetworkApp::SocialNetworkApp()
{
    users = nullptr;
    posts = nullptr;
    pages = nullptr;
    MaxUsers = 0;
    MaxPages = 0;
    MaxPosts = 0;
}

//SocialNetworkApp::SocialNetworkApp(int _maxUsers, int _maxPages): MaxUsers(_maxUsers), MaxPages(_maxPages), UserCount(0), PageCount(0) 
//{
//    users = new User * [MaxUsers];
//    pages = new Post * *[MaxPages];
//}


// Functions
User* SocialNetworkApp::FindUserByID(const string& userId, User** All_Users, int MaxUsers)
{
    for (int i = 0; i < MaxUsers; i++)
    {
        if (All_Users[i]->getUserID() == userId)
        {
            return All_Users[i];
        }
    }
    return nullptr;
}

void SocialNetworkApp::Read_UserData_FromFile()
{
    ifstream UserFile("Users.txt");

    UserFile >> MaxUsers;
    users = new User * [MaxUsers];

    for (int i = 0; i < MaxUsers; i++)
    {
        string userId, First_name, Last_name, * friendId, * likedPgsID;
        
        friendId = new string[MaxUsers];

        UserFile >> userId >> First_name >> Last_name;

        string fdId;
        int friendCount = 0;
        while (UserFile >> fdId && fdId != "-1")
        {
            friendId[friendCount++] = fdId;
        }

        likedPgsID = new string[20];

        string pgID;
        int likedPgsCount = 0;
        while (UserFile >> pgID && pgID != "-1")
        {
            likedPgsID[likedPgsCount++] = pgID;
        }

        User* newUser = new User(userId, First_name, Last_name, friendId, friendCount, likedPgsID, likedPgsCount);

        users[i] = newUser;
    }

    UserFile.close();
}

void SocialNetworkApp::Read_PageData_FromFile()
{
    ifstream PageFile("Pages.txt");

    PageFile >> MaxPages;
    pages = new Page * [MaxPages];

    for (int i = 0; i < MaxPages; i++)
    {
        string pageId, pageTitle;
        PageFile >> pageId >> pageTitle;

        pages[i] = new Page(pageId, pageTitle);
    }
}

void SocialNetworkApp::Read_PostData_FromFile()
{
    ifstream PostFile("Posts.txt");

    PostFile >> MaxPosts;
    PostFile.ignore();
    posts = new Post * [MaxPosts];

    for (int i = 0; i < MaxPosts; i++)
    {
        int num;
        PostFile >> num;
        string line;
        PostFile >> line;
        PostFile.ignore();

        int day, month, year;
        PostFile >> day >> month >> year;
        PostFile.ignore();

        Date* temp = new Date(day, month, year);

        string description;

        getline(PostFile, description);

        if (num == 2)
        {
            int type;
            string value;
            PostFile >> type;
            getline(PostFile, value);
            Activity* TempAct = new Activity(type, value);

            string ownerId;
            PostFile >> ownerId;
            PostFile.ignore();

            int noOflikes = 0;
            string likedID;
            string* IDsWhoLiked = new string[MaxPages + MaxUsers];
            while (PostFile >> likedID && likedID != "-1")
            {
                IDsWhoLiked[noOflikes++] = likedID;
            }
            PostFile.ignore();

            posts[i] = new Post(temp, description, TempAct, ownerId, IDsWhoLiked, noOflikes);
        }
        else if (num == 1)
        {
            string ownerId;
            PostFile >> ownerId;
            PostFile.ignore();

            int noOflikes = 0;
            string likedID;
            string* IDsWhoLiked = new string[MaxPages + MaxUsers];
            while (PostFile >> likedID && likedID != "-1")
            {
                IDsWhoLiked[noOflikes++] = likedID;
            }
            PostFile.ignore();

            posts[i] = new Post(temp, description, ownerId, IDsWhoLiked, noOflikes);
        }

    }
}



void SocialNetworkApp::Run()
{
    Read_UserData_FromFile();
    Read_PageData_FromFile();
    Read_PostData_FromFile();

    for (int i = 0; i < MaxUsers; i++)
    {
        users[i]->Display();
    }

    cout << "MaxPosts: " << MaxPosts << endl;
    for (int i = 0; i < MaxPosts; i++)
    {
        cout << "\nDisplaying post #" << i + 1 << endl;
       
        posts[i]->Display_Post();
    }

    // Setting Timelines
    for (int i = 0; i < MaxUsers; i++)
    {
        users[i]->SetTimeline(posts, MaxPosts);
    }
    for (int i = 0; i < MaxPages; i++)
    {
        pages[i]->SetTimeline(posts, MaxPosts);
    }

    /*users[1]->Display_FriendList(users, MaxUsers);*/
}

// Destructor
SocialNetworkApp::~SocialNetworkApp() 
{
    for (int i = 0; i < MaxUsers; i++)
    {
        delete users[i];
    }
    delete []users;

    for (int i = 0; i < MaxPages; i++)
    {
        delete pages[i];
    }
    delete []pages;

    for (int i = 0; i < MaxPosts; i++)
    {
        delete posts[i];
    }
    delete []posts;
}