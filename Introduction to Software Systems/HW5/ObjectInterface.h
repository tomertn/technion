#ifndef _OBJ_INTERFACE_H_
#define _OBJ_INTERFACE_H_

#include <string>
#include <vector>
#include "Defs.h"

using namespace std;

class ObjectInterface {
public:
	virtual ~ObjectInterface() {}
	virtual void VrtDo(string cmd, string activeUsrName) = 0;
	virtual void Preview(string activeUsrName) = 0;
	virtual void Help() const = 0;
	void Do(string cmd, string activeUsrName)
	{
		vector<string> split = StringSplit(cmd, BLANK_SPACES, 1);
		if (split[0] == "Help" && split.size() == 1) // Help
			this->Help();
		else
			this->VrtDo(cmd, activeUsrName);
	}
};


#endif
