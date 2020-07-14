#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/crypto.h>

#define MEM_SIZE 1024
#define AES_BLOCK_SIZE 16//16 byte
char *kernel_buffer; 
char xauro[1024],xauma1[1024],matt[1024],xauma2[1024],xauma3[1024],mahv[1024];
int k,tg;
u8 *key, *ma, *gm;
char ma1[1024], gm1[1024],*bq;

struct c_driver{
	dev_t dev_num; //device number
	struct class *dev_class;//device class
	struct device *dev;//device
	struct cdev *vcdev;//cdev
}lab6;

static int lab6_open(struct inode *inode, struct file *filp);
static int lab6_release(struct inode *inode, struct file *filp);
static ssize_t lab6_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off);
static ssize_t lab6_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off);

static struct file_operations fops={
	.owner=THIS_MODULE,
	.read=lab6_read,
	.write=lab6_write,
	.open=lab6_open,
	.release=lab6_release,
};
void encrypt(u8 *buf)  
{    
    struct crypto_cipher *tfm; //tranformation
    int i,count,div,modd; 
	//tinh toan so khoi, AES_BLOCK_SIZE dung la 128bit
    div=strlen(buf)/AES_BLOCK_SIZE;  
    modd=strlen(buf)%AES_BLOCK_SIZE;  
    if(modd>0)  
        div++;  
    count=div;  
    tfm=crypto_alloc_cipher("aes", 0, 16);//allocate single block cipher handle: name, type, mask
    crypto_cipher_setkey(tfm,key,16);//set key for cipher: cipher handle, buffer key, length of key in byte
    for(i=0;i<count;i++)  
    {  
        crypto_cipher_encrypt_one(tfm,ma,buf);//encrypt one block of plaintext:cipher handle, *dst,*src
        buf+=AES_BLOCK_SIZE;
        ma+=AES_BLOCK_SIZE;
    }
    crypto_free_cipher(tfm);//release
}
void decrypt(u8 *buf)
{  
    struct crypto_cipher *tfm;  
    int i,count,div,modd;  
    div=strlen(buf)/AES_BLOCK_SIZE;  
    modd=strlen(buf)%AES_BLOCK_SIZE;  
    if(modd>0)  
        div++;  
    count=div;  
    tfm=crypto_alloc_cipher("aes", 0, 16);  
    crypto_cipher_setkey(tfm,key,16);  
    for(i=0;i<count;i++)  
    {  
        crypto_cipher_decrypt_one(tfm,gm,buf);
        buf+=AES_BLOCK_SIZE;
        gm+=AES_BLOCK_SIZE;
    }
    crypto_free_cipher(tfm);//release
}  
int lab6_open(struct inode *inode, struct file *filp){
	pr_info("mo device file thanh cong");
	return 0;
}
int lab6_release(struct inode *inode, struct file *filp){
	pr_info("dong device file thanh cong");
	return 0;
}
ssize_t lab6_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off){
	if(tg==2){
		copy_to_user(user_buf,xauma1,1024);
	}
	if(tg==3){
		copy_to_user(user_buf,xauma2,1024);
	}
	if(tg==4){
		copy_to_user(user_buf,xauma3,1024);
	}
	if(tg==5){
		copy_to_user(user_buf,ma1,1024);
	}
	if(tg==6){
		copy_to_user(user_buf,gm1,1024);
	}
	if(tg==9){
		copy_to_user(user_buf,bq,1024);
	}
	return MEM_SIZE;
}
ssize_t lab6_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off){
	int i,y;
	char x;
	copy_from_user(kernel_buffer, user_buf, len);
	tg=*kernel_buffer;
	if(tg==1){
		i=0;
		kernel_buffer++;
		while(*kernel_buffer!='\0'){
			xauro[i++]=*kernel_buffer;
			kernel_buffer++;
		}
		xauro[i]='\0';
		//pr_info("%s\n",xauro);
	}
	if(tg==2){//ma hoa dich chuyen
		kernel_buffer++;
		k=*kernel_buffer;
		k=k-48;
		i=0;
		while(xauro[i]!='\0'){
			x=xauro[i];
			x-=97;
			x+=k;
			x=x%26;
			x+=97;
			xauma1[i++]=x;
		}
	}
	if(tg==3){//ma hoa thay the
		kernel_buffer++;
		for(i=0;i<26;i++){
			matt[i]=*kernel_buffer;
			kernel_buffer++;
		}
		i=0;
		while(xauro[i]!='\0'){
			y=xauro[i]-97;
			y=matt[y];
			xauma2[i++]=y;
		}
		//pr_info("%s\n",xauma2);
	}
	if(tg==4){//ma hoa hoan vi
		kernel_buffer++;
		for(i=0;i<26;i++){
			mahv[i]=*kernel_buffer;
			kernel_buffer++;
		}
		i=0;
		while(xauro[i]!='\0'){
			y=xauro[i]-97;
			y=mahv[y];
			xauma3[i++]=y+96;
		}
	}
	if(tg==5){
		kernel_buffer++;
		key=kernel_buffer;
		ma=ma1;
		encrypt(xauro); //ma hoa tu dau
		//pr_info("%s\n",ma1);
	}
	if(tg==6){
		kernel_buffer++;
		key=kernel_buffer;
		ma=ma1; gm=gm1;
		decrypt(ma);//giai ma tu dau	
		//pr_info("%s\n",gm1);
	}
	return len;
}

static int __init lab6_init(void){
	pr_info("heloo \n");
	alloc_chrdev_region(&lab6.dev_num,0,1,"lab6_trantronghuu");
	lab6.dev_class=class_create(THIS_MODULE, "LopthietbiLab6");
	lab6.dev=device_create(lab6.dev_class, NULL, lab6.dev_num,NULL,"thietbilab6");
	kernel_buffer=kmalloc(MEM_SIZE,GFP_KERNEL);
	lab6.vcdev=cdev_alloc();
	cdev_init(lab6.vcdev, &fops);
	cdev_add(lab6.vcdev,lab6.dev_num,1);
	bq="© Bản quyền thuộc về Trần Trọng Hữu, cấm phân phối cho người khác dưới mọi hình thức. :) ©";
	return 0;
}
static void __exit lab6_exit(void){
	cdev_del(lab6.vcdev);
	kfree(kernel_buffer);
	device_destroy(lab6.dev_class, lab6.dev_num);
	class_destroy(lab6.dev_class);
	pr_info("bye bye\n");
}
module_init(lab6_init);
module_exit(lab6_exit);

MODULE_AUTHOR("Tran Trong Huu");
MODULE_DESCRIPTION("lab6");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");


