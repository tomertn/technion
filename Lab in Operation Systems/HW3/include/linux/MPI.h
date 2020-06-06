#ifndef _MPI_H
#define _MPI_H

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <asm/uaccess.h>


asmlinkage long sys_register_mpi(void);
int get_rank(void);
int new_rank_num(void);
int get_pid_from_rank(int rank);
asmlinkage long sys_send_mpi_message(int rank, const char *message, ssize_t message_size);
asmlinkage long sys_receive_mpi_message(int rank, int timeout, char* message, ssize_t message_size);
struct queue_struct* q_by_rank(struct queue_struct *que, int rank);
void free_all_ranks(void);
int d_run(void);
int check_for_all(void);
int fork_register_mpi(int pid);
int get_rank_from_pid(int pid);
int copy_messages(int from_pid, int dest_pid, struct queue_struct* new_q_head);
int fork_send_mpi_message(int rank_to, int rank_from, const char *message, ssize_t message_size, struct queue_struct* new_q_head);
int check_rank_run(int rank);
int check_if_someone_wiat_for_me_rank(int me_rank);
int set_iam_wait_for_rank(int me_rank, int rank_i_wait_for);
int check_if_waited_rank_wiat_for_me_rank(int me_rank, int wait_rank);
#endif // _MPI_H

