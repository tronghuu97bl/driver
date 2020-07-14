#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
//#include <linux/jiffies.h>
#define MEM_SIZE 1024
char *kernel_buffer;
long aa[10];
unsigned long js,jf;

struct driver_lab5{
	dev_t dev_num; //device number
	struct class *dev_class; //class device
	struct device *dev; //device
	struct cdev *c_dev; 
}lab5;

static int open_lab5(struct inode *inode, struct file *filp);
static int release_lab5(struct inode *inode, struct file *filp);
static ssize_t read_lab5(struct file *filp, char __user *user_buf, size_t len, loff_t *off);
static ssize_t write_lab5(struct file *filp, const char __user *user_buf, size_t len, loff_t *off);

static struct file_operations fops={
	.owner=THIS_MODULE,
	.open=open_lab5,
	.release=release_lab5,
	.read=read_lab5,
	.write=write_lab5,
};

int open_lab5(struct inode *inode, struct file *filp){
	return 0;
}
int release_lab5(struct inode *inode, struct file *filp){
	return 0;
}
ssize_t read_lab5(struct file *filp, char __user *user_buf, size_t len, loff_t *off){
	struct timespec64 ts;
	struct timeval tv;
	ktime_get_real_ts64(&ts);
	//pr_info("time: %lld , %ld\n", ts.tv_sec, ts.tv_nsec);
	aa[1]=ts.tv_sec;
	aa[2]=ts.tv_nsec;
	jf=jiffies;
	jiffies_to_timeval(jf-js,&tv);
	aa[3]=tv.tv_sec;
	pr_info("%ld %ld %ld", aa[1], aa[2], aa[3]);
	copy_to_user(user_buf,aa,sizeof(long)*10);
	return MEM_SIZE;
}
ssize_t write_lab5(struct file *filp, const char __user *user_buf, size_t len, loff_t *off){
	return len;
}

static int __init lab5_init(void){
	pr_info("heloo \n");
	alloc_chrdev_region(&lab5.dev_num,0,1,"lab5_2trantronghuu");
	lab5.dev_class=class_create(THIS_MODULE, "LopthietbiLab5_2");
	lab5.dev=device_create(lab5.dev_class, NULL, lab5.dev_num,NULL,"thietbilab5_2");
	kernel_buffer=kmalloc(MEM_SIZE,GFP_KERNEL);
	lab5.c_dev=cdev_alloc();
	cdev_init(lab5.c_dev, &fops);
	cdev_add(lab5.c_dev,lab5.dev_num,1);
	js=jiffies;
	return 0;
}
static void __exit lab5_exit(void){
	cdev_del(lab5.c_dev);
	kfree(kernel_buffer);
	device_destroy(lab5.dev_class, lab5.dev_num);
	class_destroy(lab5.dev_class);
	pr_info("bye bye\n");
	pr_info("Bye bye!");
}
module_init(lab5_init);
module_exit(lab5_exit);
MODULE_AUTHOR("TRAN NGUYEN TRUC LINH");
MODULE_DESCRIPTION("lay time");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");






