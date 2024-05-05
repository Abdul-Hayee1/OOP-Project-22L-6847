#include "Post.h"

// Constructor
Post::Post()
{
	UsersWhoLiked = nullptr;
	PublishedDate = nullptr;
	activity = nullptr;
	comments = nullptr;
	no_of_likes = 0;
	CommentCount = 0;
	OwnerID = "";
    POwner = nullptr;
    UOwner = nullptr;
}

Post::Post(string postid, Date* pubDate, string desc, string ownerid, string* wholiked, int noOflikes) :PostID(postid), PublishedDate(pubDate), description(desc), OwnerID(ownerid), UsersWhoLiked(wholiked), no_of_likes(noOflikes)
{
	comments = new Comment * [MAX_COMMENT_LIMIT];
	activity = nullptr;
	CommentCount = 0;
    POwner = nullptr;
    UOwner = nullptr;
}

Post::Post(string postid, Date* pubDate, string desc, Activity* act, string ownerid, string* wholiked, int noOflikes) :PostID(postid), PublishedDate(pubDate), description(desc), activity(act), OwnerID(ownerid), UsersWhoLiked(wholiked), no_of_likes(noOflikes)
{
	comments = new Comment * [MAX_COMMENT_LIMIT];
	CommentCount = 0;
    POwner = nullptr;
    UOwner = nullptr;
}

// Getters
string Post::getOwnerID()
{
	return OwnerID;
}

string Post::getPostID()
{
	return PostID;
}

int Post::getNo_Of_Likes()
{
	return no_of_likes;
}

string Post::getLikedByID(int index)
{
	return UsersWhoLiked[index];
}


// Functions
void Post::AddComment(string description, User* user)
{
	if (CommentCount != MAX_COMMENT_LIMIT)
	{
		comments[CommentCount++] = new Comment(description, user);
	}
	else
	{
		cout << "Max Comment Limit Reached." << endl;
	}
}

void Post::AddComment(string description, Page* page)
{
	if (CommentCount != MAX_COMMENT_LIMIT)
	{
		comments[CommentCount++] = new Comment(description, page);
	}
	else
	{
		cout << "Max Comment Limit Reached." << endl;
	}
}

void Post::AssigningOwner(User** users,Page** pages, const int MaxUsers,const int MaxPages)
{
    bool found = false;

    for (int i = 0; i < MaxUsers; i++)
    {
        if (users[i]->getUserID() == OwnerID)
        {
            UOwner = users[i];
            POwner = nullptr;
            found = true;
            break;
        }
    }
    if (!found)
    {
        for (int i = 0; i < MaxPages; i++)
        {
            if (pages[i]->getPageID() == OwnerID)
            {
                POwner = pages[i];
                UOwner = nullptr;
                break;
            }
        }
    }
}

void Post::Display_Post(sf::RenderWindow& window, bool ShowCommentSection)
{
    sf::Text Post_desc, Owner_desc, commnt_count;
    font.loadFromFile("images/Segoe UI Historic.ttf");
    Post_desc.setFont(font);
    Post_desc.setFillColor(sf::Color::Black);
    Post_desc.setCharacterSize(34);
    Post_desc.setPosition(340.f, 250.f);
    Post_desc.Bold;
    Owner_desc.setFont(font);
    Owner_desc.setFillColor(sf::Color(5, 5, 5));
    Owner_desc.setCharacterSize(21);
    Owner_desc.setPosition(300.f, 122.f);
    commnt_count.setString(to_string(CommentCount));
    commnt_count.setCharacterSize(20);
    commnt_count.setPosition(836.f, 598.f);
    commnt_count.setFillColor(sf::Color(101, 103, 107));
    commnt_count.setFont(font);

    float maxWidth = 610.f;
    float lineHeight = 44;

    sf::Text tempText(Post_desc);

    if (ShowCommentSection == false)
    {
        // Function for word wrapping
        auto wrapText = [&](const string& str)
            {
                stringstream ss(str);
                string word;
                string line;
                float x = Post_desc.getPosition().x;
                float y = Post_desc.getPosition().y;

                while (ss >> word)
                {
                    sf::FloatRect textRect = tempText.getLocalBounds();
                    if (textRect.width + tempText.getCharacterSize() * word.size() > maxWidth)
                    {
                        tempText.setString(line);
                        tempText.setPosition(x, y);
                        window.draw(tempText);

                        // Move to the next line
                        line = word + " ";
                        tempText.setString(line);
                        y += lineHeight;
                    }
                    else
                    {
                        line += word + " ";
                        tempText.setString(line);
                    }
                }
                tempText.setString(line);
                tempText.setPosition(x, y);  // Update position
                window.draw(tempText);
            };

        window.draw(commnt_count);

        stringstream ownerStr;

        if (UOwner != nullptr)
        {
            ownerStr << UOwner->getUserID() << " : " << UOwner->getFirstName() << " " << UOwner->getLastName();
        }
        else if (POwner != nullptr)
        {
            ownerStr << POwner->getPageID() << " : " << POwner->getTitle();
        }

        Owner_desc.setString(ownerStr.str());
        float xOffset = Owner_desc.getGlobalBounds().width + 307.f;

        window.draw(Owner_desc);

        if (activity != nullptr)
        {
            activity->PrintActivity(window, xOffset);
        }
        string desc1 = "\"" + description + "\"";
        wrapText(desc1);

        PublishedDate->PrintDate(window);
    }

    if (ShowCommentSection == true)
    {
        if (CommentCount != 0)
        {
            for (int i = 0; i < CommentCount; i++)
            {
                comments[i]->Display_Comment(window);
            }
        }
        else
        {
            cout << "No Comments." << endl;
        }
    }
}



// Destructor
Post::~Post()
{

}