#include "Page.h"

Page::Page()
{
	Title = "";
	timeline = nullptr;
	LikesOnPage = 0;
    PostCount = 0;
    CurrentPostIndex = 0;
}

Page::Page(string id, string title) :PageID(id), Title(title)
{
    timeline = new Post * [MAX_POST_LIMIT];
	LikesOnPage = 0;
    PostCount = 0;
    CurrentPostIndex = 0;
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

int Page::getPost_Count()
{
    return PostCount;
}

Post* Page::getTimeline(int index)
{
    return timeline[index];
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

void Page::DisplayTimeline(sf::RenderWindow& window, const sf::Event& event, bool ShowCommentSection)
{
    font.loadFromFile("images/Segoe UI Historic.ttf");
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

// Destructors