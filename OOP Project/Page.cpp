#include "Page.h"

Page::Page()
{
	Title = "";
	timeline = nullptr;
	LikesOnPage = 0;
    PostCount = 0;
}

Page::Page(string id, string title) :PageID(id), Title(title)
{
    timeline = new Post * [MAX_POST_LIMIT];
	LikesOnPage = 0;
    PostCount = 0;
}

// Getters
string Page::getPageID()
{
    return PageID;
}

string Page::getTitle()
{
    return Title;
}

// Functions
void Page::SetTimeline(Post** AllPosts, const int& MaxPosts)
{
    for (int i = 0; i < MaxPosts; i++)
    {
        if (AllPosts[i]->getOwnerID() == PageID)
        {
            timeline[PostCount++] = AllPosts[i];
        }
    }
}