#include <linux/MPI.h>






typedef struct rank_list {
	struct list_head rank_list;
	int pid;
	int rank;
	int run;
}rank_list;

rank_list* r_list_head;


// check if all the rank is 0
int check_for_all(void) {
	if (r_list_head == NULL) {
		printk("r_list_head == NULL, its big mistake \n");
		return -1;
	}
	struct list_head* pos;
	rank_list* cur;
	list_for_each(pos, &(r_list_head->rank_list)) {
		cur = list_entry(pos, rank_list, rank_list);
		if (cur->run == 1) { return 0; }
	}
	return 1;
}
//disable run att for this process
int d_run(void) {
	int rank = get_rank();
	if (rank == -1) {
		printk("d_run with rank -1, its big mistake \n");
		return -1;
	}
	struct list_head* pos;
	rank_list* cur;
	list_for_each(pos, &(r_list_head->rank_list)) {
		cur = list_entry(pos, rank_list, rank_list);
		if (cur->rank == rank) { 
			cur->run = 0;
			return 0; }
	}
	printk("not find rank list with rank, its big mistake \n");
	return -1;
}
//clean all the rank structs
void free_all_ranks(void) {
		struct list_head *pos, *q;
		struct rank_list* tmp;
		if (r_list_head != NULL) {
			list_for_each_safe(pos, q, &(r_list_head->rank_list)) {
				tmp = list_entry(pos, struct rank_list, rank_list);
				printk("del: %d \n", tmp->rank);
				list_del(pos);
				printk("free: %d \n", tmp->rank);
				kfree(tmp);
			}
			printk("free rank head\n");
			kfree(r_list_head);//check if this correct
			r_list_head = NULL;
		}
		
}

// register the process in the ranks
asmlinkage long sys_register_mpi(void) {
	int old_rank_num = get_rank();
	if (old_rank_num != -1) { 
		printk("get_rank find someting that isnet 1: %d", old_rank_num);
		return old_rank_num; 
	}
	if (r_list_head == NULL) {
		printk("malloc r_list_head \n");
		r_list_head = (rank_list*)kmalloc(sizeof(rank_list), GFP_KERNEL);
		if (r_list_head == NULL) {
			printk("malloc 1 falid \n");
			return -ENOMEM;
		}
		INIT_LIST_HEAD(&(r_list_head->rank_list));
		printk( "ADDED first ran k\n");
	}
	printk("malloc  new_rank  \n");
	rank_list* new_rank = (struct rank_list*)kmalloc(sizeof(struct rank_list), GFP_KERNEL);
	if (new_rank == NULL) {
		printk("malloc w falid \n");
		return -ENOMEM;
	}
	new_rank->pid = current->pid;
	new_rank->rank = new_rank_num();
	new_rank->run = 1;
	

	list_add_tail(&(new_rank->rank_list), &(r_list_head->rank_list));
	printk(KERN_DEBUG "Adding new rank \n");
	
	printk("return new rank: %d \n", new_rank->rank);
	return 	new_rank->rank;
}

// return the rank of the current process
int get_rank(void)
{
	if (r_list_head == NULL)
		return -1;
	struct list_head* pos;
	rank_list* cur;
	list_for_each(pos, &(r_list_head->rank_list)) {
		cur = list_entry(pos, rank_list, rank_list);
		if (cur->pid == current->pid) { return cur->rank; }
	}
	return -1;
}

// get the rank from pid
int get_rank_from_pid(int pid)
{
	if (r_list_head == NULL)
		return -1;
	struct list_head* pos;
	rank_list* cur;
	list_for_each(pos, &(r_list_head->rank_list)) {
		cur = list_entry(pos, rank_list, rank_list);
		if (cur->pid == pid) { return cur->rank; }
	}
	return -1;
}

// return new aviable rank num
int new_rank_num(void)
{
	if (r_list_head == NULL)
		return -1;
	struct list_head* pos;
	int i = 0;
	list_for_each(pos, &(r_list_head->rank_list)) {
		i++;
	}
	return i;
}
//return pid from rank num
int get_pid_from_rank(int rank)
{
	printk("start proc get_pid_from_rank with rank = %d \n", rank);
	if (r_list_head == NULL) {
		printk("r_list_head == NULL \n");
		return -1;
	}
		
	struct list_head* pos;
	rank_list* cur;
	list_for_each(pos, &(r_list_head->rank_list)) {
		cur = list_entry(pos, rank_list, rank_list);
		if (cur->rank == rank) {
			printk("found rankkkk");
			
				return cur->pid;
		}
	}
	return -1;
}

