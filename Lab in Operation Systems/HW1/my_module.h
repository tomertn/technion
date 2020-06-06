#ifndef _MY_MODULE_H_
#define _MY_MODULE_H_

#include <linux/ioctl.h>

#define MY_MAGIC 'r'
#define MY_RESET _IOW(MY_MAGIC, 0, int)
#define MY_RESTART _IOW(MY_MAGIC, 1, int)
#define MY_SET_SEED _IOW(MY_MAGIC, 2, int)
#define BUFFER_SIZE (4096)

typedef struct  Device_t{
    void* buf;
    void* read;
    void* write;
	unsigned int minor;
    struct Device_t* next;
	int r_flag;
	int w_flag;
	int o_flag;
	uint32_t seed;
} Dev;

//
// Function prototypes
//
int my_open(struct inode *, struct file *);

int my_release(struct inode *, struct file *);

ssize_t my_read(struct file *, char *, size_t, loff_t *);

ssize_t my_write(struct file *, const char *, size_t, loff_t *);

int my_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);

uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed);

//size_t min(size_t, size_t);

#endif
