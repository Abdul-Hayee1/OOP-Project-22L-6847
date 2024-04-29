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
	MaxComments = 0;
	Current_User_Index = -1;
}

// Reading Data Functions

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
		string postID;
		PostFile >> postID;
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

			posts[i] = new Post(postID, temp, description, TempAct, ownerId, IDsWhoLiked, noOflikes);
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

			posts[i] = new Post(postID, temp, description, ownerId, IDsWhoLiked, noOflikes);
		}

	}
}

void SocialNetworkApp::Read_CommentData_FromFile()
{
	ifstream CommentFile("Comments.txt");

	CommentFile >> MaxComments;

	for (int i = 0; i < MaxComments; i++)
	{
		string word;
		CommentFile >> word;

		string postID;
		CommentFile >> postID;

		string CommentorID;
		CommentFile >> CommentorID;

		string description;
		getline(CommentFile, description);

		int postIndex;
		for (int i = 0; i < MaxPosts; i++)
		{
			if (posts[i]->getPostID() == postID)
			{
				postIndex = i;
				break;
			}
		}

		bool found = false;
		for (int i = 0; i < MaxUsers; i++)
		{
			if (users[i]->getUserID() == CommentorID)
			{
				posts[postIndex]->AddComment(description, users[i]);
				found = true;
				break;
			}
		}
		if (found == false)
		{
			for (int i = 0; i < MaxPages; i++)
			{
				if (pages[i]->getPageID() == CommentorID)
				{
					posts[postIndex]->AddComment(description, pages[i]);
					break;
				}
			}
		}

		CommentFile.ignore();
	}
}

// Main Functions
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

void SocialNetworkApp::View_Post_By_ID(const string& postID)
{
	bool found = false;
	for (int i = 0; i < MaxPosts; i++)
	{
		if (posts[i]->getPostID() == postID)
		{
			posts[i]->Display_Post();
			found = true;
			break;
		}
	}

	if (found == false)
	{
		cout << "Post not Found." << endl;
	}
}

void SocialNetworkApp::View_Likes_By_ID(const string& postID)
{
	cout << "Liked By:" << endl;
	for (int i = 0; i < MaxPosts; i++)
	{
		if (posts[i]->getPostID() == postID)
		{
			for (int j = 0; j < posts[i]->getNo_Of_Likes(); j++)
			{
				bool found = false;
				for (int k = 0; k < MaxUsers; k++)
				{
					if (posts[i]->getLikedByID(j) == users[k]->getUserID())
					{
						cout << users[k]->getUserID() << " : " << users[k]->getFirstName() << " " << users[k]->getLastName() << endl;
						found == true;
						break;
					}
				}

				if (found == false)
				{
					for (int k = 0; k < MaxPages; k++)
					{
						if (posts[i]->getLikedByID(j) == pages[k]->getPageID())
						{
							cout << pages[k]->getPageID() << " : " << pages[k]->getTitle() << endl;
							break;
						}
					}
				}
			}
		}
	}
}

void SocialNetworkApp::SetCurrentUser_Index()
{
	for (int i = 0; i < MaxUsers; i++)
	{
		if (users[i]->getUserID() == Current_User)
		{
			Current_User_Index = i;
			break;
		}
	}
}

void SocialNetworkApp::Display_CurrentUser(sf::RenderWindow& window)
{
	sf::Text defaultText;
	defaultText.setFont(font);
	defaultText.setCharacterSize(26);
	defaultText.setFillColor(sf::Color::Black);
	defaultText.setPosition(800.f, 36.f);

	stringstream ss;
	ss << "Logged in as :   " << users[Current_User_Index]->getUserID() << " :  " << users[Current_User_Index]->getFirstName() << " " << users[Current_User_Index]->getLastName();
	string text = ss.str();

	defaultText.setString(text);

	window.draw(defaultText);
}

