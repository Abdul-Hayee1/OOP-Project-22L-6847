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
void Comment::Display_Comment(sf::RenderWindow& window)
{
	font.loadFromFile("images/Segoe UI Historic.ttf");
	stringstream commentedBy;
	sf::Text commentor_text, comment_desc;
	commentor_text.setFont(font);
	commentor_text.setFillColor(sf::Color::Black);
	commentor_text.setCharacterSize(26);
	commentor_text.setPosition(300.f, 400.f);

    comment_desc.setFont(font);
    comment_desc.setFillColor(sf::Color::Black);
    comment_desc.setCharacterSize(26);
    comment_desc.setPosition(300.f, 200.f);


	if (Commented_By_Page == nullptr)
	{
		 commentedBy << "Commented By: " << Commented_By_User->getFirstName() << " " << Commented_By_User->getLastName() << endl;
	}
	else if (Commented_By_User == nullptr)
	{
		commentedBy << "Commented By: " << Commented_By_Page->getTitle() << endl;
	}

    commentor_text.setString(commentedBy.str());
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
