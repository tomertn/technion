
#ifndef ATM_H_
#define ATM_H_

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include<stdbool.h>
#include "acc.h"

using namespace std;
void* file_exe(void* file_name);
int exe_line(string line);
//FILE* enter_print(FILE* fp);
//void leave_print(FILE* fp);

//import globals
extern vector<account> acc_vec;
extern pthread_mutex_t vec_rd;
extern pthread_mutex_t vec_wrt;
extern int vec_cnt;
extern int j;
extern pthread_mutex_t j_mutex;
extern pthread_mutex_t print_mutex;
#endif /* ATM_H_ */