void SocialNetworkApp::Run()
{
	Read_UserData_FromFile();
	Read_PageData_FromFile();
	Read_PostData_FromFile();
	Read_CommentData_FromFile();

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

	//User Interface
	/*cout << "1- Set Current User" << endl;
	cout << "2- View Home of Current User" << endl;
	cout << "3- Like a Post" << endl;
	cout << "4- View the list of People who liked a Post" << endl;
	cout << "5- Comment on a Post" << endl;
	cout << "6- View a Post" << endl;
	cout << "7- Share a Memory" << endl;
	cout << "8- View User's Timeline" << endl;
	cout << "9- View Friend List" << endl;
	cout << "10- View Page" << endl;*/


	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "SocialNetworkApp");
	window.setVerticalSyncEnabled(true);
	// Graphical User Interface
	bg_image1.loadFromFile("images/fb_blue_bg.png");
	bg_sprite1.setTexture(bg_image1);
	white_logo.loadFromFile("images/white_logo.png");
	wlogo_sprite.setTexture(white_logo);
	wlogo_sprite.setPosition(20, 10);
	blue_button.loadFromFile("images/blue_button1.png");
	button_sprite.setTexture(blue_button);
	button_sprite.setScale(scaleFactor, scaleFactor);
	button_sprite.setPosition((WIN_WIDTH - blue_button.getSize().x) / 2.0f, (WIN_HEIGHT - blue_button.getSize().y) / 2.0f);

	// Background 2
	bg_image2.loadFromFile("images/white_bg.jpg");
	bg_sprite2.setTexture(bg_image2);
	blue_logo.loadFromFile("images/blue_logo.png");
	blogo_sprite.setTexture(blue_logo);
	blogo_sprite.setPosition(5.f, -10.f);
	blogo_sprite.setScale(smallFactor, smallFactor);
	sf::RectangleShape line2(sf::Vector2f(1280.f, 3.f));
	line2.setPosition(0.f, 75.f);
	line2.setFillColor(sf::Color::Blue);

	//Set Font
	font.loadFromFile("images/Arial.ttf");

	// Set Texts
	sf::Text bluebutton_text("View Current Users", font, 22);
	bluebutton_text.setFillColor(sf::Color::White);
	sf::Text CurrentUserText;
	CurrentUserText.setFont(font);
	CurrentUserText.setCharacterSize(24);
	CurrentUserText.setFillColor(sf::Color::White);
	sf::FloatRect textBounds = bluebutton_text.getLocalBounds();
	bluebutton_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	bluebutton_text.setPosition(button_sprite.getPosition() + sf::Vector2f(button_sprite.getGlobalBounds().width / 2.0f, button_sprite.getGlobalBounds().height / 2.0f));
	sf::Text defaultText("Enter User ID:", font, 24);
	defaultText.setFillColor(sf::Color::Cyan);
	defaultText.setPosition(510.f, 83.f);
	sf::Text WriteUserText("Set User as Current User:", font, 24);
	WriteUserText.setFillColor(sf::Color::White);
	WriteUserText.setPosition(500.f,40.f);

	// Set Shapes and Lines
	sf::RectangleShape textBoxOutline(sf::Vector2f(300.f, 50.f));
	textBoxOutline.setPosition(500.f, 75.f); // Text box position
	textBoxOutline.setOutlineColor(sf::Color::White);
	textBoxOutline.setOutlineThickness(2.f);
	textBoxOutline.setFillColor(sf::Color::Transparent);

	sf::RectangleShape line(sf::Vector2f(280.f, 2.f)); // Line dimensions
	line.setPosition(510.f, 115.f); // Line position
	line.setFillColor(sf::Color::Black);
	CurrentUserText.setPosition(510.f, 83.f);

	// Bools
	bool BlueButtonClicked = false;
	bool CurrentUser_Entered = false;
	bool keyPressed = false;

	// Input Strings


	// SFML 
	while (window.isOpen())
	{
		sf::Event event;
		// Event Loop
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left && !BlueButtonClicked)
				{
					if (button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					{
						button_sprite.setColor(sf::Color::Transparent);
						bluebutton_text.setFillColor(sf::Color::Transparent);
						BlueButtonClicked = true;
					}
				}
			}
			else if (BlueButtonClicked && !CurrentUser_Entered)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b' && !Current_User.empty())
					{
						Current_User.pop_back();
						if (Current_User.empty())
						{
							defaultText.setFillColor(sf::Color::Cyan);
						}
						CurrentUserText.setString(Current_User);
					}
					else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n')
					{
						defaultText.setFillColor(sf::Color::Transparent);
						Current_User += static_cast<char>(event.text.unicode);
						CurrentUserText.setString(Current_User);
					}
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !Current_User.empty())
				{
					CurrentUser_Entered = true;					
				}
			}
		}

		// Drawing Sequence
		window.clear();
		window.draw(bg_sprite1);
		window.draw(wlogo_sprite);
		window.draw(button_sprite);
		window.draw(bluebutton_text);

		if (BlueButtonClicked)
		{
			int yOffset = 25;
			sf::Vector2f textPosition(400.f, 180.f);

			for (int i = 0; i < MaxUsers; i++)
			{
				users[i]->Display(window, textPosition);
				textPosition.y += yOffset;
			}

			window.draw(WriteUserText);
			window.draw(textBoxOutline);
			window.draw(line);
			window.draw(defaultText);
		}

		window.draw(CurrentUserText);
		if (CurrentUser_Entered)
		{
		    SetCurrentUser_Index();
			window.clear();

			window.draw(bg_sprite2);
			window.draw(blogo_sprite);
			window.draw(line2);
			Display_CurrentUser(window);
		}


		// Display the Window
		window.display();
	}

	cout << Current_User_Index << endl;

	/*cout << "\nEnter Post ID:" << endl;*/
	string ID;
	/* cin >> ID;*/
	View_Likes_By_ID(ID);

}

// Destructor
SocialNetworkApp::~SocialNetworkApp()
{
	for (int i = 0; i < MaxUsers; i++)
	{
		delete users[i];
	}
	delete[]users;

	for (int i = 0; i < MaxPages; i++)
	{
		delete pages[i];
	}
	delete[]pages;

	for (int i = 0; i < MaxPosts; i++)
	{
		delete posts[i];
	}
	delete[]posts;
}