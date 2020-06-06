#ifndef _SOCIAL_NET_H_
#define _SOCIAL_NET_H_
#include "User.h"
#include <stack>
#include "MySharedPtr.h"
#include "Defs.h"
#include "ObjectInterface.h"



class ChatNet : public ObjectInterface {
public:
	ChatNet(const string& networkName, const string& adminName, const string& adminPass);
	void Preview(string activeUsrName);
	void Do(string cmd);
	void VrtDo(string cmdLine, string activeUsrName);
	void Help() const;


private:
	string networkName_;
	string activeUsrName_;
	stack<MySharedPtr<ActiveObj>> objectsStuck_;
	set<MySharedPtr<User>> setOfUsers_;

};


#endif

