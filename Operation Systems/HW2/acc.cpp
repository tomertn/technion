#include "acc.h"


account::account()
{
	_acc_num=(-1);
	_pass="0000";
	_amount=(0);
	_vip=(false);
	pthread_mutex_init(&rd, NULL);
	pthread_mutex_init(&wrt, NULL);
	cnt = 0;
}

account::account(int acc, string pass, int amount, bool vip)
{
	_acc_num= acc;
	_pass= pass;
	_amount= amount;
	_vip =vip ;
	pthread_mutex_init(&rd, NULL);
	pthread_mutex_init(&wrt, NULL);
	cnt = 0;
}

int account::get_acc_num() {
	pthread_mutex_lock(&rd);
	cnt++;
	if (cnt == 1) pthread_mutex_lock(&wrt);
	pthread_mutex_unlock(&rd);
	int t = _acc_num;
	pthread_mutex_lock(&rd);
	cnt--;
	if (cnt == 0) pthread_mutex_unlock(&wrt);
	pthread_mutex_unlock(&rd);
	return t;
}
int account::get_amount() {
	pthread_mutex_lock(&rd);
	cnt++;
	if (cnt == 1) pthread_mutex_lock(&wrt);
	pthread_mutex_unlock(&rd);
	int t = _amount;
	pthread_mutex_lock(&rd);
	cnt--;
	if (cnt == 0) pthread_mutex_unlock(&wrt);
	pthread_mutex_unlock(&rd);
	return t;
}

string account::get_pass() {
	pthread_mutex_lock(&rd);
	cnt++;
	if (cnt == 1) pthread_mutex_lock(&wrt);
	pthread_mutex_unlock(&rd);
	string t = _pass;
	pthread_mutex_lock(&rd);
	cnt--;
	if (cnt == 0) pthread_mutex_unlock(&wrt);
	pthread_mutex_unlock(&rd);
	return t;
}
bool account::is_vip() {
	pthread_mutex_lock(&rd);
	cnt++;
	if (cnt == 1) pthread_mutex_lock(&wrt);
	pthread_mutex_unlock(&rd);
	bool t = _vip;
	pthread_mutex_lock(&rd);
	cnt--;
	if (cnt == 0) pthread_mutex_unlock(&wrt);
	pthread_mutex_unlock(&rd);
	return t;
}
void account::set_amount(int amount) {
	pthread_mutex_lock(&wrt);
	_amount = amount;
	pthread_mutex_unlock(&wrt);
}

void account::set_vip(bool vip) {
	pthread_mutex_lock(&wrt);
	_vip = vip;
	pthread_mutex_unlock(&wrt);
}

int account::add_amount(int amount)
{
	int t;
	pthread_mutex_lock(&wrt);
	if ((_amount + amount) < 0) t = (-1);
	else
	{
		_amount += amount;
		t = _amount;
	}
	pthread_mutex_unlock(&wrt);
	return t;
}

int account::bank_charge(double percent)
{
	int t;
	pthread_mutex_lock(&wrt);
	if (_vip) t = (-1);
	else
	{
		double temp = (percent*_amount) / 100;
		temp = round(temp);
		_amount -= temp;
		t = temp;
	}
	pthread_mutex_unlock(&wrt);
	return t;
}
