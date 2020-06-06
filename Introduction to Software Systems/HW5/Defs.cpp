#include "Defs.h"
#include "ObjectInterface.h"

// ------------------------------- SIGNALS ------------------------------- //
void ActiveObj::Do(string cmd, string activeUsrName)
{
	objPtr_->Do(cmd, activeUsrName);
}

void ActiveObj::Preview(string usrName)
{
	objPtr_->Preview(usrName);
}



// ------------------------------- Functions ------------------------------- //
vector<string> StringSplit(const string& str, const char* delims, int maxNumSeparations)
{
	vector<string> split;
	size_t startPos = str.find_first_not_of(delims);
	if (startPos == string::npos)
	{
		split.push_back("");
		return split;
	}
	size_t endPos = str.find_first_of(delims, startPos);
	if (endPos == string::npos)
	{
		split.push_back(str.substr(startPos, string::npos));
		return split;
	}
	while (startPos != string::npos && (maxNumSeparations == -1 || (int)split.size() < maxNumSeparations))
	{
		split.push_back(str.substr(startPos, endPos - startPos));
		if (endPos == string::npos)
			startPos = string::npos;
		else
			startPos = str.find_first_not_of(delims, endPos);
		if (startPos != string::npos)
			endPos = str.find_first_of(delims, startPos);
	}
	if (startPos != string::npos)
		split.push_back(str.substr(startPos, string::npos));
	return split;
}