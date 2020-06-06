/*	smash.c
main file. This file contains the main function of smash
*******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "commands.h"
#include "signals.h"
#define MAX_LINE_SIZE 80
#define MAXARGS 20

char* L_Fg_Cmd;
list<string> history; //represents CMDs history
 list<Job> jobs; //This represents the list of jobs.
Job fg_job;//(NULL,-1,-1);
char lineSize[MAX_LINE_SIZE]; 
bool a=false;
int b=0;
 bool* is_signal_fg= &a;
int* pid_to_signal= &b;

struct sigaction ctrlC;
struct sigaction ctrlZ;


//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{


	memset(&ctrlZ, 0, sizeof(ctrlZ));
   	
	sigset_t mask_set1, mask_set2;
	sigfillset(&mask_set1);
	ctrlC.sa_mask = mask_set1;
	ctrlC.sa_flags = 0;
	ctrlC.sa_handler = &catch_SIGINT;
	if(sigaction(SIGINT, &ctrlC, NULL))
	{
		cerr << "sigaction failed in smash" << endl;
		return 1;
	}
	sigfillset(&mask_set2);
	ctrlZ.sa_mask = mask_set2;
	ctrlZ.sa_flags = 0;
	ctrlZ.sa_handler = &catch_SIGTSTP;
	if(sigaction(SIGTSTP, &ctrlZ, NULL))
	{
		cerr << "sigaction failed in smash" << endl;
		return 1;
	}

	char cmdString[MAX_LINE_SIZE];
	L_Fg_Cmd =(char*)malloc(sizeof(char)*(MAX_LINE_SIZE+1));
	if (L_Fg_Cmd == NULL) 
			exit (-1); 
	L_Fg_Cmd[0] = '\0';
	
	// the infinite input loop  
    	while (1)
    	{
		// initialize fg vars 
		*is_signal_fg = true;
		fg_job.set_PID(-1);

	 	printf ("smash > ");
		
		if (fgets(lineSize, MAX_LINE_SIZE, stdin) == NULL) {
			fgets(lineSize, MAX_LINE_SIZE, stdin);
		}

		
		strcpy(cmdString, lineSize);	
		cmdString[strlen(lineSize)-1]='\0';

		//handling history list
		if (cmdString != NULL && strcmp(cmdString,"")){
		history.push_front (cmdString);
		if (history.size() > 50)
		{
			history.resize(50);
		}
}
					// perform a complicated Command
		if(!ExeComp(lineSize)) continue; 
					// background command	
	 	if(!BgCmd(lineSize,jobs,cmdString,fg_job, history)) continue;
					// built in commands
		ExeCmd(jobs, lineSize, cmdString,fg_job,false, history);
		/* initialize for next line read*/
		lineSize[0]='\0';
		cmdString[0]='\0';
	}
		free(L_Fg_Cmd);
    return 0;
}

