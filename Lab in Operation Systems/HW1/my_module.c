/* my_module.c: Example char device module.
 *
 */
/* Kernel Programming */
#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/kernel.h>  	
#include <linux/module.h>
#include <linux/fs.h>       		
#include <asm/uaccess.h>
#include <linux/errno.h>  
#include <linux/slab.h>

#define MY_DEVICE "s19_device"

#include "my_module.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomer and Shalev");

/* globals */
int my_major = 0; /* will hold the major # of my device driver */
Dev* my_dev = NULL; 

struct file_operations my_fops = {
  .open = my_open,
  .release = my_release,
  .read = my_read,
  .write = my_write,
  .ioctl = my_ioctl
};

// find the requested device in the list
static Dev* findDevice(unsigned int minor){
	Dev* itr = my_dev;
	while(itr != NULL){
		if(itr->minor == minor)
			return itr;
		else 
		itr = itr->next;
	}
	return NULL;
}

// init the modules
int init_module(void)
{
    my_major = register_chrdev(my_major, MY_DEVICE, &my_fops);

    if (my_major < 0)
    {
		return my_major;
    }
	my_dev=NULL;
    return 0;
}

// free the devices 
void cleanup_module(void)
{
    unregister_chrdev(my_major, MY_DEVICE);

	while(my_dev != NULL){
		Dev* itr = my_dev;
		my_dev = my_dev->next;
		if(itr->buf != NULL){
			kfree(itr->buf);
		}
		if(itr != NULL){
			kfree(itr);
		}
	}
	
    return;
}

// open a new device
int my_open(struct inode *inode, struct file *filp)
{
	unsigned int minor = MINOR(inode->i_rdev);
	Dev* dev = findDevice(minor);
	if(dev!=NULL){	
		filp->private_data = (void*)dev;
		dev->o_flag = 1;
		if (filp->f_mode & FMODE_READ)
		{
			printk(KERN_WARNING "open divce in read mode\n");
			dev->r_flag = 1;

		}
		if (filp->f_mode & FMODE_WRITE)
		{
			dev->w_flag = 1;
			printk(KERN_WARNING "opene divce in write mode\n");
		}
		return 0;
	}
	dev = (Dev*)kmalloc(sizeof(Dev), GFP_KERNEL);
	if (dev == NULL)
	{
		return -EFAULT;
	}
	dev->buf = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	if (dev->buf == NULL)
	{
		kfree(dev);
		return -EFAULT;
	}
	dev->read = dev->buf;
	dev->minor = minor;
	dev->write = dev->buf;
	dev->seed = 0;

	
	
	if ( my_dev == NULL )	dev->next = NULL;
	else dev->next = my_dev;
	my_dev = dev;
		
	filp->private_data = (void*)dev;
	dev->o_flag = 1;
	
    if (filp->f_mode & FMODE_READ)
    {
		printk(KERN_WARNING "open divce in read mode\n");
		dev->r_flag = 1;
    }
    
    if (filp->f_mode & FMODE_WRITE)
    {
		printk(KERN_WARNING "opene divce in write mode\n");
        dev->w_flag = 1;
    }
    return 0;
}

// close the device
int my_release(struct inode *inode, struct file *filp)
{
	Dev* curr = (Dev*)filp->private_data;
	if (curr == NULL)
	{
		return -EFAULT;
	}
	
	if (curr->o_flag == 0)
	{
		return -EBADF;
	}
	
    if (filp->f_mode & FMODE_READ)
    {
		curr->r_flag = 0;
    }
    
    if (filp->f_mode & FMODE_WRITE)
    {
        curr->w_flag = 0;
    }
	
	curr->o_flag = 0;
	printk(KERN_WARNING "device closed");
    return 0;
}


ssize_t my_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    Dev* curr = filp->private_data;
	if (curr == NULL)
	{
		return -EFAULT;
	}
	
	// the divice is not open or no permsion
	if ( curr->o_flag == 0 || curr->r_flag == 0)
	{
		return -EFAULT;
	}
	
	
	if ( curr->write == curr->buf )
	{
		return 0;
	}
	
    size_t num_to_copy = min(count,(size_t)((char*)curr->write - (char*)curr->read));
	uint32_t to_buf = murmur3_32(curr->read, (size_t)num_to_copy, curr->seed);
	if(copy_to_user(buf, &to_buf , sizeof(uint32_t)) != 0)
	{
		return -EFAULT;
	}
	if(copy_to_user(buf+4, curr->read, num_to_copy) != 0)
	{
		return -EFAULT;
	}
	curr->read += num_to_copy;
    return num_to_copy + 4;
}


ssize_t my_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    Dev* curr = filp->private_data;
	if (curr == NULL)
	{
		return -EFAULT;
	}
	if ( curr->o_flag == 0 || curr->w_flag == 0)
	{
		return -EFAULT;
	}
	// there is no enough space in the device
	if((curr->write + count) > (curr->buf + BUFFER_SIZE))
	{
		return -ENOMEM;
	}
	if (count == 0)
	{
		return -EINVAL;
	}
	if ( copy_from_user(curr->write, buf, count) != 0 )
	{
		return -EFAULT;
	}
	curr->write += count;
	return count;
}


int my_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	Dev* curr = filp->private_data;
	if (curr == NULL)
	{
		return -EFAULT;
	}
	
	// the device is not open
	if ( curr->o_flag == 0 )
	{
		return -EFAULT;
	}
	
    switch(cmd)
    {
		case MY_RESTART: 
			curr->read = curr->buf;
		break;

		case MY_RESET:
			curr->read = curr->buf;
			curr->write = curr->buf;
		break;
		
		case MY_SET_SEED:
			curr->seed = arg;
			break;
		default:
			return -ENOTTY;
    }
    return 0;
}

uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed) {

  uint32_t h = seed;
  if (len > 3) {
    const uint32_t* key_x4 = (const uint32_t*) key;
    size_t i = len >> 2;
    do {
      uint32_t k = *key_x4++;
      k *= 0xcc9e2d51;
      k = (k << 15) | (k >> 17);
      k *= 0x1b873593;
      h ^= k;
      h = (h << 13) | (h >> 19);
      h = (h * 5) + 0xe6546b64;
    } while (--i);
    key = (const uint8_t*) key_x4;
  }
  if (len & 3) {
    size_t i = len & 3;
    uint32_t k = 0;
    key = &key[i - 1];
    do {
      k <<= 8;
      k |= *key--;
    } while (--i);
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    h ^= k;
  }
  h ^= len;
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;
  return h;
}