//check if given rank is running
int check_rank_run(int rank)
{
	printk("start proc check_rank_run with rank = %d \n", rank);
	if (r_list_head == NULL) {
		printk("r_list_head == NULL \n");
		return -1;
	}

	struct list_head* pos;
	rank_list* cur;
	list_for_each(pos, &(r_list_head->rank_list)) {
		cur = list_entry(pos, rank_list, rank_list);
		if (cur->rank == rank) {
			printk("found rankkkk");
			if (cur->run == 1) {
				return cur->pid;
			}
			else {
				printk("run isnt 1");
				return -1;
			}
		}
	}
	return -1;
}

//send message to rank
asmlinkage long sys_send_mpi_message(int rank, const char *message, ssize_t message_size) {
		struct task_struct* tsk = NULL;
		if (message == NULL || message_size < 1) {
			printk("1: messege null or size<1 \n");
			return -EINVAL;
		}
		int send_rank = get_rank();
		if (send_rank == -1) {
			printk("send_rank =-1 \n");
			return -ESRCH;
		}
		int pid = check_rank_run(rank);
		if (pid == -1) {
			printk("pid =-1 \n");
			return -ESRCH;
		}
		tsk = find_task_by_pid(pid);
		
		struct queue_struct* new_q = (struct queue_struct*)kmalloc(sizeof(struct queue_struct), GFP_KERNEL);
		if (new_q == NULL) {
			return -ENOMEM;
		}
		new_q->message = (char*)kmalloc(message_size, GFP_KERNEL);
		new_q->message_size = message_size;
		new_q->rank_from = send_rank;
		if (new_q->message == NULL) {
			kfree(new_q);
			return -ENOMEM;
		}
		
		if (copy_from_user(new_q->message, message, message_size)) {
			kfree(new_q->message);
			kfree(new_q);
			printk("copy from user \n");
			return -EFAULT;
		}
		if (tsk->q_head == NULL) {
			tsk->q_head = (struct queue_struct*)kmalloc(sizeof(struct queue_struct), GFP_KERNEL);
			if (tsk->q_head == NULL) {
				kfree(new_q->message);
				kfree(new_q);
				return -ENOMEM;
			}
			INIT_LIST_HEAD(&(tsk->q_head->q_list));
			printk(KERN_DEBUG "ADDED first mess\n");
		}

		list_add_tail(&(new_q->q_list), &(tsk->q_head->q_list));
		printk(KERN_DEBUG "Adding new mess\n");
		//for debug
		struct list_head* pos;
		list_for_each(pos, &tsk->q_head->q_list) {
			struct queue_struct* cur = list_entry(pos, struct queue_struct, q_list);
			printk("%d: %s\n", cur->rank_from, cur->message);
		}
		return 	0;
	}

//recevie message from rank

	asmlinkage long sys_receive_mpi_message(int rank, char* message, ssize_t message_size) {
		if (message == NULL || message_size < 1) {
			return -EINVAL;
		}
		int old_rank_num = get_rank();
		if (old_rank_num == -1) {
			return -ESRCH;
		}
		if (get_pid_from_rank(rank) == -1) {
			return -ESRCH;
		}
		struct task_struct* tsk = NULL;
		int pid = current->pid;
		tsk = find_task_by_pid(pid);
		struct queue_struct* tmp_q = q_by_rank(tsk->q_head, rank);
		if (tmp_q == NULL) {
			return -EFAULT;
		}
		else if (tmp_q->message_size < message_size) {
			message_size = tmp_q->message_size;
		}
		if (copy_to_user(message, tmp_q->message, message_size)) {
			return -EFAULT;
		}
		list_del(&tmp_q->q_list);
		if (tmp_q->message != NULL) {
			kfree(tmp_q->message);
		}
		kfree(tmp_q);
		return message_size;
	}


