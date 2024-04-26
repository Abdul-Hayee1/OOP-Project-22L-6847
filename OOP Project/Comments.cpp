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
void Comment::Display_Comment()
{
	if (Commented_By_Page == nullptr)
	{
		cout << "Commented By: " << Commented_By_User->getFirstName() << " " << Commented_By_User->getLastName() << endl;
	}
	else if (Commented_By_User == nullptr)
	{
		cout << "Commented By: " << Commented_By_Page->getTitle() << endl;
	}
	cout << "Comment: " << description << endl;
}
