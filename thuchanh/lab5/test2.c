#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
char write_buf[1024];
long read_buf[10];
int main()
{
        int fd;
        char option;
        printf("**************************************************\n");
        printf("*******user application to test char driver*******\n");
 
        fd = open("/dev/thietbilab5_2", O_RDWR);//mo de doc va ghi
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
 
        while(1) {
                printf("        ****Please Enter the Option******        \n");
                printf("        1. Lay thoi gian tuyet doi, chinh xac den nano giay      \n");
                printf("        2. Lay thoi gian tuyet doi, chinh xac den micro giay      \n");
                printf("        3. Lay thoi gian tuong doi    \n");
                printf("        4. Exit                 \n");
                printf("*************************************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
                                read(fd, read_buf, sizeof(long)*3);
                                printf("Thoi gian tuyet doi: %ld,%ld (chinh xac den nano giay)\n",read_buf[1], read_buf[2]);
                                break;
                        case '2':
                                read(fd, read_buf, sizeof(long)*3);
                                printf("Thoi gian tuyet doi: %ld,%ld (chinh xac den micro giay)\n",read_buf[1], read_buf[2]/1000);
                                break;
                        case '3':
                                read(fd, read_buf, sizeof(long)*4);
								printf("Thoi gian tuong doi: %ld s",read_buf[3]);
                        		break;

                        case '4':
                                close(fd);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
}


