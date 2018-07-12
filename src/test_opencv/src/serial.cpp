#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#define BAUNDRATE B9600 
#define MODEMDEVICE "/dev/serial/by-id/usb-Hokuyo_Data_Flex_for_USB_URG-Series_USB_Driver-if00"
#define _POSIX_SOURCE 1
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;

int main(){
  int fd,c,res;
  struct termios oldtio,newtio;
  char buf[255]={'S','C','I','P','2','.','0','\n'};

  fd = open(MODEMDEVICE,O_WRONLY |O_NOCTTY);
  if(fd<0){
    printf("hoge?\n");
    perror(MODEMDEVICE);
    return -1;
  }

  tcgetattr(fd,&oldtio);

  bzero(&newtio,sizeof(newtio));
  newtio.c_cflag=BAUNDRATE|CRTSCTS|CS8|CLOCAL|CREAD;
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag=0;

  newtio.c_lflag=0;

  newtio.c_cc[VTIME]=0;
  newtio.c_cc[VMIN]=0;

    tcflush(fd,TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
    int ret;

    if((ret = write(fd,buf,255))< 1){
      printf("hogehoge-----hoge?\n");
      return -1;
    }
    else if(ret == 0){
      printf("hogehoge??????");
    }
    


    tcsetattr(fd,TCSANOW,&oldtio);
    close(fd);

    printf("hogehoge\n");

    return 0;
}
