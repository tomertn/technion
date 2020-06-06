#include "Office.H"
#include "Class.H"
#include "Child.H"
#include "Teacher.H"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int stringToInt(const string s) {
  istringstream istr(s);
  int i = 0;
  istr >> i;
  return i;
}

double stringToDouble(const string s1,const string s2) {
  
  istringstream istr1(s1);
  istringstream istr2(s2);
  int i; //integer part
  int j; //fraction part
  double a = 0;
  istr1 >> i;
  istr2 >> j;
  a = double(i)+double(j)/1000; //assuming fraction part is alwways 3 digits
  return a;
}

vector<string> tokenize(string line, const char* delim) {
	unsigned int i, j; 
	vector<string> tokens;
	while (!line.empty()) {
		i = line.find_first_not_of(delim);
		j = line.find_first_of(delim, i+1);
		tokens.push_back(line.substr(i, j-i));
		if (j > line.size()-1)
			line = "";
		else
			line = line.substr(j+1,line.size()-j-1);
	}
	return tokens;
}

	/*int o;
	Office a;
	a.addClass(70, 2, 20, 4);
	a.addClass(70, 3, 21, 4);
	Child jeremy("jeremy", 20, "1"), roee("roee", 21, "2"), amir("amir", 20, "0544444444"), noy("noy", 20, "4");
	Teacher tomer("tomer", 23, 4), shalev("shalev", 24, 5), razi("razi", 24, 5);
	a.addChildOffice(jeremy);
	a.addTeacherOffice(tomer);
	a.addChildOffice(roee);
	a.addChildOffice(amir);
	a.sickChildMark("amir");
	a.addChildOffice(jeremy);
	a.removeChildOffice("amir");
	a.addTeacherOffice(shalev);
	a.addChildOffice(roee);
	a.addChildOffice(jeremy);
	a.addChildOffice(amir);
	a.addTeacherOffice(razi);
	a.removeChildOffice("amir");
	a.removeChildOffice("jeremy");
	a.removeTeacherOffice("tomer");
	a.removeTeacherOffice("razi");
	a.addTeacherOffice(razi);
	a.print();
	cin >> o;
	
	Child jeremy("jeremy", 20, "1"), roee("roee", 20, "2"), amir("amir", 20, "3"), noy("noy",20,"4");
	Teacher tomer("tomer", 23, 4), shalev("shalev", 24, 5);
	Class alef(6, 70, 2, 20, 4);
	alef.addTeacher(tomer);
	alef.addTeacher(shalev);
	alef.addChild(jeremy);
	alef.addChild(noy);
	roee.setSick();
	alef.addChild(roee);
	alef.addChild(amir);
	alef.occupiedOn();
	alef.removeTeacher("tomer");
	alef.removeChild("jeremy");
	alef.addChild(noy);
	alef.print();
	int a;
	cin >> a;


	*/

	void printError(vector<string> tokensToPrint)
	{
		cerr << "Failed - " << tokensToPrint[0];
		unsigned int i = 1;
		for (i = 1; i < tokensToPrint.size(); i++)
		{
			cerr << " " << tokensToPrint[i];
		}
		cerr << endl;
	}

	int main() {

		Office KG_Office; //KinderGarten Office
		
		/* 
						  //
		Office a;
		a.addClass(70, 2, 20, 4);
		a.addClass(70, 3, 21, 4);
		Child jeremy("jeremy", 20, "1"), roee("roee", 21, "2"), amir("amir", 20, "0544444444"), noy("noy", 20, "4");
		Teacher tomer("tomer", 23, 4), shalev("shalev", 24, 5), razi("razi", 24, 5);
		a.addChildOffice(jeremy);
		a.addTeacherOffice(tomer);
		a.addChildOffice(roee);
		a.addChildOffice(amir);
		a.sickChildMark("amir");
		a.print();
		string s = "a";
		cout << s.compare("b");
		int b;
		cin >> b; 
		//
		*/
		const char* delims = " \t\n";
		vector<string> tokens;
		string line;
		unsigned int lineNumber = 1;

		while (!cin.eof()) {
			getline(cin, line);
			tokens = tokenize(line, delims);
			int lengthOfWords = tokens.size();
			if (tokens.size() == 0) { //empty line
				continue;
			}

			if (tokens[0] == "addClass")
			{
				if (lengthOfWords != 5)
				{
					printError(tokens);
					lineNumber++;
					continue;
				}
				vector<string> intAndFloat = tokenize(tokens[2], ".");
				if (stringToInt(tokens[1]) <= 0 || stringToDouble(intAndFloat[0], intAndFloat[1]) <= 0 || stringToInt(tokens[3]) <= 0 || stringToInt(tokens[4]) <= 0)
				{
					printError(tokens);
				}
				else if (!KG_Office.addClass(stringToInt(tokens[1]), stringToDouble(intAndFloat[0], intAndFloat[1]), stringToInt(tokens[4]), stringToInt(tokens[3])))
				{
					printError(tokens);
				}

			}

			if (tokens[0] == "removeClass")
			{
				if (lengthOfWords != 2)
				{
					printError(tokens);
				}
				else if (stringToInt(tokens[1]) <= 0)
				{
					printError(tokens);
				}
				else if (KG_Office.removeClass(stringToInt(tokens[1]))==FAILURE)
				{
					printError(tokens);
				}
			}

			if (tokens[0] == "addChild")
			{
				if (lengthOfWords != 4)
				{
					printError(tokens);
					lineNumber++;
					continue;
				}
				Child new_child(tokens[2], stringToInt(tokens[1]), tokens[3]);
				if (stringToInt(tokens[1]) <= 0)
				{
					printError(tokens);
				}
				else if (KG_Office.addChildOffice(new_child)==FAILURE)
				{
					printError(tokens);
				}
			}

			if (tokens[0] == "addTeacher")
			{
				if (lengthOfWords != 4)
				{
					printError(tokens);
					lineNumber++;
					continue;
				}
				Teacher new_teacher(tokens[2], stringToInt(tokens[1]), stringToInt(tokens[3]));
				if (stringToInt(tokens[1]) <= 0 || stringToInt(tokens[3]) <= 0)
				{
					printError(tokens);
				}
				else if (KG_Office.addTeacherOffice(new_teacher)==FAILURE)
				{
					printError(tokens);
				}
			}

			if (tokens[0] == "removeChild")
			{
				if (lengthOfWords != 2)
				{
					printError(tokens);
				}
				else if (KG_Office.removeChildOffice(tokens[1])==FAILURE)
				{
					printError(tokens);
				}
			}

			if (tokens[0] == "removeTeacher")
			{
				if (lengthOfWords != 2)
				{
					printError(tokens);
				}
				else if (KG_Office.removeTeacherOffice(tokens[1])==FAILURE)
				{
					printError(tokens);
				}
			}

			if (tokens[0] == "PrintKindergarten")
			{
				if (lengthOfWords != 1)
				{
					printError(tokens);
				}
				else
				{
					KG_Office.print();
				}
			}
			if (tokens[0] == "sickChild")
			{
				if (lengthOfWords != 2)
				{
					printError(tokens);
				}
				else if (KG_Office.sickChildMark(tokens[1]) == FAILURE)
				{
					//cout << tokens[1] << endl; למה??? שעה לקחלי להבין מה הבעיה
					printError(tokens);
				}
			}

			lineNumber++;
		}


		return 0;
	};
