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
	timeline = nullptr;
	LikesOnPage = 0;
    PostCount = 0;
}


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