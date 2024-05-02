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
	Choice = 0;
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
		PageFile >> pageId;
		getline(PageFile, pageTitle);

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

void SocialNetworkApp::View_Post_By_ID(sf::RenderWindow& window, const string& postID)
{
	bool found = false;
	for (int i = 0; i < MaxPosts; i++)
	{
		if (posts[i]->getPostID() == postID)
		{
			posts[i]->Display_Post(window);
			found = true;
			break;
		}
	}

	if (found == false)
	{
		cout << "Post not Found." << endl;
	}
}

void SocialNetworkApp::View_Page_By_ID(sf::RenderWindow&, const string&)
{

}

void SocialNetworkApp::View_Likes_By_ID(sf::RenderWindow& window, const string& postID)
{
	stringstream input;
	sf::Font font;
	font.loadFromFile("images/Segoe UI Historic.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(28);
	text.setFillColor(sf::Color::Black);
	text.setLineSpacing(2);
	text.setPosition(300.f, 250.f);

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
						input << users[k]->getUserID() << " : " << users[k]->getFirstName() << " " << users[k]->getLastName() << endl;
						found = true;
						break;
					}
				}

				if (found == false)
				{
					for (int k = 0; k < MaxPages; k++)
					{
						if (posts[i]->getLikedByID(j) == pages[k]->getPageID())
						{
							input << pages[k]->getPageID() << " : " << pages[k]->getTitle() << endl;
							break;
						}
					}
				}
			}
			break;
		}
	}

	text.setString(input.str());
	window.draw(text);
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
	ss << "Logged in as :   " << users[Current_User_Index]->getUserID() << " -  " << users[Current_User_Index]->getFirstName() << " " << users[Current_User_Index]->getLastName();
	string text = ss.str();

	defaultText.setString(text);

	window.draw(defaultText);
}

void SocialNetworkApp::Display_UserMenu(sf::RenderWindow& window)
{
	sf::Texture Main_Menu, Menu_bg;
	sf::Sprite Menu_sprite, menu_bg_sprite;
	sf::Text menuOptions;

	Main_Menu.loadFromFile("images/main_menu1.png");
	Menu_sprite.setTexture(Main_Menu);
	Menu_sprite.setScale(0.2f, 0.2f);
	Menu_sprite.setPosition(200.f, 50.f);
	Menu_bg.loadFromFile("images/3d_bg3.png");
	menu_bg_sprite.setTexture(Menu_bg);
	menu_bg_sprite.setScale(0.82f, 1.f);
	menu_bg_sprite.setPosition(180.f, 170.f); // 891.f ending point

	// Menu Options
	menuOptions.setFont(font);
	menuOptions.setCharacterSize(20);
	menuOptions.setFillColor(sf::Color::Black);
	menuOptions.setPosition(230.f, 220.f);

	menuOptions.setString(
		"1.  View Home of Current User.\n\n"
		"2.  Like a Post.\n\n"
		"3.  View the List of People who liked a Post.\n\n"
		"4.  Comment on a Post.\n\n"
		"5.  View a Post.\n\n"
		"6.  Share a Memory.\n\n"
		"7.  View Current User's Timeline.\n\n"
		"8.  View Friend List.\n\n"
		"9.  View a Page."
	);

	// Choice TextBox
	sf::RectangleShape textBoxOutline(sf::Vector2f(255.f, 50.f));
	textBoxOutline.setPosition(960.f, 300.f); // Text box position
	textBoxOutline.setOutlineColor(sf::Color(0, 100, 209));
	textBoxOutline.setOutlineThickness(2.f);
	textBoxOutline.setFillColor(sf::Color::Transparent);

	sf::RectangleShape line(sf::Vector2f(242.f, 2.f)); // Line dimensions
	line.setPosition(968.f, 340.f); // Line position
	line.setFillColor(sf::Color::Black);

	sf::Text defaultText("Enter Choice:", font, 24);
	defaultText.setFillColor(sf::Color::Black);
	defaultText.setPosition(960.f, 265.f);

	// Draw Sequence
	window.draw(Menu_sprite);
	window.draw(menu_bg_sprite);
	window.draw(menuOptions);
	window.draw(textBoxOutline);
	window.draw(line);
	window.draw(defaultText);

}

