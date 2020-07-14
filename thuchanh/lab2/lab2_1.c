#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

int8_t soh2[50], soh16[50],soh8[50],dem2=0,dem8=0,dem16=0;
int soh10=100;
module_param(soh10,int,0);

void chuyen16_2(int a[]){
	int i;
	for(
}
void chuyen16_8(int a[]){
	
}
void chuyen10_2(int a){
	int i, n,tg[50],dem=0;
	n=a;
	while(n>0){
		tg[dem++]=n%2;
		n=n/2;
	}
	pr_info("so %d sau khi chuyen sang he 2 la: ",soh10);
	for(i=dem-1;i>=0;i--){
		soh2[dem2++]=tg[i];
		pr_info("%d",soh2[dem2-1]);
	}
}
void chuyen10_16(int a){
	int i,dem=0,tg[50],x=0;
	for(i=dem2-1;i>=0;i=i-4){
		 if(i>=3){
		 	x=soh2[i]; x+=soh2[i-1]*2; x+=soh2[i-2]*4; x+=soh2[i-3]*8; tg[dem++] =x;
		 }else{
		 	if(i==2){ x=soh2[i]; x+=soh2[i-1]*2; x+=soh2[i-2]*4; tg[dem++] =x;}
		 	if(i==1){ x=soh2[i]; x+=soh2[i-1]*2; tg[dem++] =x;}
		 	if(i==0){ x=soh2[i]; tg[dem++] =x;}
		 }	
	}
	pr_info("so %d sau khi chuyen sang he 16 la: ",soh10);
	for(i=dem-1;i>=0;i--){
		soh16[dem16++]=tg[i];
		if(soh16[dem16-1]<=9){
			pr_info("%d",soh16[dem16-1]);
		}else{
			if(soh16[dem16-1]==10) pr_info("A");
			if(soh16[dem16-1]==11) pr_info("B");
			if(soh16[dem16-1]==12) pr_info("C");
			if(soh16[dem16-1]==13) pr_info("D");
			if(soh16[dem16-1]==14) pr_info("E");
			if(soh16[dem16-1]==15) pr_info("F");
		}
	}
}
void chuyen8_16(int a[]){

}
void chuyen2_8(int8_t a[]){
	int i,dem=0,tg[50],x=0;
	for(i=dem2-1;i>=0;i=i-3){
		 if(i>=2){
		 	//tinh bt
		 	x=soh2[i]; x+=soh2[i-1]*2; x+=soh2[i-2]*4; tg[dem++] =x;
		 }else{
		 	if(i==1){ x=soh2[i]; x+=soh2[i-1]*2; tg[dem++] =x;}
		 	if(i==0){ x=soh2[i]; tg[dem++] =x;}
		 }	
	}
	pr_info("so %d sau khi chuyen sang he 8 la: ",soh10);
	for(i=dem-1;i>=0;i--){
		soh8[dem8++]=tg[i];
		pr_info("%d",soh8[dem8-1]);
	}
}
void chuyen2_10(int8_t a[]){
	int i, tong=0,tg=1;
	for(i=dem2-1;i>=0;i--){
		tong+=soh2[i]*tg;
		tg*=2;
	}
	pr_info("so sau khi chuyen tu he 2 sang he 10 la: %d \n",tong);
}
static int __init lab2_init(void){
	pr_info("hello\n");
	chuyen10_2(soh10);
	chuyen2_8(soh2);
	chuyen2_10(soh2);
	chuyen10_16(soh10);
	return 0;
}
static void __exit lab2_exit(void){
	pr_info("exit\n");
}

module_init(lab2_init);
module_exit(lab2_exit);

MODULE_AUTHOR("");
MODULE_VERSION("");
MODULE_DESCRIPTION("");
MODULE_VERSION("");