// get queueu from rank
	struct queue_struct* q_by_rank(struct queue_struct *que, int rank) {
		if (que == NULL) {
			return NULL;
		}
		struct list_head* pos;
		struct queue_struct* cur;
		list_for_each(pos, &que->q_list) {
			cur = list_entry(pos, struct queue_struct, q_list);
			if (cur->rank_from == rank) {
				return cur;
			}
		}
		return NULL;
	}
	// copy all the message from father to sun
	int copy_messages(int from_pid, int dest_pid, struct queue_struct* new_q_head) {
		struct task_struct* tsk = find_task_by_pid(from_pid);
		if (tsk->q_head == NULL) { return -2; }
		int rank_to = get_rank_from_pid(dest_pid);
		int rank_from;
		struct list_head* pos;
		struct queue_struct* cur;
		list_for_each(pos, &tsk->q_head->q_list) {
			cur = list_entry(pos, struct queue_struct, q_list);
			rank_from = cur->rank_from;
			printk("FORK: copy %d to %d mes %s zise %d \n", rank_to, rank_from, cur->message, cur->message_size);
			if (fork_send_mpi_message(rank_to, rank_from, cur->message, cur->message_size, new_q_head) == -1) {
					printk("error in fork_send_mpi_message \n"); 
					return -1;
			}
		}
		return 0;
	}
	//register sun in forkk
	int fork_register_mpi(int pid) {
		
		if (r_list_head == NULL) {
			printk("BIG mistake in fork_reg \n");
			r_list_head = (rank_list*)kmalloc(sizeof(rank_list), GFP_KERNEL);
			if (r_list_head == NULL) {
				printk("malloc 1 falid \n");
				return -ENOMEM;
			}
			INIT_LIST_HEAD(&(r_list_head->rank_list));
			printk("ADDED first ran k\n");
		}
		rank_list* new_rank = (struct rank_list*)kmalloc(sizeof(struct rank_list), GFP_KERNEL);
		if (new_rank == NULL) {
			printk("malloc w falid \n");
			return -ENOMEM;
		}
		new_rank->pid = pid;
		new_rank->rank = new_rank_num();
		new_rank->run = 1;


		list_add_tail(&(new_rank->rank_list), &(r_list_head->rank_list));
		printk(KERN_DEBUG "Adding new rank \n");
		
		printk("return new rank: %d \n", new_rank->rank);
		return 	new_rank->rank;
	}

	// send messsage ffrom father to sun
	int fork_send_mpi_message(int rank_to,int rank_from,const char *message, ssize_t message_size, struct queue_struct* new_q_head) {
		//struct task_struct* tsk = NULL;
		if (message == NULL || message_size < 1) {
			printk("1: messege null or size<1 \n");
			return -EINVAL;
		}
		int pid = get_pid_from_rank(rank_to);
		if (pid == -1) {
			printk("pid =-1 \n");
			return -ESRCH;
		}
		
		struct queue_struct* new_q = (struct queue_struct*)kmalloc(sizeof(struct queue_struct), GFP_KERNEL);
		if (new_q == NULL) {
			return -ENOMEM;
		}
		new_q->message = (char*)kmalloc(message_size, GFP_KERNEL);
		new_q->message_size = message_size;
		new_q->rank_from = rank_from;
		if (new_q->message == NULL) {
			kfree(new_q);
			return -ENOMEM;
		}
		
		printk("FORK:memcoy BEFOR: mes_from:   \n");
		memcpy(new_q->message, message, message_size);
	
		//printk("FORK:memcoy SUCSES: mes_from: %s mes to: %s size: %d \n", new_q->message, message, message_size);
		printk("FORK CHeck tsk head pid \n");
		/*if (tsk->q_head == NULL) {
			printk("FORK q head is null do mallock \n");
			tsk->q_head = (struct queue_struct*)kmalloc(sizeof(struct queue_struct), GFP_KERNEL);
			if (tsk->q_head == NULL) {
				kfree(new_q->message);
				kfree(new_q);
				return -ENOMEM;
			}
			printk("FORK INIT_LIST_HEAD  \n");
			INIT_LIST_HEAD(&(tsk->q_head->q_list));
			printk(KERN_DEBUG "ADDED first mess\n");
		}*/
		printk("FORK list_add_tail  \n");
		list_add_tail(&(new_q->q_list), &new_q_head->q_list);
		printk(KERN_DEBUG "Adding new mess\n");
	
		struct list_head* pos;
		list_for_each(pos, &new_q_head->q_list) {
			struct queue_struct* cur = list_entry(pos, struct queue_struct, q_list);
			printk("%d: %s\n", cur->rank_from, cur->message);
		}
		return 	0;
	}
