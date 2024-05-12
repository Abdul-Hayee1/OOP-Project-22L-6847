#include "SocialNetworkApp.h"

// Constructor
SocialNetworkApp::SocialNetworkApp()
{
	users = nullptr;
	posts = nullptr;
	pages = nullptr;
	CurrentDate = nullptr;
	MaxUsers = 0;
	MaxPages = 0;
	MaxPosts = 0;
	MaxComments = 0;
	Current_User_Index = -1;
	Choice = 0;
	font1.loadFromFile("images/Segoe UI Historic.ttf");
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

		UserFile.ignore();
		string image_path;
		getline(UserFile, image_path);

		User* newUser = new User(userId, First_name, Last_name, friendId, friendCount, likedPgsID, likedPgsCount, image_path);

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
			string* IDsWhoLiked = new string[MAX_LIKES_ON_POST];
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
			string* IDsWhoLiked = new string[MAX_LIKES_ON_POST];
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
void SocialNetworkApp::Display_CurrentSystemDate(sf::RenderWindow& window)
{
	stringstream ss;
	ss << "Current Date: " << CurrentDate->getDay() << "-" << CurrentDate->getMonth() << "-" << CurrentDate->getYear();

	sf::Text date_text(ss.str(), font1, 26);
	date_text.setFillColor(sf::Color::Black);
	date_text.setPosition(970.f, 100.f);

	window.draw(date_text);
}

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

void SocialNetworkApp::View_Post_By_ID(sf::RenderWindow& window, const string& postID, bool ShowCommentSection)
{
	bool found = false;
	for (int i = 0; i < MaxPosts; i++)
	{
		if (posts[i]->getPostID() == postID)
		{
			posts[i]->Display_Post(window, ShowCommentSection);
			found = true;
			break;
		}
	}

	if (found == false)
	{
		cout << "Invalid Post ID." << endl;
	}
}

void SocialNetworkApp::View_Page_By_ID(sf::RenderWindow& window, const sf::Event& event, const string& pageID, bool ShowCommentSection)
{
	bool found = false;
	for (int i = 0; i < MaxPages; i++)
	{
		if (pages[i]->getPageID() == pageID)
		{
			pages[i]->DisplayTimeline(window, event, ShowCommentSection);
			found = true;
			break;
		}
	}

	if (found == false)
	{
		cout << "Invalid Page ID." << endl;
	}
}

void SocialNetworkApp::View_Likes_By_ID(sf::RenderWindow& window, const string& postID)
{
	stringstream input;
	sf::Font font;
	font.loadFromFile("images/Segoe UI Historic.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(28);
	text.setFillColor(sf::Color(0, 100, 209));
	text.setLineSpacing(2);
	text.setPosition(300.f, 250.f);

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
	sf::Text defaultText, defaultText1;
	defaultText.setFont(font);
	defaultText.setCharacterSize(26);
	defaultText.setFillColor(sf::Color::Black);
	defaultText.setPosition(740.f, 36.f);
	defaultText1.setFont(font);
	defaultText1.setCharacterSize(26);
	defaultText1.setFillColor(sf::Color::Black);
	defaultText1.setPosition(995.f, 36.f);


	sf::Vector2f Position(910.f, 0.f);
	float smallfactor = 0.14f;

	users[Current_User_Index]->Display_ProfilePic(window, Position, smallfactor);
	stringstream ss, sd;
	ss << "Logged in as :";
	sd << users[Current_User_Index]->getUserID() << " -  " << users[Current_User_Index]->getFirstName() << " " << users[Current_User_Index]->getLastName();
	string text = ss.str();
	string text2 = sd.str();
	defaultText.setString(text);
	defaultText1.setString(text2);
	window.draw(defaultText1);
	window.draw(defaultText);
}

void SocialNetworkApp::Display_UserMenu(sf::RenderWindow& window) const
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

	// Assigning Friends and Liked Pages
	for (int i = 0; i < MaxUsers; i++)
	{
		users[i]->SetFriends_and_Pages(users, pages, MaxUsers, MaxPages);
	}
	
	CurrentDate = new Date(15, 11, 2017);

	// Setting User's Home
	for (int i = 0; i < MaxUsers; i++)
	{
		users[i]->SetHome(CurrentDate);
	}

	// User Interface
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
	// Logout Button
	logout.loadFromFile("images/logout.png");
	logout_button_sprite.setTexture(logout);
	sf::Color originalColor1 = logout_button_sprite.getColor();
	logout_button_sprite.setScale(1.4f, 1.4f);
	logout_button_sprite.setPosition(1224.f,100.f);
	sf::Text logout_text("Logout", font1, 26);
	logout_text.setFillColor(sf::Color(101, 103, 107));
	logout_text.setPosition(1125.f, 98.f);



	// Background 2
	bg_image2.loadFromFile("images/white_bg.jpg");
	bg_sprite2.setTexture(bg_image2);
	blue_logo.loadFromFile("images/blue_logo.png");
	blogo_sprite.setTexture(blue_logo);
	blogo_sprite.setPosition(5.f, -10.f);
	blogo_sprite.setScale(smallFactor, smallFactor);
	sf::RectangleShape line2(sf::Vector2f(1280.f, 3.f));
	line2.setPosition(0.f, 80.f);
	line2.setFillColor(sf::Color(0, 100, 209));

	//Set Font
	font.loadFromFile("images/Arial.ttf");

	// Set Texts
	sf::Text bluebutton_text("View Current Users", font, 22);
	bluebutton_text.setFillColor(sf::Color(255, 255, 0));
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
	sf::Text defaultText2("Enter Post ID: ", font, 28);
	defaultText2.setFillColor(sf::Color::Black);
	defaultText2.setPosition(512.f, 277.f);
	sf::Text PostIdText;
	PostIdText.setFont(font);
	PostIdText.setCharacterSize(24);
	PostIdText.setFillColor(sf::Color::Black);
	PostIdText.setPosition(522.f, 320.f);

	// Page ID Box
	sf::Text defaultText3("Enter Page ID: ", font, 28);
	defaultText3.setFillColor(sf::Color::Black);
	defaultText3.setPosition(512.f, 277.f);
	sf::Text PageIdText;
	PageIdText.setFont(font);
	PageIdText.setCharacterSize(24);
	PageIdText.setFillColor(sf::Color::Black);
	PageIdText.setPosition(522.f, 320.f);

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

	post_bg.loadFromFile("images/post_bg (2).png");
	post_bg_sprite.setTexture(post_bg);
	post_bg_sprite.setPosition(250.f, 100.f);
	post_bg_sprite.setScale(1.f, 0.9f);

	// Home Page
	fb_home.loadFromFile("images/fb_home_icon.png");
	fb_home_sprite.setTexture(fb_home);
	fb_home_sprite.setScale(0.1f, 0.1f);
	fb_home_sprite.setPosition(290.f, 25.f);
	sf::Text fb_home_text("Home", font1, 26);
	fb_home_text.setFillColor(sf::Color(101, 103, 107));
	fb_home_text.setPosition(341.f, 37.f);

	// Comment Section
	sf::Text comment_desc_text;
	font1.loadFromFile("images/Segoe UI Historic.ttf");
	comment_desc_text.setFont(font1);
	comment_desc_text.setCharacterSize(24);
	comment_desc_text.setFillColor(sf::Color::Black);
	comment_desc_text.setPosition(420.f, 350.f);
	sf::Text defaultText_comment("Add a comment...", font1, 25);
	defaultText_comment.setFillColor(sf::Color(101, 103, 107));
	defaultText_comment.setPosition(420.f, 350.f);

	add_commentBox.loadFromFile("images/add_comment_box.png");  // Choice == 4
	add_commentBox_sprite.setTexture(add_commentBox);
	add_commentBox_sprite.setScale(1.5f, 1.8f);
	add_commentBox_sprite.setPosition(390.f, 320.f);
	sf::Color originalColor2 = add_commentBox_sprite.getColor();
	sf::Vector2f add_comm_profile_position(280.f, 330.f);
	float scaleFactor_comm_profile = 0.22f;
	sf::Text comment_posted_text("Comment Posted.", font1, 35);
	comment_posted_text.setFillColor(sf::Color(101, 103, 107));
	comment_posted_text.setPosition(550.f, 330.f);

	sf::RectangleShape comment_box(sf::Vector2f(680.f, 62.f));  // To activate comment event
	comment_box.setOutlineColor(sf::Color::Black);
	comment_box.setPosition(262.f, 603.f);
	comment_box.setOutlineThickness(2.f);
	comment_box.setFillColor(sf::Color::Transparent);
	sf::FloatRect smallerRegion(262.f, 603.f, 680.f, 62.f);

	comment_bg.loadFromFile("images/3d_bg3.png");
	comment_bg_sprite.setTexture(comment_bg);
	comment_bg_sprite.setPosition(220.f, 100.f);
	comment_bg_sprite.setScale(1.f, 1.25);

	// CHOICE == 3
	view_likes_bg.loadFromFile("images/view_likes_bg.png");
	likes_bg_sprite.setTexture(view_likes_bg);
	likes_bg_sprite.setPosition(280.f, 100.f);
	likes_bg_sprite.setScale(1.f, 0.8f);
	sf::Text likePage_id_text;
	likePage_id_text.setFont(font);
	likePage_id_text.setCharacterSize(29);
	likePage_id_text.setPosition(590.f, 125.f);
	likePage_id_text.setFillColor(sf::Color::Black);

	// Timeline
	sf::Text TimelineDefaulText("No Posts Uploaded.", font1, 32);
	TimelineDefaulText.setFillColor(sf::Color(101, 103, 107));
	TimelineDefaulText.setPosition(525.f, 350.f);

	// Memory
	sf::Text MemoryText_text;
	MemoryText_text.setFont(font1);
	MemoryText_text.setCharacterSize(26);
	MemoryText_text.setFillColor(sf::Color::Black);
	MemoryText_text.setPosition(522.f, 320.f);
	sf::Text defaultMemoryText("Enter Memory Text:", font1, 28);
	defaultMemoryText.setPosition(512.f, 277.f);
	defaultMemoryText.setFillColor(sf::Color::Black);

	sf::Text defaultText6("Memory Posted.", font1, 35);
	defaultText6.setFillColor(sf::Color(101, 103, 107));
	defaultText6.setPosition(530.f, 330.f);

	// Bools
	bool BlueButtonClicked = false;
	bool CurrentUser_Entered = false;
	bool LogoutButtonClicked = false;
	bool keyPressed = false;
	bool ChoiceEntered = false;
	bool PostID_Entered = false;
	bool PageID_Entered = false;
	bool ShowCommentSection = false;
	bool Comment_Entered = false;
	bool Comment_Entered1 = false;
	bool MemoryTextEntered = false;
	bool LikeButtonClicked = false;
	bool UnlikeButtonClicked = false;
	bool LikedState = false;
	bool MemoryEntered = false;
	bool HomeSet = false;

	// Input Strings
	string ID_toViewPost;
	string ID_toViewPage;
	string comment_description;
	string MemoryText;

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

			if (!BlueButtonClicked)
			{
				if (event.type == sf::Event::MouseButtonPressed)
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
			else if (BlueButtonClicked && CurrentUser_Entered)
			{
				if (event.type == sf::Event::MouseButtonPressed)  // Logout Button
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (logout_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
						{
							logout_button_sprite.setColor(sf::Color::Transparent);
							CurrentUser_Entered = false;
						}
					}
				}


				if (ChoiceEntered == true)
				{
					if (Choice == 1)
					{
						if (ShowCommentSection == false)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ChoiceEntered = false;
									}
								}
							}

							if (event.type == sf::Event::MouseButtonPressed)
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (smallerRegion.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										ShowCommentSection = true;
									}
								}
							}
						}
						else if (ShowCommentSection == true)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ShowCommentSection = false;
									}
								}
							}
						}
					}
					else if (Choice == 2)
					{
						if (PostID_Entered == false)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ChoiceEntered = false;
									}
								}
							}

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

								textBoxOutline1.setOutlineColor(sf::Color::Transparent);
								defaultText2.setFillColor(sf::Color::Transparent);
								PostIdText.setFillColor(sf::Color::Transparent);
								line3.setFillColor(sf::Color::Transparent);
							}
						}
						else if (PostID_Entered == true)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										PostID_Entered = false;
										textBoxOutline1.setOutlineColor(sf::Color(0, 100, 209));
										defaultText2.setFillColor(sf::Color::Black);
										PostIdText.setFillColor(sf::Color::Black);
										line3.setFillColor(sf::Color::Black);
										ID_toViewPost = "";
										PostIdText.setString(ID_toViewPost);
									}
								}
							}

							if (LikedState == false && LikeButtonClicked == false && UnlikeButtonClicked == false)
							{
								if (event.type == sf::Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if (smallerRegion.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
										{
											LikeButtonClicked = true;
											LikedState = true;
										}
									}
								}
							}
							else if (LikedState == true && UnlikeButtonClicked == false)
							{
								if (event.type == sf::Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if (smallerRegion.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
										{
											UnlikeButtonClicked = true;
											LikedState = false;
										}
									}
								}
							}
						}
					}
					else if (Choice == 3)
					{
						if (PostID_Entered == false)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ChoiceEntered = false;
									}
								}
							}

							if (event.type == sf::Event::TextEntered)
							{
								if (event.text.unicode == '\b' && !ID_toViewPost.empty())
								{
									ID_toViewPost.pop_back();
									PostIdText.setString(ID_toViewPost);
									likePage_id_text.setString(ID_toViewPost);
								}
								else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n')
								{
									ID_toViewPost += static_cast<char>(event.text.unicode);
									PostIdText.setString(ID_toViewPost);
									likePage_id_text.setString(ID_toViewPost);
								}
							}
							else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !ID_toViewPost.empty())
							{
								PostID_Entered = true;

								textBoxOutline1.setOutlineColor(sf::Color::Transparent);
								defaultText2.setFillColor(sf::Color::Transparent);
								PostIdText.setFillColor(sf::Color::Transparent);
								line3.setFillColor(sf::Color::Transparent);
							}
						}
						else if (PostID_Entered == true)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										PostID_Entered = false;
										textBoxOutline1.setOutlineColor(sf::Color(0, 100, 209));
										defaultText2.setFillColor(sf::Color::Black);
										PostIdText.setFillColor(sf::Color::Black);
										line3.setFillColor(sf::Color::Black);
										ID_toViewPost = "";
										PostIdText.setString(ID_toViewPost);
									}
								}
							}
						}
					}
					else if (Choice == 4)
					{
						if (PostID_Entered == false)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ChoiceEntered = false;
									}
								}
							}

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

								textBoxOutline1.setOutlineColor(sf::Color::Transparent);
								defaultText2.setFillColor(sf::Color::Transparent);
								PostIdText.setFillColor(sf::Color::Transparent);
								line3.setFillColor(sf::Color::Transparent);
							}
						}
						else if (PostID_Entered == true)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										PostID_Entered = false;
										textBoxOutline1.setOutlineColor(sf::Color(0, 100, 209));
										defaultText2.setFillColor(sf::Color::Black);
										PostIdText.setFillColor(sf::Color::Black);
										line3.setFillColor(sf::Color::Black);
										add_commentBox_sprite.setColor(originalColor2);
										ID_toViewPost = "";
										comment_description = "";
										comment_desc_text.setString(comment_description);
										PostIdText.setString(ID_toViewPost);
										comment_desc_text.setFillColor(sf::Color::Black);
										Comment_Entered1 = false;
									}
								}
							}

							if (Comment_Entered == false)
							{
								if (event.type == sf::Event::TextEntered)
								{
									if (event.text.unicode == '\b' && !comment_description.empty())
									{
										comment_description.pop_back();
										if (comment_description.empty())
										{
											defaultText_comment.setFillColor(sf::Color(101, 103, 107));
										}
										comment_desc_text.setString(comment_description);
									}
									else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n')
									{
										comment_description += static_cast<char>(event.text.unicode);
										defaultText_comment.setFillColor(sf::Color::Transparent);
										comment_desc_text.setString(comment_description);
									}
								}
								else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !comment_description.empty())
								{
									Comment_Entered = true;
									Comment_Entered1 = true;
									add_commentBox_sprite.setColor(sf::Color::Transparent);
									comment_desc_text.setFillColor(sf::Color::Transparent);
								}
							}
						}
					}
					else if (Choice == 5)
					{
						if (PostID_Entered == true)
						{

							if (ShowCommentSection == false)
							{
								if (event.type == sf::Event::MouseButtonPressed)  // back button
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
										{
											PostID_Entered = false;
											textBoxOutline1.setOutlineColor(sf::Color(0, 100, 209));
											defaultText2.setFillColor(sf::Color::Black);
											PostIdText.setFillColor(sf::Color::Black);
											line3.setFillColor(sf::Color::Black);
											ID_toViewPost = "";
											PostIdText.setString(ID_toViewPost);
										}
									}
								}

								if (event.type == sf::Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if (smallerRegion.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
										{
											ShowCommentSection = true;
										}
									}
								}
							}
							if (ShowCommentSection == true)
							{
								if (event.type == sf::Event::MouseButtonPressed)  // back button
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
										{
											back_button_sprite.setColor(sf::Color::Transparent);
											ShowCommentSection = false;
										}
									}
								}
							}
						}
						else if (PostID_Entered == false)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ChoiceEntered = false;
									}
								}
							}

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

								textBoxOutline1.setOutlineColor(sf::Color::Transparent);
								defaultText2.setFillColor(sf::Color::Transparent);
								PostIdText.setFillColor(sf::Color::Transparent);
								line3.setFillColor(sf::Color::Transparent);
							}
						}
					}
					else if (Choice == 6)
					{
						if (PostID_Entered == false)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ChoiceEntered = false;
									}
								}
							}

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

								textBoxOutline1.setOutlineColor(sf::Color::Transparent);
								defaultText2.setFillColor(sf::Color::Transparent);
								PostIdText.setFillColor(sf::Color::Transparent);
								line3.setFillColor(sf::Color::Transparent);
							}
						}
						else if (PostID_Entered == true)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										PostID_Entered = false;
										textBoxOutline1.setOutlineColor(sf::Color(0, 100, 209));
										defaultText2.setFillColor(sf::Color::Black);
										PostIdText.setFillColor(sf::Color::Black);
										line3.setFillColor(sf::Color::Black);
										ID_toViewPost = "";
										PostIdText.setString(ID_toViewPost);
									}
								}
							}

							if (MemoryTextEntered == false)
							{
								if (event.type == sf::Event::TextEntered)
								{
									if (event.text.unicode == '\b' && !MemoryText.empty())
									{
										MemoryText.pop_back();
										MemoryText_text.setString(MemoryText);
									}
									else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\n')
									{
										MemoryText += static_cast<char>(event.text.unicode);
										MemoryText_text.setString(MemoryText);
									}
								}
								else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !MemoryText.empty())
								{
									MemoryTextEntered = true;
									MemoryEntered = true;
									defaultMemoryText.setFillColor(sf::Color::Transparent);
									MemoryText_text.setFillColor(sf::Color::Transparent);
								}
							}
							if (MemoryEntered == true)
							{
								if (event.type == sf::Event::MouseButtonPressed)  // back button
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
										{
											back_button_sprite.setColor(sf::Color::Transparent);
											ChoiceEntered = false;
											MemoryEntered = false;
											MemoryTextEntered = false;
											MemoryText = "";
											MemoryText_text.setString(MemoryText);
											defaultMemoryText.setFillColor(sf::Color::Black);
											MemoryText_text.setFillColor(sf::Color::Black);
										}
									}
								}
							}
						}
					}
					else if (Choice == 7)
					{

						if (ShowCommentSection == false)
						{
							if (event.type == sf::Event::MouseButtonPressed)
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (smallerRegion.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										ShowCommentSection = true;
									}
								}
							}

							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ChoiceEntered = false;
										users[Current_User_Index]->setCurrentPostIndex();
									}
								}
							}
						}
						else if (ShowCommentSection == true)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ShowCommentSection = false;
									}
								}
							}
						}
					}
					else if (Choice == 8)
					{
						if (event.type == sf::Event::MouseButtonPressed)  // back button
						{
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
								{
									back_button_sprite.setColor(sf::Color::Transparent);
									ChoiceEntered = false;
								}
							}
						}
					}
					else if (Choice == 9)
					{
						if (PageID_Entered == false)
						{
							if (event.type == sf::Event::MouseButtonPressed)  // back button
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
									{
										back_button_sprite.setColor(sf::Color::Transparent);
										ChoiceEntered = false;
									}
								}
							}

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

								textBoxOutline1.setOutlineColor(sf::Color::Transparent);
								defaultText3.setFillColor(sf::Color::Transparent);
								PageIdText.setFillColor(sf::Color::Transparent);
								line3.setFillColor(sf::Color::Transparent);
							}
						}
						else if (PageID_Entered == true)
						{
							if (ShowCommentSection == false)
							{
								if (event.type == sf::Event::MouseButtonPressed)  // back button
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
										{
											PageID_Entered = false;

											defaultText3.setFillColor(sf::Color::Black);
											PageIdText.setFillColor(sf::Color::Black);
											textBoxOutline1.setOutlineColor(sf::Color(0, 100, 209));
											line3.setFillColor(sf::Color::Black);
											ID_toViewPage = "";
											PageIdText.setString(ID_toViewPage);
										}
									}
								}

								if (event.type == sf::Event::MouseButtonPressed)
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if (smallerRegion.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
										{
											ShowCommentSection = true;
										}
									}
								}
							}

							if (ShowCommentSection == true)
							{
								if (event.type == sf::Event::MouseButtonPressed)  // back button
								{
									if (event.mouseButton.button == sf::Mouse::Left)
									{
										if (back_button_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
										{
											back_button_sprite.setColor(sf::Color::Transparent);
											ShowCommentSection = false;
										}
									}
								}
							}
						}
					}

				}
				else if (ChoiceEntered == false)
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
						logout_button_sprite.setColor(sf::Color::Transparent);
						logout_text.setFillColor(sf::Color::Transparent);
					}
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

			if (!ChoiceEntered)
			{
				Display_UserMenu(window);
				window.draw(ChoiceText);

				logout_button_sprite.setColor(originalColor1);
				window.draw(logout_button_sprite);
				logout_text.setFillColor(sf::Color(101, 103, 107));
				window.draw(logout_text);
			}

			if (ChoiceEntered)
			{
				back_button_sprite.setColor(originalColor);
				window.draw(back_button_sprite);

				if (Choice == 1)
				{
					if (ShowCommentSection == false)
					{
						if (users[Current_User_Index]->getHomePostsCount() != 0)
						{
							Display_CurrentSystemDate(window);
							window.draw(post_bg_sprite);
							window.draw(fb_home_sprite);
							window.draw(fb_home_text);
						}
						users[Current_User_Index]->Display_Home(window, event, ShowCommentSection);
					}
					else if (ShowCommentSection == true)
					{
						window.draw(comment_bg_sprite);
						users[Current_User_Index]->Display_Home(window, event, ShowCommentSection);
					}
				}
				else if (Choice == 2)
				{
					window.draw(textBoxOutline1);
					window.draw(defaultText2);
					window.draw(line3);
					window.draw(PostIdText);

					if (PostID_Entered)
					{
						window.draw(post_bg_sprite);
						View_Post_By_ID(window, ID_toViewPost, ShowCommentSection);

						if (LikeButtonClicked == true)
						{
							for (int i = 0; i < MaxPosts; i++)
							{
								if (posts[i]->getPostID() == ID_toViewPost)
								{
									posts[i]->Add_Like(users[Current_User_Index]->getUserID());
									break;
								}
							}
							LikeButtonClicked = false;
						}
						else if (UnlikeButtonClicked == true)
						{
							for (int i = 0; i < MaxPosts; i++)
							{
								if (posts[i]->getPostID() == ID_toViewPost)
								{
									posts[i]->Remove_Like();
									break;
								}
							}
							UnlikeButtonClicked = false;
						}
					}
				}
				else if (Choice == 3)
				{
					window.draw(textBoxOutline1);
					window.draw(defaultText2);
					window.draw(line3);
					window.draw(PostIdText);

					if (PostID_Entered)
					{
						window.draw(likes_bg_sprite);
						window.draw(likePage_id_text);
						View_Likes_By_ID(window, ID_toViewPost);
					}
				}
				else if (Choice == 4)
				{
					window.draw(textBoxOutline1);
					window.draw(defaultText2);
					window.draw(line3);
					window.draw(PostIdText);

					if (PostID_Entered == true && Comment_Entered1 == false)
					{
						users[Current_User_Index]->Display_ProfilePic(window, add_comm_profile_position, scaleFactor_comm_profile);
						window.draw(add_commentBox_sprite);
						window.draw(defaultText_comment);
						window.draw(comment_desc_text);
					}

					if (Comment_Entered == true && PostID_Entered == true)
					{
						for (int i = 0; i < MaxPosts; i++)
						{
							if (posts[i]->getPostID() == ID_toViewPost)
							{
								posts[i]->AddComment(comment_description, users[Current_User_Index]);
								break;
							}
						}
						Comment_Entered = false;
					}
					if (Comment_Entered1 == true)
					{
						window.draw(comment_posted_text);
					}
				}
				else if (Choice == 5)
				{
					window.draw(textBoxOutline1);
					window.draw(defaultText2);
					window.draw(line3);
					window.draw(PostIdText);

					if (PostID_Entered && ShowCommentSection == false)
					{
						window.draw(post_bg_sprite);
						Display_CurrentSystemDate(window);

						View_Post_By_ID(window, ID_toViewPost, ShowCommentSection);

					}
					if (ShowCommentSection == true)
					{
						window.draw(comment_bg_sprite);
						View_Post_By_ID(window, ID_toViewPost, ShowCommentSection);
					}

				}
				else if (Choice == 6)
				{
					window.draw(textBoxOutline1);
					window.draw(defaultText2);
					window.draw(line3);
					window.draw(PostIdText);
					if (PostID_Entered == false)
					{
						users[Current_User_Index]->DisplayTimeline_PostIDs(window);
					}

					if (PostID_Entered == true)
					{
						if (MemoryTextEntered == false)
						{
							window.draw(defaultMemoryText);
							window.draw(MemoryText_text);
						}
						else if (MemoryTextEntered == true)
						{
							users[Current_User_Index]->addMemory(MemoryText, CurrentDate, ID_toViewPost);
							MemoryTextEntered = false;
						}

						if (MemoryEntered == true)
						{
							window.draw(defaultText6);
						}
					}
				}
				else if (Choice == 7)
				{
					if (ShowCommentSection == false)
					{
						if (users[Current_User_Index]->getPost_Count() != 0)
						{
							window.draw(post_bg_sprite);
							Display_CurrentSystemDate(window);
							users[Current_User_Index]->DisplayTimeline(window, event, ShowCommentSection);
						}
						else
						{
							window.draw(TimelineDefaulText);
						}
					}
					if (ShowCommentSection == true)
					{
						window.draw(comment_bg_sprite);
						users[Current_User_Index]->DisplayTimeline(window, event, ShowCommentSection);
					}
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

					if (ShowCommentSection == false && PageID_Entered)
					{
						for (int i = 0; i < MaxPages; i++)
						{
							if (pages[i]->getPageID() == ID_toViewPage)
							{
								if (pages[i]->getPost_Count() != 0)
								{
									window.draw(post_bg_sprite);
									Display_CurrentSystemDate(window);
									View_Page_By_ID(window, event, ID_toViewPage, ShowCommentSection);
								}
								else
								{
									window.draw(TimelineDefaulText);
								}
							}
						}
					}
					else if (ShowCommentSection == true && PageID_Entered)
					{
						window.draw(comment_bg_sprite);
						View_Page_By_ID(window, event, ID_toViewPage, ShowCommentSection);
					}
				}

			}

		}


		// Display the Window
		window.display();
	}
}

// Destructor
SocialNetworkApp::~SocialNetworkApp()
{
	if (users != nullptr)
	{
		for (int i = 0; i < MaxUsers; i++)
		{
			delete users[i];
		}
		delete[] users;
	}

	if (posts != nullptr)
	{
		for (int i = 0; i < MaxPosts; i++)
		{
			delete posts[i];
		}
		delete[] posts;
	}

	if (pages != nullptr)
	{
		for (int i = 0; i < MaxPages; i++)
		{
			delete pages[i];
		}
		delete[] pages;
	}

	delete CurrentDate;
}