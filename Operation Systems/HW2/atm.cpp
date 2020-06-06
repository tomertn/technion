#include "atm.h"
#define MAX_ARGS 5

/*FILE* enter_print(FILE* fp)
{
	pthread_mutex_lock(&print_mutex);
cout<<"getinn"<<endl;
	fp= fopen("log.txt", "a");
	return fp;
}

void leave_print(FILE* fp)
{
	fclose(fp);
cout<<"file clise"<<endl;
cerr<<"eror sttea,"<<endl;
	pthread_mutex_unlock(&print_mutex);
}
*/
void* file_exe(void* _file_name)
{
	//bool out=true;
cout<<"11111"<<endl;
	string line;
	string* file_name = (string*)(_file_name);
cout<<file_name<<endl;
cout<<*file_name<<endl;
	ifstream myfile((*file_name).c_str());
	if (myfile.is_open())
	{
cout<<"ook"<<endl;
		while (getline(myfile, line))
		{
			usleep(100000);
			exe_line(line);
		}
		myfile.close();
	}

	return 0;//(void*)out;
}


int exe_line(string _line)
{
	int atm_i = j;
	j++;
cout<<"ook2"<<endl;
	pthread_mutex_unlock(&j_mutex);
cout<<"ook22"<<endl;
	char* args[MAX_ARGS],* cmd,* line;
cout<<"ook222"<<endl;
	const char* line_temp = _line.c_str();
cout<<"ook2222"<<endl;

	//strcpy(line, line_temp);
cout<<"ook22222"<<endl;
	char* delimiters = (char*)" \t";
cout<<"ook222222"<<endl;
	int num_args = 0, i;
cout<<"ook2.2"<<endl;
pthread_mutex_lock(&print_mutex);
	cmd = strtok(strdup(_line.c_str()), delimiters);
pthread_mutex_unlock(&print_mutex);
cout<<"ook2.3"<<endl;
	if (cmd == NULL)
	{
		cerr << "error in strtokon" << endl;
		return 1;
	}
	for (i = 0; i < MAX_ARGS; i++)
	{
cout<<"ook3"<<endl;
		args[i] = strtok(NULL, delimiters);
		if (args[i] != NULL)
			num_args++;
	}

	//open account
	if (!strcmp(cmd, "O"))		//open account
	{

		cout<<"OOOOOOOOOOO"<< endl;

		int acc_to_open = atoi(args[0]);
		int amount = atoi(args[2]);
		bool flag = false;
		pthread_mutex_lock(&vec_wrt);
	
		vector<account>::iterator it = acc_vec.begin();
			for (; it != acc_vec.end(); it++)
			{
				if (it->get_acc_num() == acc_to_open)
				{
					flag = true; break;
				}
			}
			if (!flag)
			{
				account acc_to_push(acc_to_open, args[1], amount, false);
				acc_vec.push_back(acc_to_push);

			}
		sleep(1);
		pthread_mutex_unlock(&vec_wrt);
		if (!flag)
		{
			pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
			fprintf(fp, "%s", "aaa");
			cout << atm_i << ": New account id is " << acc_to_open << " with password ";
			cout << args[1] << " and initial balance " << amount << endl;
			fclose(fp);
			pthread_mutex_unlock(&print_mutex);
		}
		else
		{
			pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
			cout << "Error " << atm_i << ": Your transaction failed - acoount with the same id exist" << endl;
		fclose(fp);
			pthread_mutex_unlock(&print_mutex);
		}
	}

	//set account to vip
	else if (!strcmp(cmd, "L"))
	{
		int account_num = atoi(args[0]), password = atoi(args[1]);
		bool flag = false;

		pthread_mutex_lock(&vec_rd);
		vec_cnt++;
		if (vec_cnt == 1) pthread_mutex_lock(&vec_wrt);
		pthread_mutex_unlock(&vec_rd);
		
		vector<account>::iterator it = acc_vec.begin();
		for (; it != acc_vec.end(); it++)
		{
			if (it->get_acc_num() == account_num)
			{
				flag = true;
				if (atoi(it->get_pass().c_str()) == password) {
					it->set_vip(true); break;
				}
				else {
					flag = false;
					 break;
				}
			}
		}
		sleep(1);
		if (!flag)
		{
			
			pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
			cout << "Error " << atm_i << ": Your transaction failed - password for account id ";
			cout << account_num << " is incorrect" << endl;
			fclose(fp);
			pthread_mutex_unlock(&print_mutex);
		}
		pthread_mutex_lock(&vec_rd);
		vec_cnt--;
		if (vec_cnt == 0) pthread_mutex_unlock(&vec_wrt);
		pthread_mutex_unlock(&vec_rd);
	}

	//deposite
	else if (!strcmp(cmd, "D"))
	{
		int account_num = atoi(args[0]), password = atoi(args[1]), amount= atoi(args[2]);
		bool flag = false;
		pthread_mutex_lock(&vec_rd);
		vec_cnt++;
		if (vec_cnt == 1) pthread_mutex_lock(&vec_wrt);
		pthread_mutex_unlock(&vec_rd);

		vector<account>::iterator it = acc_vec.begin();
		for (; it != acc_vec.end(); it++)
		{
			if (it->get_acc_num() == account_num)
			{
				flag = true;
				
				if (atoi(it->get_pass().c_str()) == password) {
					int t=it->add_amount(amount);
					pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
					cout << atm_i << ": Account "<<account_num<<" new balance is ";
					cout << t<< " after "<<amount<<" $ was deposited" << endl;
					fclose(fp);
			pthread_mutex_unlock(&print_mutex);
					break;
				}
				else {
					pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
					cout << "Error " << atm_i << ": Your transaction failed - password for account id ";
					cout << account_num << " is incorrect" << endl;
					fclose(fp);
			pthread_mutex_unlock(&print_mutex);
					break;
				}
			}
		}
		sleep(1);
		if (!flag)
		{
			pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
			cout << "Error " << atm_i << ": Your transaction failed - account id ";
			cout << account_num << " does not exist" << endl;
			fclose(fp);
			pthread_mutex_unlock(&print_mutex);
		}
		pthread_mutex_lock(&vec_rd);
		vec_cnt--;
		if (vec_cnt == 0) pthread_mutex_unlock(&vec_wrt);
		pthread_mutex_unlock(&vec_rd);
	}

	//withdraw
	else if (!strcmp(cmd, "W"))
	{
	int account_num = atoi(args[0]), password = atoi(args[1]), amount = atoi(args[2]);
	bool flag = false;

	pthread_mutex_lock(&vec_rd);
	vec_cnt++;
	if (vec_cnt == 1) pthread_mutex_lock(&vec_wrt);
	pthread_mutex_unlock(&vec_rd);

	vector<account>::iterator it = acc_vec.begin();
	for (; it != acc_vec.end(); it++)
	{
		if (it->get_acc_num() == account_num)
		{
			flag = true;
			if (atoi(it->get_pass().c_str()) == password) {
				int t = it->add_amount(-amount);
				if (t != (-1))
				{
					pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
					cout << atm_i << ": Account " << account_num << " new balance is ";
					cout << t << " after " << amount << " $ was withdrew" << endl;
					fclose(fp);
			pthread_mutex_unlock(&print_mutex);
				}
				else
				{
					pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
					cout << "Error " << atm_i << ": Your transaction failed - account id ";
					cout << account_num << " balance is lower than "<< amount << endl;
					fclose(fp);
			pthread_mutex_unlock(&print_mutex);
				}
				break;
			}
			else {
				pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
				cout << "Error " << atm_i << ": Your transaction failed - password for account id ";
				cout << account_num << " is incorrect" << endl;
				fclose(fp);
			pthread_mutex_unlock(&print_mutex);
				break;
			}
		}
	}
	sleep(1);
	if (!flag)
	{
		pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
		cout << "Error " << atm_i << ": Your transaction failed - account id ";
		cout << account_num << " does not exist" << endl;
		fclose(fp);
			pthread_mutex_unlock(&print_mutex);
	}
	pthread_mutex_lock(&vec_rd);
	vec_cnt--;
	if (vec_cnt == 0) pthread_mutex_unlock(&vec_wrt);
	pthread_mutex_unlock(&vec_rd);
	}

	//check balance
	else if (!strcmp(cmd, "B"))
	{
	int account_num = atoi(args[0]), password = atoi(args[1]);
	bool flag = false;

	pthread_mutex_lock(&vec_rd);
	vec_cnt++;
	if (vec_cnt == 1) pthread_mutex_lock(&vec_wrt);
	pthread_mutex_unlock(&vec_rd);

	vector<account>::iterator it = acc_vec.begin();
	for (; it != acc_vec.end(); it++)
	{
		if (it->get_acc_num() == account_num)
		{
			flag = true;
			
			if (atoi(it->get_pass().c_str()) == password) {
				pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
				cout << atm_i << ": Account " << account_num << " balance is " << it->get_amount()<<endl;
				fclose(fp);
			pthread_mutex_unlock(&print_mutex);
				break;
			}
			else {
				pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
				cout << "Error " << atm_i << ": Your transaction failed - password for account id ";
				cout << account_num << " is incorrect" << endl;
				fclose(fp);
			pthread_mutex_unlock(&print_mutex);
				break;
			}
		}
	}
	sleep(1);
	if (!flag)
	{
		pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
		cout << "Error " << atm_i << ": Your transaction failed - account id ";
		cout << account_num << " does not exist" << endl;
		fclose(fp);
			pthread_mutex_unlock(&print_mutex);
	}
	pthread_mutex_lock(&vec_rd);
	vec_cnt--;
	if (vec_cnt == 0) pthread_mutex_unlock(&vec_wrt);
	pthread_mutex_unlock(&vec_rd);
	}

	//transfer 
	else if (!strcmp(cmd, "T"))
	{
	int account_num = atoi(args[0]), password = atoi(args[1]), target = atoi(args[2]), amount=atoi(args[3]);
	bool flag = false, flag1 = false;

	pthread_mutex_lock(&vec_rd);
	vec_cnt++;
	if (vec_cnt == 1) pthread_mutex_lock(&vec_wrt);
	pthread_mutex_unlock(&vec_rd);

	vector<account>::iterator it = acc_vec.begin();
	for (; it != acc_vec.end(); it++)
	{
		if (it->get_acc_num() == account_num)
		{
			flag = true;

			if (atoi(it->get_pass().c_str()) == password) 
			{
				vector<account>::iterator it1 = acc_vec.begin();
				for (; it1 != acc_vec.end(); it1++)
				{
					if (it1->get_acc_num() == target)
					{
						flag1 = true;
						int t = (it->add_amount(-amount));
						if (t != (-1))
						{
							int t1=it1->add_amount(amount);
							pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
							cout << atm_i << ": Transfer " << amount << " from account " << account_num << " to account" << target;
							cout << " new account balance is " << t << " new target account balance is "; 
							cout << t1 << endl;
							fclose(fp);
			pthread_mutex_unlock(&print_mutex);
						}
						else //not enough money
						{
			pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
							cout << "Error " << atm_i << ": Your transaction failed - account id ";
							cout << account_num << " balance is lower than " << amount << endl;
							fclose(fp);
			pthread_mutex_unlock(&print_mutex);
						}
						break;
					}
				}
			}
			else 
			{
				pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
				cout << "Error " << atm_i << ": Your transaction failed - password for account id ";
				cout << account_num << " is incorrect" << endl;
				fclose(fp);
			pthread_mutex_unlock(&print_mutex);
				break;
			}
		}
	}
	sleep(1);
	if (!flag)
	{
		pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
		cout << "Error " << atm_i << ": Your transaction failed - account id ";
		cout << account_num << " does not exist" << endl;
		fclose(fp);
			pthread_mutex_unlock(&print_mutex);
	}
	else if (!flag1)
	{
		pthread_mutex_lock(&print_mutex);
			FILE* fp= fopen("log.txt", "a");
		cout << "Error " << atm_i << ": Your transaction failed - account id ";
		cout << target << " does not exist" << endl;
		fclose(fp);
			pthread_mutex_unlock(&print_mutex);
	}
	pthread_mutex_lock(&vec_rd);
	vec_cnt--;
	if (vec_cnt == 0) pthread_mutex_unlock(&vec_wrt);
	pthread_mutex_unlock(&vec_rd);
	
	}

}
