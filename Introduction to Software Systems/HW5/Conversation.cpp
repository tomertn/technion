#include <iostream>
#include "Defs.h"
#include "Conversation.h"
#include "User.h"




//Interface
void Conversation::DisplayParticipants() const {
	for (auto itr = readStatus_.begin(); itr != readStatus_.end();  ) {
		cout << (*itr).first ;
		if ( (++itr)  != readStatus_.end()) cout << COMMA_SPACE;
	}
	cout << endl;
} 

void Conversation::VrtDo(string cmdLine, string activeUsrName)
{
	vector<string> cmdLineTokens = StringSplit(cmdLine, BLANK_SPACES, 1);
	if (cmdLineTokens[0] == "Write" && cmdLineTokens.size() == 2) // Write
	{
		set<string>::iterator it = users_.find(activeUsrName);
		if (it == users_.end()) {
			cout << activeUsrName << NOT_IN_THE_CONVERSATION;
			return;
		}
		Message msgToInsert(activeUsrName, cmdLineTokens[1] );
		messages_.push_back(msgToInsert);
		time_ = chrono::system_clock::now();
		map<string, ConversationStatus>::iterator itr = readStatus_.begin();
		for (; itr != readStatus_.end(); itr++) {
			itr->second = UNREAD;
			if (itr->first == activeUsrName) itr->second = READ;
		}
	}

	else if (cmdLineTokens[0] == "Back" && cmdLineTokens.size() == 1) // Back
	{
		GoBack goBack;
		throw (goBack);
	}
	else if (cmdLineTokens.size() == 0) { throw BackSignal(); }
	else // INVALID_INPUT
		cout << INVALID_INPUT;
}


void Conversation::Preview(string activeUsrName)
{
	set<string>::iterator it = users_.find(activeUsrName);
	if (it != users_.end()) {
		map<string, ConversationStatus>::iterator itr = readStatus_.find(activeUsrName);
		itr->second = READ;
		cout << PARTICIPANTS_TITLE;
		for (itr = readStatus_.begin(); itr != readStatus_.end(); ) {
			cout << itr->first << PARTICIPANT_READ_STATUS;
			if (++itr != readStatus_.end()) cout << COMMA_SPACE;
		}
		cout << endl;
		unsigned int i = 0;
		for (; i < messages_.size(); i++)
			messages_[i].Print();
	}
	else cout << activeUsrName << NOT_IN_THE_CONVERSATION;
}


void Conversation::Help() const
{
	cout << "Write <message>" << endl;
	cout << "Back" << endl;
}

bool Conversation::IsRead(string name) {
	map<string, ConversationStatus>::iterator Mapitr = readStatus_.find(name);
	if (Mapitr != readStatus_.end()) {
		if (Mapitr->second == READ)
			return true;
	}
	return false;
}

/*void Conversation::markAsRead(string name) {
	map<string, ConversationStatus>::iterator Mapitr = readStatus_.find(name);
	if (Mapitr != readStatus_.end()) {
		 Mapitr->second
	}
	return;
}*/
void  Conversation::addParticipant(string name) {
	if (users_.find(name) != users_.end()) return;
	users_.insert(name);
	readStatus_.insert(pair<string, ConversationStatus>(name, READ));
}

void  Conversation::updateTime() {
	time_ = chrono::system_clock::now();
}

void  Conversation::removeParticipant(string name) {
	if (users_.find(name) == users_.end()) return;
	users_.erase(users_.find(name));
	readStatus_.erase(name);
}