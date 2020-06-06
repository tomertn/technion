#include<iostream>
#include "User.h"

using namespace std;
// ------------------------------- User ------------------------------- //



// Interface

void User::Preview(string activeUsrName)
{
	bool flage = false;
		cout << USER_PREVIEW_PART1;
		for (auto itr = pMessageBox_->getList().begin(); itr != pMessageBox_->getList().end();itr++) {
				if (!itr->get()->IsRead(activeUsrName)) { flage = true; }
			}
		if (!flage) {  cout << USER_PREVIEW_PART2_NO_MESSAGES;  }
		else{ cout << USER_PREVIEW_PART2_NEW_MESSAGES; }
}
void User::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "Messages" && cmdLineTokens.size() == 1) // Messages
	{
		OpenAMessages open(pMessageBox_);
		throw(open);
	}
	else if (cmdLineTokens[0] == "Logout" && cmdLineTokens.size() == 1) // Logout
	{
		LogOut logOut;
		throw (logOut);
	}
	else if (cmdLineTokens.size() == 0) { throw BackSignal(); }
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}





void User::Help() const
{
	cout << "Messages" << endl;
	cout << "Logout" << endl;
}









// ------------------------------- Admin ------------------------------- //
void Admin::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() == 3) // New
	{
		NewAdmin newAdmin(cmdLineTokens[1], cmdLineTokens[2]);
		throw (newAdmin);
	}
	else if (cmdLineTokens[0] == "Delete" && cmdLineTokens.size() == 2) // Delete
	{
		DeleteUser deleteUser(cmdLineTokens[1]);
		throw (deleteUser);
	}
	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		SearchName search(cmdLineTokens[1]);
		throw(search);
	}
	else // User command
	{
		this->User::VrtDo(cmdLine, activeUsrName);
	}
}

void Admin::Help() const
{
	cout << "New <admin name> <admin password>" << endl;
	cout << "Delete <user name>" << endl;
	cout << "Search <partial user name>" << endl;
	User::Help(); // User commands
}