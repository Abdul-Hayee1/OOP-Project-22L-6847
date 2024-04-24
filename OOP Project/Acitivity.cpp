#include "Activity.h"

// Constructor
Activity::Activity() 
{
	Type = 0;
	Value = "";
}

Activity::Activity(int type, string value) : Type(type), Value(value) {}

Activity::Activity(const Activity& obj)
{
	Type = obj.Type;
	Value = obj.Value;
}



// Functions
void Activity::PrintActivity()
{
	if (Type == 1)
	{
		cout << "is feeling ";
	}
	else if (Type == 2)
	{
		cout << "is thinking about ";
	}
	else if (Type == 3)
	{
		cout << "is Making ";
	}
	else if (Type == 4)
	{
		cout << "is celebrating ";
	}

	cout << Value << "." << endl;
}

// Destructor
Activity::~Activity() {}