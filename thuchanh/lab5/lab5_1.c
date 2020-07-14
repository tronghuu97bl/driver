#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define MEM_SIZE 1024
char *kernel_buffer; 
static int sohe10,dd2,dd8,dd16;//do dai 2,...
int q2[100], q8[100], q16[100];
int *so2,*so8,*so16;
char soh2[100], soh8[100],soh16[100];

struct c_driver{
	dev_t dev_num; //device number
	struct class *dev_class;//device class
	struct device *dev;//device
	struct cdev *vcdev;//cdev
}lab5;

static int lab5_open(struct inode *inode, struct file *filp);
static int lab5_release(struct inode *inode, struct file *filp);
static ssize_t lab5_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off);
static ssize_t lab5_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off);
static int docso_h10(int soh10);
static void chuyen10_2(int soh10);
static void chuyen10_8(int q2[]);
static void chuyen10_16(int soh10);

static struct file_operations fops={
	.owner=THIS_MODULE,
	.read=lab5_read,
	.write=lab5_write,
	.open=lab5_open,
	.release=lab5_release,
};

int lab5_open(struct inode *inode, struct file *filp){
	pr_info("mo device file thanh cong");
	return 0;
}
int lab5_release(struct inode *inode, struct file *filp){
	pr_info("dong device file thanh cong");
	return 0;
}
ssize_t lab5_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off){
	copy_to_user(user_buf, soh2, dd2+1);
	copy_to_user(user_buf+100, soh8, dd8+1);
	copy_to_user(user_buf+200, soh16, dd16+1);
	return MEM_SIZE;
}
ssize_t lab5_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off){
	copy_from_user(kernel_buffer, user_buf, len);
	sohe10=docso_h10(0);
	chuyen10_2(sohe10);
	chuyen10_8(q2);
	chuyen10_16(sohe10);
	return len;
}

int docso_h10(int soh10){
	int x;
	x=*kernel_buffer;
	while(x!='\0'){
		soh10= soh10*10+(x-48);
		kernel_buffer++;
		x=*kernel_buffer;
	}
	pr_info("gia tri duoc ghi vao driver la: %d ",soh10);
	return soh10;
}
 void chuyen10_2(int soh10){
 	int kq[100];
 	int x,dem=0,i,dem2=0;
 	while(soh10>0){
 		x=soh10%2;
 		kq[dem++]=x;
 		soh10=soh10/2;
 	}
 	for(i=dem-1;i>=0;i--){
 		q2[dem2++]=kq[i];
 	}
 	dd2=dem2;
 	so2=q2;
 	for(i=0; i<dd2; i++){
		soh2[i]=*so2;
		so2++;
	}
	soh2[dd2]= 2;
 }
 void chuyen10_8(int q2[]){
 	int i,dem=0,x,dem2=0;
 	int kq[100];
	//pr_info("dd2: %d",dd2);
 	for(i=dd2-1;i>=0; i-=3){
 		if(i>=2){
 			x=0; x+=q2[i]; x+=q2[i-1]*2; x+=q2[i-2]*4; kq[dem++]=x;
 		}
 		else{
			if(i==1){x=0; x+=q2[i]; x+=q2[i-1]*2; kq[dem++]=x;}
 			if(i==0){x=0; x+=q2[i]; kq[dem++]=x;}		
		}
 	}
 	dd8=dem;
 	so8=q8;
 	for(i=dem-1;i>=0;i--){
 		q8[dem2++]=kq[i];
 	}
 	for(i=0;i<dd8;i++){
 		soh8[i] = *so8;
 		so8++;
 	}
 	soh8[dd8]=8;
 }
 void chuyen10_16(int soh10){
 	int i,dem=0,x,dem2=0;
 	int kq[100];
 	for(i=dd2-1;i>=0; i-=4){
 		if(i>=3){ x=0; x+=q2[i]; x+=q2[i-1]*2; x+=q2[i-2]*4; x+=q2[i-3]*8; kq[dem++]=x; }
 		else{
 			if(i==2){x=0; x+=q2[i]; x+=q2[i-1]*2; x+=q2[i-2]*4; kq[dem++]=x; } 
			if(i==1){x=0; x+=q2[i]; x+=q2[i-1]*2; kq[dem++]=x;}
 			if(i==0){x=0; x+=q2[i]; kq[dem++]=x;}		
		}
 	}
 	dd16=dem;
 	so16=&q16[0];
 	for(i=dem-1;i>=0;i--){
 		q16[dem2++]=kq[i];
 	}
 	for(i=0;i<dd16;i++){
 		soh16[i]=*so16;
 		so16++;
 	}
 	soh16[dd16]=16;
 }

static int __init lab5_init(void){
	pr_info("heloo \n");
	alloc_chrdev_region(&lab5.dev_num,0,1,"lab5_trantronghuu");
	lab5.dev_class=class_create(THIS_MODULE, "LopthietbiLab5");
	lab5.dev=device_create(lab5.dev_class, NULL, lab5.dev_num,NULL,"thietbilab5");
	kernel_buffer=kmalloc(MEM_SIZE,GFP_KERNEL);
	lab5.vcdev=cdev_alloc();
	cdev_init(lab5.vcdev, &fops);
	cdev_add(lab5.vcdev,lab5.dev_num,1);
	//chuyen10_2(sohe10);
	//pr_info("dd2: %d",dd2);
	//chuyen10_8(q2);
	return 0;
}
static void __exit lab5_exit(void){
	cdev_del(lab5.vcdev);
	kfree(kernel_buffer);
	device_destroy(lab5.dev_class, lab5.dev_num);
	class_destroy(lab5.dev_class);
	pr_info("bye bye\n");
}
module_init(lab5_init);
module_exit(lab5_exit);

MODULE_AUTHOR("Tran Trong Huu");
MODULE_DESCRIPTION("lab5");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");


