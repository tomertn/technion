#include "MessageBox.h"


using namespace std;



//Interface

bool compareConversations(MySharedPtr<Conversation> first, MySharedPtr<Conversation> second) {
	return (first->getTime() > second->getTime());
}


void MessageBox::VrtDo(string cmd, string activeUsrName)
{
	listOfPConversations.sort(compareConversations);
	//size_t idx;

	vector<string> cmdLineTokens = StringSplit(cmd, BLANK_SPACES);
	if (cmdLineTokens[0] == "New" && cmdLineTokens.size() > 1) // New
	{
		// check repetitions
		for (unsigned int i = 1; i < cmdLineTokens.size(); i++) {   
			for (unsigned int j = i+1; j < cmdLineTokens.size(); j++) {
				if (i == j) continue;
				if (cmdLineTokens[i] == cmdLineTokens[j]) {
					cout << CONVERSATION_FAIL_USER_REPETITION;
					return;
				}
			}
		}
		for (unsigned int k = 1; k < cmdLineTokens.size(); k++) {
			if (cmdLineTokens[k] == activeUsrName) {
				cout << CONVERSATION_FAIL_USER_REPETITION;
				return;
			}
		}

		makeNewConversation makeNewConvers;
		for (unsigned int i = 1; i < cmdLineTokens.size(); i++) {
			makeNewConvers.addMemberToVecotr(cmdLineTokens[i]);
		}
		makeNewConvers.addMemberToVecotr(activeUsrName);
		throw(makeNewConvers);
	}

	else if (cmdLineTokens[0] == "Open" && cmdLineTokens.size() == 2) // Open
	{
		
		//check if num
		for (int i = 0; cmdLineTokens[1][i] != 0; i++)
		{
			if (cmdLineTokens[1][i]<'0' || cmdLineTokens[1][i] > '9') {
				cout << INVALID_CONVERSATION_NUMBER; return;
			}
		}

		int number = 0;
		for (int i = 0; cmdLineTokens[1][i] != 0; i++)
		{
			number = number * 10 + ((int)cmdLineTokens[1][i] - (int)'0');
		}

			//check range
		
		if (number < 1 || (unsigned)(number) > listOfPConversations.size()) {
			cout << INVALID_CONVERSATION_NUMBER;
			return;
		}
			int i = 1;
			auto itr = listOfPConversations.begin();
			for (; i < number; i++ ) {
				++itr;
			}

			//MySharedPtr<Conversation> pConvers(*itr);//תכלס אפשר להחליף בשורה הבאה את הפוניטר באיטרטור
			OpenAConversation open(*itr);
			throw(open);
		

		
		
	}


	else if (cmdLineTokens[0] == "Delete" && cmdLineTokens.size() == 2) // Delete
	{
		//check if num
		for (int i = 0; cmdLineTokens[1][i] != 0; i++)
		{
			if (cmdLineTokens[1][i]<'0' || cmdLineTokens[1][i] > '9') {
				cout << INVALID_CONVERSATION_NUMBER; return;
			}
		}

		int number = 0;
		for (int i = 0; cmdLineTokens[1][i] != 0; i++)
		{
			number = number * 10 + ((int)cmdLineTokens[1][i] - (int)'0');
		}

		//check range

		if (number < 1 || (unsigned)(number) > listOfPConversations.size()) {
			cout << INVALID_CONVERSATION_NUMBER;
			return;
		}
		//delete
		int num = 0;
		for (int i = 0; cmdLineTokens[1][i] != 0; i++)
		{
			num = num * 10 + ((int)cmdLineTokens[1][i] - (int)'0');
		}
		list<MySharedPtr<Conversation>>::iterator itr = listOfPConversations.begin();
		for (int i = 1; i < num; i++) {
			itr++;
		}
		(*itr)->removeParticipant(activeUsrName);
		this->listOfPConversations.erase(itr);
		//MySharedPtr<Conversation> pConvers(*itr);
		//DeleteConsFromBox deleteCon(pConvers);
		//throw(deleteCon);
		return;
	}


	else if (cmdLineTokens[0] == "Search" && cmdLineTokens.size() == 2) // Search
	{
		SearchName search(cmdLineTokens[1]);
		throw(search);
	}
	else if (cmdLineTokens[0] == "Back") // Back
	{
		GoBack goBack;
		throw (goBack);
	}
	else if (cmdLineTokens.size() == 0) { throw BackSignal(); }
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}


void MessageBox::Preview(string activeUsrName)
{
	listOfPConversations.sort(compareConversations);
	int count = 1;
	if (listOfPConversations.empty()) {
		cout << "No conversations" << endl;
		return;
	}
	else {
		cout << "Conversations:" << endl;
		listOfPConversations.sort(compareConversations);
		for (auto itr = listOfPConversations.begin(); itr != listOfPConversations.end(); itr++)
		{
			cout << count << ") ";
			if (!(*itr)->IsRead(activeUsrName))
				cout << "(UNREAD) ";
			cout << "Participants: ";
			(*itr)->DisplayParticipants();
			++count;
		}
	}
}


void MessageBox::Help() const
{
	cout << "New <user names separated by spaces>" << endl;
	cout << "Open <conversation number>" << endl;
	cout << "Delete <conversation number>" << endl;
	cout << "Search <partial user name>" << endl;
	cout << "Back" << endl;
}

int MessageBox::getSize() const {
	return listOfPConversations.size();
}

/*void  MessageBox::removeConversations(MySharedPtr<Conversation> conversation) {
	list<MySharedPtr<Conversation>>::iterator itr = listOfPConversations.begin();
	for (; itr != listOfPConversations.end(); itr++) {
	listOfPConversations;

}
MessageBox::~MessageBox() {
	list<MySharedPtr<Conversation>>::iterator itr = listOfPConversations.begin();
	for (; itr != listOfPConversations.end(); itr++) {
		listOfPConversations.push_back(*itr);
	}

}*/