void SocialNetworkApp::Run()
{
	// Reading Files
	Read_UserData_FromFile();
	Read_PageData_FromFile();
	Read_PostData_FromFile();
	Read_CommentData_FromFile();


	// Setting Timelines
	for (int i = 0; i < MaxUsers; i++)
	{
		users[i]->SetTimeline(posts, MaxPosts);
	}
	for (int i = 0; i < MaxPages; i++)
	{
		pages[i]->SetTimeline(posts, MaxPosts);
	}

	// Assigning Post Owners
	for (int i = 0; i < MaxPosts; i++)
	{
		posts[i]->AssigningOwner(users, pages, MaxUsers, MaxPages);
	}

	//User Interface

	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "SocialNetworkApp", sf::Style::None);
	window.setVerticalSyncEnabled(true);
	// Graphical User Interface
	bg_image1.loadFromFile("images/fb_blue_bg.png");
	bg_sprite1.setTexture(bg_image1);
	white_logo.loadFromFile("images/white_logo.png");
	wlogo_sprite.setTexture(white_logo);
	wlogo_sprite.setPosition(20, 10);
	blue_button.loadFromFile("images/blue_button.png");
	button_sprite.setTexture(blue_button);
	button_sprite.setPosition((WIN_WIDTH - blue_button.getSize().x) / 2.0f, (WIN_HEIGHT - blue_button.getSize().y) / 2.0f);
	back_button.loadFromFile("images/back_button2.png");
	back_button_sprite.setTexture(back_button);
	back_button_sprite.setScale(0.3f, 0.3f);
	back_button_sprite.setPosition(20.f, 100.f);
	sf::Color originalColor = back_button_sprite.getColor();


	// Background 2
	bg_image2.loadFromFile("images/white_bg.jpg");
	bg_sprite2.setTexture(bg_image2);
	blue_logo.loadFromFile("images/blue_logo.png");
	blogo_sprite.setTexture(blue_logo);
	blogo_sprite.setPosition(5.f, -10.f);
	blogo_sprite.setScale(smallFactor, smallFactor);
	sf::RectangleShape line2(sf::Vector2f(1280.f, 3.f));
	line2.setPosition(0.f, 75.f);
	line2.setFillColor(sf::Color(0, 100, 209));

	//Set Font
	font.loadFromFile("images/Arial.ttf");

	// Set Texts
	sf::Text bluebutton_text("View Current Users", font, 22);
	bluebutton_text.setFillColor(sf::Color::Yellow);
	sf::Text CurrentUserText;
	CurrentUserText.setFont(font);
	CurrentUserText.setCharacterSize(24);
	CurrentUserText.setFillColor(sf::Color::White);
	sf::FloatRect textBounds = bluebutton_text.getLocalBounds();
	bluebutton_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	bluebutton_text.setPosition(button_sprite.getPosition() + sf::Vector2f(button_sprite.getGlobalBounds().width / 2.0f, button_sprite.getGlobalBounds().height / 2.0f));
	// User ID Box
	sf::Text defaultText("Enter User ID:", font, 24);
	defaultText.setFillColor(sf::Color::Cyan);
	defaultText.setPosition(510.f, 83.f);
	sf::Text WriteUserText("Set User as Current User:", font, 24);
	WriteUserText.setFillColor(sf::Color::White);
	WriteUserText.setPosition(500.f, 40.f);
	sf::Text ChoiceText("", font, 24);
	ChoiceText.setFillColor(sf::Color::Black);
	ChoiceText.setPosition(968.f, 310.f);
	//post ID box
	sf::Text defaultText2("Enter Post ID: ", font, 29);
	defaultText2.setFillColor(sf::Color::Black);
	defaultText2.setPosition(512.f, 277.f);
	sf::Text PostIdText;
	PostIdText.setFont(font);
	PostIdText.setCharacterSize(24);
	PostIdText.setFillColor(sf::Color::Black);
	PostIdText.setPosition(520.f, 355.f);

	// Page ID Box
	sf::Text defaultText3("Enter Page ID: ", font, 29);
	defaultText3.setFillColor(sf::Color::Black);
	defaultText3.setPosition(512.f, 277.f);
	sf::Text PageIdText;
	PageIdText.setFont(font);
	PageIdText.setCharacterSize(24);
	PageIdText.setFillColor(sf::Color::Black);
	PageIdText.setPosition(520.f, 355.f);

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

	//Post ID TextBox
	sf::RectangleShape textBoxOutline1(sf::Vector2f(255.f, 50.f));
	textBoxOutline1.setPosition(512.f, 315.f); // Text box position
	textBoxOutline1.setOutlineColor(sf::Color(0, 100, 209));
	textBoxOutline1.setOutlineThickness(2.f);
	textBoxOutline1.setFillColor(sf::Color::Transparent);

	sf::RectangleShape line3(sf::Vector2f(242.f, 2.f)); // Line dimensions
	line3.setPosition(520.f, 355.f); // Line position
	line3.setFillColor(sf::Color::Black);

	post_bg.loadFromFile("images/post_bg.png");
	post_bg_sprite.setTexture(post_bg);
	post_bg_sprite.setPosition(250.f, 100.f);
	post_bg_sprite.setScale(1.f, 0.84f);

	// Bools
	bool BlueButtonClicked = false;
	bool CurrentUser_Entered = false;
	bool keyPressed = false;
	bool ChoiceEntered = false;
	bool PostID_Entered = false;
	bool PageID_Entered = false;

	// Input Strings
	string ID_toViewPost;
	string ID_toViewPage;

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
				else if (event.mouseButton.button == sf::Mouse::Left && BlueButtonClicked && CurrentUser_Entered && ChoiceEntered)
				{
					if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					{
						back_button_sprite.setColor(sf::Color::Transparent);
						ChoiceEntered = false;
						PostID_Entered = false;
						PageID_Entered = false;

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
			else if (BlueButtonClicked && CurrentUser_Entered && !ChoiceEntered)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128 && (event.text.unicode >= '0' && event.text.unicode <= '9'))
					{
						ChoiceText.setString(ChoiceText.getString() + static_cast<char>(event.text.unicode));
					}
					else if (event.text.unicode == '\b' && !ChoiceText.getString().isEmpty())
					{
						std::string str = ChoiceText.getString();
						str.pop_back();
						ChoiceText.setString(str);
					}
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !Current_User.empty())
				{
					Choice = std::stoi(ChoiceText.getString().toAnsiString());
					ChoiceEntered = true;
				}
			}
			else if (BlueButtonClicked && ChoiceEntered && Choice == 5 || Choice == 3 && !PostID_Entered)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b' && !ID_toViewPost.empty())
					{
						ID_toViewPost.pop_back();
						PostIdText.setString(ID_toViewPost);
					}
					else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n')
					{
						ID_toViewPost += static_cast<char>(event.text.unicode);
						PostIdText.setString(ID_toViewPost);
					}
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !ID_toViewPost.empty())
				{
					PostID_Entered = true;
				}
			}
			else if (BlueButtonClicked && ChoiceEntered && Choice == 9 && !PageID_Entered)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b' && !ID_toViewPage.empty())
					{
						ID_toViewPage.pop_back();
						PageIdText.setString(ID_toViewPage);
					}
					else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n')
					{
						ID_toViewPage += static_cast<char>(event.text.unicode);
						PageIdText.setString(ID_toViewPage);
					}
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !ID_toViewPage.empty())
				{
					PageID_Entered = true;
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

				if (!ChoiceEntered)
				{
					Display_UserMenu(window);
					window.draw(ChoiceText);

					// Option 5 reset
					textBoxOutline1.setOutlineColor(sf::Color(0, 100, 209));
					defaultText2.setFillColor(sf::Color::Black);
					PostIdText.setFillColor(sf::Color::Black);
					line3.setFillColor(sf::Color::Black);
					ID_toViewPost = "";
					PostIdText.setString(ID_toViewPost);

					// Option 9 reset
					defaultText3.setFillColor(sf::Color::Black);
					PageIdText.setFillColor(sf::Color::Black);
					ID_toViewPage = "";
					PageIdText.setString(ID_toViewPage);
				}

				if (ChoiceEntered)
				{
					back_button_sprite.setColor(originalColor);
					window.draw(back_button_sprite);


					if (Choice == 1)
					{

					}
					else if (Choice == 2)
					{

					}
					else if (Choice == 3)
					{
						window.draw(textBoxOutline1);
						window.draw(defaultText2);
						window.draw(line3);
						window.draw(PostIdText);

						if (PostID_Entered)
						{
							textBoxOutline1.setOutlineColor(sf::Color::Transparent);
							defaultText2.setFillColor(sf::Color::Transparent);
							PostIdText.setFillColor(sf::Color::Transparent);
							line3.setFillColor(sf::Color::Transparent);

							View_Likes_By_ID(window, ID_toViewPost);
						}
					}
					else if (Choice == 4)
					{

					}
					else if (Choice == 5)
					{
						window.draw(textBoxOutline1);
						window.draw(defaultText2);
						window.draw(line3);
						window.draw(PostIdText);

						if (PostID_Entered)
						{
							textBoxOutline1.setOutlineColor(sf::Color::Transparent);
							defaultText2.setFillColor(sf::Color::Transparent);
							PostIdText.setFillColor(sf::Color::Transparent);
							line3.setFillColor(sf::Color::Transparent);

							window.draw(post_bg_sprite);

							View_Post_By_ID(window, ID_toViewPost);
						}

					}
					else if (Choice == 6)
					{

					}
					else if (Choice == 7)
					{

					}
					else if (Choice == 8)
					{
						users[Current_User_Index]->Display_FriendList(window, users, MaxUsers);
					}
					else if (Choice == 9)
					{
						window.draw(textBoxOutline1);
						window.draw(defaultText3);
						window.draw(line3);
						window.draw(PageIdText);

						if (PageID_Entered)
						{
							textBoxOutline1.setOutlineColor(sf::Color::Transparent);
							defaultText3.setFillColor(sf::Color::Transparent);
							PageIdText.setFillColor(sf::Color::Transparent);
							line3.setFillColor(sf::Color::Transparent);

							View_Page_By_ID(window, ID_toViewPage);
						}
					}

				}

			}


			// Display the Window
			window.display();
		}
	}
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