#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <list>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream> 
#include<stdbool.h>
#define MAX_LINE_SIZE 80
#define MAX_ARG 20
#define PATH_MAX 4096

using namespace std;


class Job {
public:
	Job();
	Job(string name, int PID, int TOA);
	string get_name() { return _name; }
	void set_name(string name) { _name = name; }
	int get_PID() { return _PID; }
	void set_PID(const int i) { _PID = i; }
	int get_TOA() { return _TOA; }
	void set_TOA(int i) { _TOA = i; }
	bool is_bg() { return _bg; }
	void set_bg(bool i) { _bg = i; }
	void set_is_sleep(bool f) { _is_sleep = f; }
	bool is_sleep() { return _is_sleep; }
	
private:
	string _name;
	int _PID;
	int	_TOA; //time of arrival
	bool _bg; // true if runs in the background
	bool _is_sleep;
};
//typedef enum { false , true } bool;
int ExeComp(char* lineSize);
int BgCmd(char* lineSize, list<Job>& jobs, char* cmdString, Job& fg_job, list<string>& history);
int ExeCmd(list<Job>& jobs, char* lineSize, char* cmdString,Job& fg_proc, bool isBG,list<string>& history);
void ExeExternal(char *args[MAX_ARG], char* cmdString, Job& fg_job, bool isBG);
#endif

