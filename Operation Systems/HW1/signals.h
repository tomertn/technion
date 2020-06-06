#ifndef _SIGS_H
#define _SIGS_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "commands.h"
#include <string.h>

extern Job fg_job;
extern list<Job> jobs;


bool send_signal(int pid, int signal);
string sigint_to_signame(int sigint);
void catch_SIGINT(int signum);
void catch_SIGTSTP(int signum);

#endif

