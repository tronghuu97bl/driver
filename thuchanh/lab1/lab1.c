#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>

int aa[100]={1,2,3,4,5,6,7,8,9,10};
int a=9,b=6,min=1000,max=0,tbc=0,spt;
int matrix[100]={1,2,3,4,-1,-2,-3,-4,6,3,1,8,-3,-3,-2,-1};
int c_mt=4,sptt=16;

module_param(a,int,0);
module_param(b,int,0);
//module_param_array(aa,int,NULL,0000);
module_param_array(aa,int,&spt,0000);
module_param_array(matrix,int,&sptt,0000);
module_param(c_mt,int,0);
void tong_chuoi(int a[]){
	int i;
	for(i=0;i<10;i++){
		tbc+=a[i];
	}
	pr_info("tong cac phan tu trong chuoi so la: %d \n",tbc);
}
void ucln(int a, int b){
	int tg,a1,a2;
	a1=a;a2=b;
	while(b>0){
		tg=a;
		a=b;
		b=tg%b;
	}
	pr_info("UCLN cua %d va %d la: %d\n",a1,a2,a);
}
void tim_min_max(int a[]){
	int i;
	for(i=0; i<10;i++){
		if(a[i]<min) min=a[i];
		if(a[i]>max) max=a[i];	
	}
	pr_info("min la: %d max la: %d\n",min,max);
}
void tb_cong(int a[]){
	if(spt!=0){
		tbc=tbc/spt;	
	}else{
		tbc=tbc/10;
	}
	pr_info("Tbc cua chuoi so la: %d\n",tbc);
}
void matran(int a[]){
	int i,tong=0,spt_am=0,spt_duong=0,min1=999,min2=999,max1=-999,max2=-999,tong_chan=0,tong_le=0,dc,dp;
	for(i=0;i<sptt;i++){
		tong+=a[i];
		if(a[i]<0) spt_am++;
		if(a[i]>0) spt_duong++;
		if(a[i]%2==0) tong_chan+=a[i]; else tong_le+=a[i];
	}
	dc=c_mt+1;
	dp=c_mt-1;
	for(i=0;i<sptt;i+=dp){
		if(a[i]<min1) min1=a[i];
		if(a[i]>max1) max1=a[i];
	}
	for(i=c_mt-1;i<sptt;i+=dc){
		if(a[i]<min2) min2=a[i];
		if(a[i]>max2) max2=a[i];
	}
	pr_info("tong cac phan tu trong ma tran la: %d",tong);
	pr_info("so phan tu am la: %d",spt_am);
	pr_info("so phan tu duong la: %d",spt_duong);
	pr_info("tong cac phan tu le la: %d",tong_le);
	pr_info("tong cac phan tu chan la: %d",tong_chan);
	pr_info("min tren cheo 9: %d",min2);
	pr_info("max tren cheo 9: %d",max2);
	pr_info("min tren cheo phu: %d",min1);
	pr_info("max tren cheo phu: %d\n",max1);
}
static int __init lab1_init(void){
	pr_info("hello.\n");
	tong_chuoi(aa);
	ucln(a,b);
	tim_min_max(aa);
	tb_cong(aa);
	matran(matrix);
	return 0;
}
static void __exit lab1_exit(void){
	pr_info("exit\n");
}
module_init(lab1_init);
module_exit(lab1_exit);

MODULE_DESCRIPTION("lab1");
MODULE_AUTHOR("TRAN TRONG HUU");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
