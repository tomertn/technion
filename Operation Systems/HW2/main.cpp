#include "atm.h"
#include "acc.h"
#include <vector>
#include <map>

using namespace std;

/* bank representation:*/
//global vars
vector<account> acc_vec; 
pthread_mutex_t vec_rd;
pthread_mutex_t vec_wrt;
pthread_mutex_t j_mutex;
pthread_mutex_t print_mutex;
int vec_cnt = 0, j=1, bank_amount = 0;

//bank funcs
void* bank_charge_func(void* parameter)
{

	while (*(bool*)parameter)
	{
		sleep(3);
		double percent = ((rand() % 201)/100)+2;
		double to_charge;

		pthread_mutex_lock(&vec_rd);
		vec_cnt++;
		if (vec_cnt == 1) pthread_mutex_lock(&vec_wrt);
		pthread_mutex_unlock(&vec_rd);


		
		vector<account>::iterator it = acc_vec.begin();
		for (; it != acc_vec.end(); it++)
		{
			int t = it->bank_charge(percent);
			if (t != (-1))
			{
				bank_amount += t;
			pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
				cout << "Bank: commissions of " << percent << " % were charged, the bank gained " << t << " $ ";
				cout << "from account " << it->get_acc_num() << endl;
				fclose(fp);
			pthread_mutex_unlock(&print_mutex);
			}
		}


		pthread_mutex_lock(&vec_rd);
		vec_cnt--;
		if (vec_cnt == 0) pthread_mutex_unlock(&vec_wrt);
		pthread_mutex_unlock(&vec_rd);
	}
}

void* bank_print_func(void* parameter)
{

	while (*(bool*)parameter)
	{
		usleep(500000);
		pthread_mutex_lock(&print_mutex);
		//printf("\033[2J");
		//printf("\033[1;1H");
		cout << "Current Bank Status" << endl;
		pthread_mutex_unlock(&print_mutex);

		pthread_mutex_lock(&vec_rd);
		vec_cnt++;
		if (vec_cnt == 1) pthread_mutex_lock(&vec_wrt);
		pthread_mutex_unlock(&vec_rd);

		vector<account>::iterator it = acc_vec.begin();
		for (; it != acc_vec.end(); it++)
		{
			pthread_mutex_lock(&print_mutex);
			cout << "Account " << it->get_acc_num() << ": Balance - " << it->get_amount() << " $ , ";
			cout << "Account Password - " << it->get_pass()<<endl;
			pthread_mutex_unlock(&print_mutex);
		}
		pthread_mutex_lock(&print_mutex);
		cout << "The Bank has " << bank_amount << " $" << endl;
		pthread_mutex_unlock(&print_mutex);

		pthread_mutex_lock(&vec_rd);
		vec_cnt--;
		if (vec_cnt == 0) pthread_mutex_unlock(&vec_wrt);
		pthread_mutex_unlock(&vec_rd);
	}
}


int main(int argc, char *argv[]) {
	if (argc <= 1 || (argc - 2) != atoi(argv[1]))	//input check
	{
		cout << "illegal arguments" << endl;
		return 1;
	} 
	
	//init global mutexs
	pthread_mutex_init(&vec_rd, NULL);
	pthread_mutex_init(&vec_wrt, NULL);
	pthread_mutex_init(&j_mutex, NULL);
	pthread_mutex_init(&print_mutex, NULL);

	int i, n = atoi(argv[1]);
	bool is_threads = true;
	
	//atm's threads
	pthread_t* atms = (pthread_t*)malloc(sizeof(pthread_t)*n);
	if (!atms)
	{
		cerr << "alocation was failed" << endl;
		return 1;
	}

	//bank threads
	pthread_t bank_charge;
	pthread_t bank_print_status;



	for ( i = 0; i < n; i++)		//atms threads
	{
		pthread_mutex_lock(&j_mutex);
cout<<&argv[i+2]<<endl;
cout<<*&argv[i+2]<<endl;
		string* s= new string(argv[i+2]);
cout<<*s<<endl;
		pthread_create(&atms[i], NULL, &file_exe, (void*)s);
	}

	pthread_create(&bank_charge, NULL, &bank_charge_func, (void*)(&is_threads));
	pthread_create(&bank_print_status, NULL, &bank_print_func, (void*)(&is_threads));

	for (i = 0; i < n; i++)		//atms threads
	{
		pthread_join(atms[i], NULL);
	}
	is_threads = false;
	pthread_join(bank_charge, NULL);
	pthread_join(bank_print_status, NULL);

	//dont forget to destroy mutex's
	pthread_mutex_destroy(&j_mutex);
	pthread_mutex_destroy(&print_mutex);
	pthread_mutex_destroy(&vec_rd);
	pthread_mutex_destroy(&vec_wrt);
	free(atms);
	return 0;
}



