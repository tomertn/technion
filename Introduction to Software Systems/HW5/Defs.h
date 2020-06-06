#ifndef _DEFS_H_
#define _DEFS_H_
#include <string>
#include <vector>
using namespace std;

#define BLANK_SPACES " \t\n\r"

class ObjectInterface;


// ------------------------------- OUTPUT ------------------------------- //
// Outputs
#define INVALID_INPUT "Invalid Input! Type Help for possible Inputs" << endl

#define USER_ALREADY_EXISTS "User already exists" << endl
#define USER_DOES_NOT_EXIST "User doesn't exist" << endl
#define WRONG_PASSWORD "Wrong password" << endl

#define CONVERSATION_FAIL_NO_USER "Failed to create conversation - some users don't exist" << endl
#define CONVERSATION_FAIL_USER_REPETITION "Failed to create conversation - User repetitions found in participants list" << endl
#define INVALID_CONVERSATION_NUMBER "Invalid conversation number" << endl
#define REMOVE_USER_FAIL "Failed to remove user - User is an administrator" << endl

#define USER_PREVIEW_PART1 "Hi " << name_ << ", "
#define USER_PREVIEW_PART2_NO_MESSAGES "you have no new messages." << endl
#define USER_PREVIEW_PART2_NEW_MESSAGES "you have new messages." << endl

#define COMMA_SPACE ", "
#define PARTICIPANT_READ_STATUS " " << (IsRead(itr->first) ? "(read)" : "(unread)")
#define NOT_IN_THE_CONVERSATION " is not part of the conversation" << endl
#define PARTICIPANTS_TITLE "Participants: "

#define SEARCH_FOUND_TITLE "Users matching the pattern are:" << endl
#define SEARCH_NOT_FOUND_TITLE "No user matches the pattern" << endl

// ------------------------------- SIGNALS ------------------------------- //
// ActiveObj
class ActiveObj {
public:
	ActiveObj(ObjectInterface* objPtr) : objPtr_(objPtr) {}
	void Do(string cmd, string activeUsrName);
	void Preview(string usrName);
private:
	ObjectInterface* objPtr_;
};

// BackSignal
class BackSignal {
};



// ------------------------------- Functions ------------------------------- //
vector<string> StringSplit(const string& str, const char* delims, int maxNumSeparations = -1);




#endif
