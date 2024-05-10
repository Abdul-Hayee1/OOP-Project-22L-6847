#include "Comments.h"

// Constructors
Comment::Comment(string desc, User* user) :description(desc), Commented_By_User(user)
{
	Commented_By_Page = nullptr;
}

Comment::Comment(string desc, Page* page) :description(desc), Commented_By_Page(page)
{
	Commented_By_User = nullptr;
}

// Functions
void Comment::Display_Comment(sf::RenderWindow& window, sf::Vector2f& box_position, sf::Vector2f& comment_position, sf::Vector2f& profile_position, sf::Vector2f& commentor_position, float smallfactor)
{
    sf::Texture comment_box;
    sf::Sprite comment_box_sprite;
    comment_box.loadFromFile("images/comment box.png");
    comment_box_sprite.setTexture(comment_box);
    comment_box_sprite.setPosition(box_position);
    comment_box_sprite.setScale(1.f, 1.2f);

    font.loadFromFile("images/Segoe UI Historic.ttf");
    stringstream commentedBy;
    sf::Text commentor_text, comment_desc;
    commentor_text.setFont(font);
    commentor_text.setFillColor(sf::Color(5, 5, 5));
    commentor_text.setCharacterSize(24);
    commentor_text.setPosition(commentor_position);

    comment_desc.setFont(font);
    comment_desc.setFillColor(sf::Color(101, 103, 107));
    comment_desc.setCharacterSize(26);
    comment_desc.setPosition(comment_position);


    if (Commented_By_Page == nullptr)
    {
        Commented_By_User->Display_ProfilePic(window, profile_position, smallfactor);
        commentedBy << Commented_By_User->getUserID() << " : " << Commented_By_User->getFirstName() << " " << Commented_By_User->getLastName() << endl;
    }
    else if (Commented_By_User == nullptr)
    {
        commentedBy << Commented_By_Page->getPageID() << " : " << Commented_By_Page->getTitle() << endl;
    }

    commentor_text.setString(commentedBy.str());
    window.draw(comment_box_sprite);
    window.draw(commentor_text);

    float maxWidth = 610.f;
    float lineHeight = 44;

    sf::Text tempText(comment_desc);

    auto wrapText = [&](const string& str)
        {
            stringstream ss(str);
            string word;
            string line;
            float x = comment_desc.getPosition().x;
            float y = comment_desc.getPosition().y;

            while (ss >> word)
            {
                sf::FloatRect textRect = tempText.getLocalBounds();
                if (textRect.width + tempText.getCharacterSize() * word.size() > maxWidth)
                {
                    y += lineHeight;
                    // Draw the current line
                    tempText.setString(line);
                    tempText.setPosition(x, y); // Update position
                    window.draw(tempText);

                    // Move to the next line
                    line = word + " ";
                    tempText.setString(line);
                    y += 20;
                }
                else
                {
                    line += word + " ";
                    tempText.setString(line);
                }
            }
            // Draw the last line
            tempText.setString(line);
            tempText.setPosition(x, y); // Update position
            window.draw(tempText);
        };

    wrapText(description);
}