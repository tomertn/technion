//		commands.cpp
//********************************************
#include "commands.h"
#include "signals.h"

extern bool* is_signal_fg;
extern int* pid_to_signal;

Job::Job()
{
	_name = "";
	_PID = -1;
	_TOA = 0;
	_bg = false;
	_is_sleep = false;
}

Job::Job(string name, int PID, int TOA)
{
	_name = name;
	_PID = PID;
	_TOA = TOA;
	_bg = false;
	_is_sleep = false;
}


int update_job_list(list<Job>& jobs);
//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command strings, pointer to the fg job, bool whether it came from BG, pointer to history list
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(list<Job>& jobs, char* lineSize, char* cmdString,Job& fg_job,bool isBG, list<string>& history)
{
	char* cmd; 
	char* args[MAX_ARG];
	char* delimiters = (char*)" \t\n";
	char current_path[PATH_MAX];
	char prev_path[PATH_MAX];
	int i = 0, num_arg = 0;
	bool illegal_cmd = false; // illegal command
	
	string full_command;
    	cmd = strtok(lineSize, delimiters);
if (cmd == NULL )
		return 0; 
		full_command = cmd;
		full_command += " ";
	

   	args[0] = cmd;
	for (i=1; i<MAX_ARG; i++)
	{
		args[i] = strtok(NULL, delimiters); 
		if (args[i] != NULL)
		{
			num_arg++;
			if(num_arg != 1) full_command += " ";
			full_command += args[i];
		}
	}
/*************************************************/
// Built in Commands 
/*************************************************/
	if (!strcmp(cmd, "cd") ) 
	{
		if (num_arg != 1 )
			illegal_cmd = true;
		else
		{
			if (getcwd(current_path, sizeof(current_path)) == NULL)
			{
				cerr << "there was an error in cd" << endl;
				return 1;
			}
			if (!strcmp(args[1], "-"))
			{
				if (chdir(prev_path) == (-1)) {
					cerr << "error in prev path" << endl;
					return 1;
				}
				else
				{
					swap(current_path, prev_path);
					cout << current_path << endl;
				}
			}

			else
			{
				char temp[PATH_MAX];
				strcpy(temp, current_path);
				if (chdir(args[1]) == (-1)) {
					illegal_cmd = true;
					cerr << "error in cd" << endl;
				}
				else
				{
					strcpy(prev_path, temp);
				}
			}

			//strcpy(prev_path, current_path);
		}
	} 
	
	/*************************************************/
	else if (!strcmp(cmd, "pwd")) 
	{
		if (num_arg != 0)
		{
			illegal_cmd = true;
		}
		else
		{
			if (getcwd(current_path, sizeof(current_path)) == NULL)
			{
				cerr << "there was an error in pwd" << endl;
				return 1;
			}
			cout << current_path << endl;;
		}
	}
	
	/*************************************************/
	else if (!strcmp(cmd, "history"))
	{
		if (num_arg != 0)
		{
			illegal_cmd = true;
		}
		else
		{
			history.reverse();
			list<string>::iterator it;
			for (it = history.begin(); it != history.end(); it++)
			{
				cout << *it << endl;
			}
			history.reverse();
		}
	
	}
	/*************************************************/
	
	else if (!strcmp(cmd, "jobs")) 
	{
		if (num_arg != 0) illegal_cmd = true;
		else
		{
			if (update_job_list(jobs) == 0)
			{
				list<Job>::iterator it;
				int job_num = 1;
				for (it = jobs.begin(); it != jobs.end(); it++)
				{
					int time_t = (int)time(NULL) - it->get_TOA();
					// print jobs descreption line
					if (it->is_bg()) {
						if(!it->is_sleep())
							cout << "[" << job_num << "] " << it->get_name().c_str() << " : " << it->get_PID() << " " << time_t << " sec" << endl;
						else
							cout << "[" << job_num << "] " << it->get_name().c_str() << " : " << it->get_PID() << " " << time_t << " sec (Stopped)" << endl;
					}
					job_num++;
				}
			}
		}
	}
	/*************************************************/
	else if (!strcmp(cmd, "showpid")) 
	{
		if (num_arg != 0)
			illegal_cmd = true;
		else
		{
			cout << "smash pid is " << getpid() << endl;
		}
	}
	/*************************************************/
	else if (!strcmp(cmd, "kill")) 
	{
		if (num_arg != 2 || args[1][0]!='-')
			illegal_cmd = true;
		else
		{
			int signum = atoi(args[1]+1);
			int place = atoi(args[2]);
			int pid,cnt;
			list<Job>::iterator it;
			if (!update_job_list(jobs))
			{
				for (it = jobs.begin(), cnt = 1; it != jobs.end(); it++, cnt++)
				{
					if (cnt == place) {
						pid = it->get_PID();
						break;
						}
				}
				if (it == jobs.end())
				{
					cout << "smash error : > kill " << place << "-" << "job does not exist" << endl;
					return 1;
				}

				*is_signal_fg = false;
				*pid_to_signal =pid;	
				if (!send_signal(pid, signum))
				{
					cout << "smash error : > kill " << place << "-" << "cannot send signal" << endl;
					return 1;
				}

				//signals that have special handling in our interface:
				string signame = sigint_to_signame(signum);
				if (signame == "SIGTERM" || signame == "SIGKILL") jobs.erase(it);
				if (signame == "SIGCONT") it->set_is_sleep(false);
				if (signame == "SIGTSTP" || signame == "SIGSTOP") it->set_is_sleep(true);

			}
		}
	} 
	/*************************************************/
	else if (!strcmp(cmd, "fg"))
	{
		Job job_to_fg;
		if (num_arg != 1 && num_arg != 0)
			illegal_cmd = true;
		else
		{
			if (!update_job_list(jobs))
			{
				if (jobs.size() == 0)
				{
					cerr << "smash error: > \"fg\" : there are no jobs in bg";
					return 1;
				}

				if (num_arg == 0)
				{
					job_to_fg = jobs.back();
					jobs.pop_back();
				}
				else // num_arg==1
				{
					int cnt = 1;
					int job_num = atoi(args[1]);
					if ((int)jobs.size() < job_num || job_num < 0)
					{
						cerr << "smash error: > \"fg " << args[1] << "\" - command number doesn't exist" << endl;
						return 1;
					}
					for (list<Job>::iterator it = jobs.begin(); it != jobs.end(); cnt++)
					{
						if (cnt == job_num)
						{
							job_to_fg = *it;
							it = jobs.erase(it);
							break;
						}
						else ++it;
					}
				}

			}
		}
		if (!update_job_list(jobs))
		{
			if(job_to_fg.is_sleep())
				if (!send_signal(job_to_fg.get_PID(), SIGCONT)) return 1;
			job_to_fg.set_is_sleep(false);
			fg_job = job_to_fg;
			waitpid(fg_job.get_PID(), NULL, WUNTRACED);
			fg_job.set_PID(-1);
		}		
	}
	/*************************************************/
	else if (!strcmp(cmd, "bg")) 
	{
		Job job_to_bg;
		
		int cnt=1;
		if (num_arg != 1 && num_arg != 0)
			illegal_cmd = true;
		else if(!update_job_list(jobs))
		{
			if (jobs.size() == 0)
			{
				cout << "there are no bg jobs" << endl;
				return 1;
			}
			if (num_arg == 1)
			{
				int job_num = atoi(args[1]);
				list<Job>::iterator it = jobs.begin();
				for (; it != jobs.end(); it++,cnt++)
				{
					if (cnt == job_num)
					{
						if (send_signal(it->get_PID(), SIGCONT))
						{
							it->set_is_sleep(false);
						}
						break;
					}
				}
				if (it == jobs.end())
				{
					cout << "job to bg was not found" << endl;
					return 1;
				}
			}
			else
			{
				list<Job>::iterator it = jobs.end();
				for (; it != jobs.begin(); it--)
				{
					if (it->is_sleep())
					{
						if (send_signal(it->get_PID(), SIGCONT))
						{
							it->set_is_sleep(false);
						}
						break;
					}
				}
				if (it == jobs.begin())
				{
					if (it->is_sleep())
					{
						if (send_signal(it->get_PID(), SIGCONT))
							it->set_is_sleep(false);
					}
					else
					{
						cout << "there were no any sleep jobs at the jobs bg list" << endl;
						return 1;
					}
				}
			}
		}
	}
	/*************************************************/
	else if (!strcmp(cmd, "quit"))
	{
		if (num_arg != 1 && num_arg != 0)
			illegal_cmd = true;
		else
		{
			if (num_arg == 0)
			{
				exit(0);
			}
			else //num_arg == 1
			{
				if (!update_job_list(jobs))
				{
					if (strcmp(args[1], "kill")) //args[1]!="kill"
						illegal_cmd = true;
					else
					{
						list<Job>::iterator it = jobs.begin();
						int job_num =1;
						for (; it != jobs.end(); it++, job_num++)
						{
							if (waitpid(it->get_PID(), NULL, WNOHANG) != 0) continue;
							cout << "[" << job_num << "] " << it->get_name().c_str() << " - Sending SIGTERM... " << endl;
							if (!send_signal(it->get_PID(), SIGTERM))
							{
								cout << "there was an error in quit" << endl;
							}
							sleep(5);
							if (waitpid(it->get_PID(), NULL, WNOHANG) == 0)//still alive
							{
								cout << " (5 sec passed) Sending SIGKILL... " << endl;
								if (!send_signal(it->get_PID(), SIGKILL))
								{
									cout << "there was an error in quit" << endl;
									return 1;
								}
							}
								cout << "Done." << endl;
						}
						exit(0);
					}
				}
			}
		}
	} 
	/*************************************************/
	else if (!strcmp(cmd, "mv"))
	{
		if (num_arg !=2)
			illegal_cmd = true;
		else
		{
			if (rename(args[1], args[2]) == 0)
			{
				printf("%s has been renamed to %s\n", args[1], args[2]);
			}
			else
			{
				cerr << "there were an error in mv" << endl;
			}
		}
	}
	/*************************************************/
	else // external command
	{
 		ExeExternal(args, cmdString,fg_job,isBG);
	 	return 0;
	}
	if (illegal_cmd == true)
	{
		printf("smash error: > \"%s\"\n", cmdString);
		return 1;
	}
	
    return 0;
}
//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string, pointer to jobs list, bool whether it came from BG
// Returns: void
//**************************************************************************************
void ExeExternal(char *args[MAX_ARG], char* cmdString,Job& fg_job, bool isBG)
{
	int pID;
    	switch(pID = fork()) 
	{
    		case -1: 
				//error
				cerr << "an error occured in fork of external cmd" << endl;
        	case 0 :
                	// Child Process
               	setpgrp();
				execvp(args[0], args);
				cerr << "an error occured in exec" << endl;

				exit(0);
			default:
				//father process
				if (!isBG)
				{
					fg_job.set_bg(false);
					fg_job.set_is_sleep(false);
					fg_job.set_name(args[0]);
					fg_job.set_PID(pID);
					fg_job.set_TOA((int)time(NULL));
				}
				waitpid(pID, NULL, WUNTRACED);
				if (!isBG) fg_job.set_PID(-1);
	}
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char* lineSize)
{

    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
    {
		cout << "the shell does not take care of complicated commands" << endl;
		return 0;
	} 
	return -1;
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs, pointer to the fg job, pointer to history list
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, list<Job>& jobs, char* cmdString, Job& fg_job,list<string>& history)
{


	char* delimiters = (char*)" \t\n";

	Job job_to_bg;
	if (lineSize[strlen(lineSize)-2] == '&')
	{
		lineSize[strlen(lineSize)-2] = '\0';
		//execute a in the background
		int pid;
		update_job_list(jobs);
		pid = fork();
		switch (pid)
		{
		case -1: //error
			cerr << "there was an error in fork" << endl;
			return -1;
		case 0:  // child process
			setpgrp();
			exit(ExeCmd(jobs, lineSize, cmdString, fg_job,true,history));
			exit(1); //exeCMD was failed
		default: //father process
			job_to_bg.set_TOA((int)time(NULL));
			job_to_bg.set_PID(pid);
			job_to_bg.set_name((strtok(lineSize, delimiters)));
			job_to_bg.set_is_sleep(false);
			job_to_bg.set_bg(true);
			jobs.push_back(job_to_bg);
			return 0;
		}
	}
	return -1;
}


//**************************************************************************************
// function name: update_job_list
// Description: collecting Zombies and update the job list
// Parameters:  pointer to jobs list
// Returns: 0- Success 1- failure
//**************************************************************************************

int update_job_list(list<Job>& jobs)
{
	list<Job>::iterator it;
	for (it = jobs.begin(); it != jobs.end();)
	{
		int temp = waitpid(it->get_PID(), NULL, WNOHANG);
		if (temp == -1)
		{
			cerr << "error in waitpid" << endl;
			return 1;
		}
		if (temp != 0) {
			jobs.erase(it);
			it = jobs.begin();
		}
		else it++; 
	}
	return 0;
}
