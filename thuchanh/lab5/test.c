	#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
char write_buf[1024];
char read_buf[1024];
int abc;
int main()
{
        int fd;
        char option;
        printf("**************************************************\n");
        printf("*******user application to test char driver*******\n");
 
        fd = open("/dev/thietbilab5", O_RDWR);//mo de doc va ghi
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
 
        while(1) {
                printf("        ****Please Enter the Option******        \n");
                printf("        1. Write a number decimal to device      \n");
                printf("        2. Read a number binary from device      \n");
                printf("        3. Read a number octal from device       \n");
                printf("        4. Read a number hexadecimal from device \n");
                printf("        5. Exit                 \n");
                printf("*************************************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
                                printf("Enter the number decimal to write into driver :");
                                scanf("  %s", write_buf);
                                printf("Data Writing ...");
                                write(fd, write_buf, strlen(write_buf)+1);
                                printf("Done!\n");
                                break;
                        case '2':
                                printf("READ BINARY NUMBER ...");
                                read(fd, read_buf, 100);
								int i=0;
								while(read_buf[i]!= 2){
									printf("%d ",read_buf[i]);
									i++;
								}
								printf("Done!\n");
                                break;
                        case '3':
                        		printf("READ OCTAL NUMBER ...");
                                read(fd, read_buf, 100);
								i=100;
								while(read_buf[i]!= 8){
									printf("%d ",read_buf[i]);
									i++;
								}
								printf("Done!\n");
                        		break;
						case '4':
								printf("READ HEXADECIMAL NUMBER ...");
                                read(fd, read_buf, 100);
								i=200;
								while(read_buf[i]!= 16){
									if(read_buf[i]<10){
										printf("%d ",read_buf[i]);
									}else{
										if(read_buf[i]==10) printf("A ");
										if(read_buf[i]==11) printf("B ");
										if(read_buf[i]==12) printf("C ");
										if(read_buf[i]==13) printf("D ");
										if(read_buf[i]==14) printf("E ");
										if(read_buf[i]==15) printf("F ");
									}
									i++;
								}
								printf("Done!\n");
								break;
                        case '5':
                                close(fd);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        //close(fd);
}


