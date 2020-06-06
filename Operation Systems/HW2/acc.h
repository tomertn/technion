
#ifndef ACC_H_
#define ACC_H_

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <stdbool.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <iostream>
using namespace std;


class account {

public:

	account();
	account(int acc, string pass, int amount, bool vip);
	~account() { pthread_mutex_destroy(&rd); pthread_mutex_destroy(&wrt);}
	int get_acc_num();
	int get_amount();
	string get_pass();
	bool is_vip();
//	void set_acc_num(int acc_num);// { _acc_num = acc_num; }
	void set_amount(int amount);// { _amount = amount; }
	void set_vip(bool vip);// { _vip = vip; }
	int add_amount(int amount);
	int bank_charge(double percent);

	void rd_lock() { pthread_mutex_lock(&rd); }
	void wrt_lock() { pthread_mutex_lock(&wrt); }
	void rd_unlock() { pthread_mutex_unlock(&rd); }
	void wrt_unlock() { pthread_mutex_unlock(&wrt); }

private:
	pthread_mutex_t rd;
	pthread_mutex_t wrt;
	int _acc_num;
	string _pass;
	int _amount;
	bool _vip;
	int cnt;
};







#endif /* ACC_H_ */
