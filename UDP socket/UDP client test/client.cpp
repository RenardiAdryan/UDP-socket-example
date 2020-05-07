#include <stdio.h>      /* for printf() and fprintf() */
#include <stdbool.h>
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <pthread.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>


#define GROUP       "172.16.190.101" 
#define KEYTEST     7755        //SHM
#define PORTMULTI   5159
#define PORT1       5114        //STRIKER1
#define PORT2       5112        //STRIKER2
#define PORT3       5113        //KIPER
#define ECHOMAX     4

unsigned int dataXO[3],dataYO[3];

void DieWithError(char *errorMessage) /* External error handling function */
{
    perror(errorMessage);
}


struct paketdariClient
{
    int dataXO;int dataYO;int dataTO;

};
struct paketdariClient esrow1,esrow2,esrow3;



int main(int argc, char *argv[]){
    struct sockaddr_in si;
    int sock;

    if((sock=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){DieWithError((char *)"socket");}

    memset((char *)&si,0,sizeof(si));
    si.sin_family      = AF_INET;
    si.sin_addr.s_addr = htonl(INADDR_ANY);
    si.sin_port        = htons(PORT2); 
    
    if(bind(sock,(struct sockaddr *)&si,sizeof(si))<0){DieWithError((char *)"bind");}
    


  /*  struct sockaddr_in dest;
    memset((char *)&dest,0,sizeof(dest));
    dest.sin_family      = AF_INET;
    dest.sin_addr.s_addr = inet_addr(GROUP);
    dest.sin_port        = htons(PORT2);  //JIKA mengirim tidak perlu BIND NETWORK
*/




    int count,count1;
    while(1){
         //if(count++>100  ) {count=0;esrow2.dataXO++; if(esrow2.dataXO>5000){esrow2.dataXO=0;}}
         //if(count1++>1000 ) {count1=0;esrow2.dataYO++;if(esrow2.dataYO>5000){esrow2.dataYO=0;}}
        
         //if(sendto(sock,&esrow2,sizeof(esrow2),0,(struct sockaddr *) &dest, sizeof(dest))<0) DieWithError((char *)"sendto() fail");
       if(recvfrom(sock,&esrow1,sizeof(esrow1),0,NULL,NULL)<0)DieWithError((char *)"recvfrom()");
         else 
             {
              dataXO[0] = esrow1.dataXO;
              dataYO[0] = esrow1.dataYO;
             }
  
        

        printf("receive : dataX0 = %d || dataY0 = %d || dataT0 = %d \n", esrow1.dataXO, esrow1.dataYO,esrow1.dataTO);
                                                                                               


        }
            close(sock);
    }

