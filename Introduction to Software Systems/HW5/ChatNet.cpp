#include <iostream>
#include <stdexcept>
#include "Conversation.h"
#include "ChatNet.h"
#include "User.h"

#define NO_ACTIVE_USER "No User"

using namespace std;



bool operator<(const MySharedPtr<User>& user1, const MySharedPtr<User>& user2) { return  user1->getName()< user2->getName(); }

// Interface
void ChatNet::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES);
	if (cmdLineTokens[0] == "Login" && cmdLineTokens.size() == 3) // Login
	{
		bool flag = false;
		for (auto itr = setOfUsers_.begin(); itr != setOfUsers_.end(); itr++)  {
			if (itr->get()->getName() == cmdLineTokens[1]) {
				flag = true;
				if (itr->get()->getPassword() != cmdLineTokens[2])
					cout << WRONG_PASSWORD;
				else
				{
					activeUsrName_ = cmdLineTokens[1];
					objectsStuck_.push(MySharedPtr<ActiveObj>(new ActiveObj(itr->get())));
					objectsStuck_.top().get()->Preview(activeUsrName_);
				}
			}
		}
		if (!flag) cout << USER_DOES_NOT_EXIST;
	}

	else if (cmdLineTokens[0] == "New" && cmdLineTokens.size() == 3) // New
	{
		for (auto itr = setOfUsers_.begin(); itr != setOfUsers_.end(); itr++) {
			if (itr->get()->getName() == cmdLineTokens[1]) {
				cout << USER_ALREADY_EXISTS;
				return;
			}
		}
		MySharedPtr<User> pUser(new User(cmdLineTokens[1], cmdLineTokens[2]));
		setOfUsers_.insert(pUser);
	}


	else if (cmdLineTokens[0] == "Exit" && cmdLineTokens.size() == 1) // Exit
	{
		throw BackSignal();
	}
	else if(cmdLineTokens.size() == 0){ throw BackSignal(); }
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}

void ChatNet::Do(string cmd)
{
	try
	{
		// Call Do method of the currently active object.
		// When using stack (from STL) this could be like something like the following line:
		
		objectsStuck_.top()->Do(cmd, activeUsrName_);
	}
	catch (GoBack goBack)
	{
		objectsStuck_.pop();
		objectsStuck_.top()->Preview(activeUsrName_);
	}
	catch (makeNewConversation makeNewConvers)
	{
		// check whether all the names exist
		bool flag = false;
		for (auto itr= makeNewConvers.namesOfMembers.begin(); itr != makeNewConvers.namesOfMembers.end(); itr++) {
			for (auto itr2 = setOfUsers_.begin(); itr2 != setOfUsers_.end(); itr2++) {
				if (itr2->get()->getName() == *itr) { flag = true; }
			}
			if (!flag) {
				cout << CONVERSATION_FAIL_NO_USER; return;
			}
			flag = false;
		}
		MySharedPtr<Conversation> pConversation(new Conversation());
		pConversation->updateTime();
		for (auto itr = makeNewConvers.namesOfMembers.begin(); itr != makeNewConvers.namesOfMembers.end(); itr++) {
			for (auto itr2 = setOfUsers_.begin(); itr2 != setOfUsers_.end(); itr2++) {
				if (itr2->get()->getName() == *itr) { pConversation->addParticipant(*itr);  }//add all Participant to  Conversation
			}
		}
		for (auto itr = makeNewConvers.namesOfMembers.begin(); itr != makeNewConvers.namesOfMembers.end(); itr++) {
			for (auto itr2 = setOfUsers_.begin(); itr2 != setOfUsers_.end(); itr2++) {
				if (itr2->get()->getName() == *itr) {
					itr2->get()->getMessageBox()->addConversations(pConversation);
					//pConversation->IsRead(itr);
				}
			}

		}
		// more catch phrases

	}

	catch (OpenAConversation open)
	{
		objectsStuck_.push(MySharedPtr<ActiveObj>(new ActiveObj(open.getPtr().get())));
		objectsStuck_.top().get()->Preview(activeUsrName_);
	}

	//catch (OpenAConversation deleteCon) {} think that we dont need this

	catch (SearchName search) {
		BOOL found = FALSE;
		set<MySharedPtr<User>>::iterator itr = setOfUsers_.begin();
		for (; itr != setOfUsers_.end(); itr++) {
			if (itr->get()->getName().find(search.getPtr()) != string::npos) {
				if (found == FALSE) {
					cout << SEARCH_FOUND_TITLE;
					found = TRUE;
				}
				cout << itr->get()->getName() << endl;
			}
		}
		if (found == FALSE) {
			cout << SEARCH_NOT_FOUND_TITLE;
		}
	}

	catch (OpenAMessages open) {
		objectsStuck_.push(MySharedPtr<ActiveObj>(new ActiveObj(open.getPtr().get())));
		objectsStuck_.top().get()->Preview(activeUsrName_);
	}
	catch (LogOut logOut) {
		objectsStuck_.pop();
		activeUsrName_ = NO_ACTIVE_USER;
		objectsStuck_.top()->Preview(activeUsrName_);
	}
	catch (NewAdmin newAdmin) {
		for (auto itr = setOfUsers_.begin(); itr != setOfUsers_.end(); itr++) {
			if (itr->get()->getName() == newAdmin.getName()) {
				cout << USER_ALREADY_EXISTS;
				return;
			}
		}
		MySharedPtr<User> pAdmin(new Admin(newAdmin.getName(), newAdmin.getPass()));
		setOfUsers_.insert(pAdmin);
	}
	catch (DeleteUser deleteUser) {
		for (auto itr = setOfUsers_.begin(); itr != setOfUsers_.end(); itr++) {
			if (itr->get()->getName() == deleteUser.getName()) {
				if (itr->get()->getType() == 1) {
					cout << REMOVE_USER_FAIL;
					return;
				}
				else {
					list<MySharedPtr<Conversation>>::iterator itr3 = itr->get()->getMessageBox()->getList().begin();
					while (!itr->get()->getMessageBox()->getList().empty()) {
						itr->get()->getMessageBox()->getList().begin()->get()->removeParticipant(deleteUser.getName());
						itr->get()->getMessageBox()->getList().pop_front();

					}
					/*for (; itr3 != itr->get()->getMessageBox()->getList().end(); itr3++) {
						(*itr3)->removeParticipant(deleteUser.getName());//remove user from all convs
						itr->get()->getMessageBox()->getList().push_back(*itr3);//remove convs from box
					}*/
					setOfUsers_.erase(itr);
					return;

				}
			}
		}
		cout << USER_DOES_NOT_EXIST;
	}
}



void ChatNet::Preview(string activeUsrName)
{
	cout << "Welcome to " << networkName_ << "." << endl;
}


void ChatNet::Help() const
{
	cout << "Login <user name> <password>" << endl;
	cout << "New <user name> <password>" << endl;
	cout << "Exit" << endl;
}

ChatNet::ChatNet(const string& networkName, const string& adminName, const string& adminPass) : networkName_(networkName),activeUsrName_(NO_ACTIVE_USER) {
	
	setOfUsers_.insert(MySharedPtr<User>(new Admin(adminName, adminPass)));
	objectsStuck_.push(MySharedPtr<ActiveObj>(new ActiveObj(this)));
	Preview(activeUsrName_);
}