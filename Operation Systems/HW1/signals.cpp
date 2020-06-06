// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.h"

//extern vars to handle bg process signals
extern bool* is_signal_fg;
extern int* pid_to_signal;



//**************************************************************************************
// function name: sigint_to_signame
// Description: return the name of signum
// Parameters: num of signal
// Returns: String
//**************************************************************************************

string sigint_to_signame(int sigint)
{
	string signame[] = { "ERROR", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL",
		"SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP",
		"SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGPOLL", "SIGPWR", "SIGSYS" };
	if (sigint>0 && sigint < 32)
	{
		return signame[sigint];
	}
	return NULL;
}

//**************************************************************************************
// function name: send_signal
// Description: wraping function of sending signal. includes compatible prints.
// Parameters: pid, num of signal
// Returns: true - success, false - failure
//**************************************************************************************
bool send_signal(int pid, int signal) 
{
	
	if (kill(pid, signal) == 0)
	{
		string signame = sigint_to_signame(signal);
		cout << "signal ";
		printf("%s", signame.c_str());
		cout << " was sent to pid " << pid << endl;
		return true;
	}
	else
	{
		cerr << "there were error in kill function" << endl;
		return false;
	}

}

//**************************************************************************************
// function name: catch_SIGINT
// Description: SIGINT handler. special handler for CNTRL+C of sending signal to fg process.
// Parameters: num of signal
// Returns: void
//**************************************************************************************
void catch_SIGINT(int signum)
{
	if (fg_job.get_PID() == -1) 
	{
	return;
	}
	if (signum != SIGINT) return;

	if (fg_job.get_PID() != -1 && waitpid(fg_job.get_PID(), NULL, WNOHANG) == 0)
	{
		if (!send_signal(fg_job.get_PID(), SIGINT))	return;
	
		else
		{
			waitpid(fg_job.get_PID(), NULL, WUNTRACED);
			fg_job.set_PID(-1);
		}
	}
}


//**************************************************************************************
// function name: catch_SIGTSTP
// Description: SIGTSTP handler. special handler for CNTRL+Z of sending signal to fg process.
// Parameters: num of signal
// Returns: void
//**************************************************************************************
void catch_SIGTSTP(int signum)
{
	// Do nothing if its fg job and fg == -1
	if (*is_signal_fg && (fg_job.get_PID() == -1)){
	return;
	}

	if (signum != SIGTSTP) return;

	// handling bg SIGTSTP (came from kill -20 [num] command)
	if (*is_signal_fg == false) { 
		send_signal(*pid_to_signal, 19);
		return;
	}

	//handling CNTRL+Z
	int pid = fg_job.get_PID();
	if ( waitpid(fg_job.get_PID(), NULL, WNOHANG) == 0) //check if process still alive
	{
		// send SIGSTOP signal to the fg proccess. if there was an error return, otherwise job sleeps
		if (!send_signal(fg_job.get_PID(), 19))	return;

		Job job_to_bg (fg_job.get_name(),fg_job.get_PID(),(int)time(NULL));
				job_to_bg.set_bg(true);
				job_to_bg.set_is_sleep(true);
				jobs.push_back(job_to_bg);
				cout << jobs.front().get_PID() <<endl;
				fg_job.set_PID(-1);
	}

}

