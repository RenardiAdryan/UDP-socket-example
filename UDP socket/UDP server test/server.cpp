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


#define GROUP       "224.16.32.75"//224.0.0.1
#define IPSERVER	"172.16.75.105"//"192.168.1.106"
#define KEYTEST     7755        //SHM
#define PORTMULTI   5151
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
    int dataXO;int dataYO;

};
struct paketdariClient esrow1,esrow2,esrow3;


 struct sockaddr_in dest,si;
    int sock;

void *increment1(void *arg){

	while(1){
		     if(recvfrom(sock,&esrow2,sizeof(esrow2),0, NULL,NULL)<0)DieWithError((char *)"recvfrom()");
           else 
              {
               dataYO[0] = esrow2.dataYO;
               dataXO[0] = esrow2.dataXO;
              }
        
        
    }
}
void sendtoALL(){

 
    int sock1;
    if((sock1=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){DieWithError((char *)"socket");}
    memset((char *)&dest,0,sizeof(dest));
    dest.sin_family      = AF_INET;
    dest.sin_addr.s_addr = inet_addr(IPSERVER);
    dest.sin_port        = htons(PORTMULTI);  //JIKA mengirim tidak perlu BIND NETWORK

	if(sendto(sock1,&esrow1,sizeof(esrow1),0,(struct sockaddr *) &dest, sizeof(dest))<0)DieWithError((char *)"sendto() fail");
	close(sock1);
}

int main(int argc, char *argv[]){

   struct ip_mreq     mreq;

    if((sock=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){DieWithError((char *)"socket");}
    memset((char *)&si,0,sizeof(si));
    si.sin_family      = AF_INET;
    si.sin_addr.s_addr = htonl(INADDR_ANY);
    si.sin_port        = htons(PORT2);  
    
    if(bind(sock,(struct sockaddr *)&si,sizeof(si))<0){DieWithError((char *)"bind");}
   
     mreq.imr_multiaddr.s_addr=inet_addr(GROUP);
     mreq.imr_interface.s_addr=htonl(INADDR_ANY);
     
     if(setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))<0)
     	DieWithError((char*)"setsockopt fail");

    pthread_t t1;
    pthread_create(&t1,NULL,increment1,NULL);

    //if(bind(sock,(struct sockaddr *)&dest,sizeof(dest))<0){DieWithError((char *)"bind");}

    int count,count1;
    while(1){
    	 //if(count++>1000) {count=0; esrow1.dataXO++;if(esrow1.dataXO>5000){esrow1.dataXO=0;}}
    	 //if(count1++>100  ) {count1=0;esrow1.dataYO++;if(esrow1.dataYO>5000){esrow1.dataYO=0;}}
          
    	 //sendtoALL();
     

         //printf("dataX0 =  %d || dataY0 = %d \n", esrow1.dataXO,esrow1.dataYO);
        // printf("receive : dataX0 = %d || dataY0 = %d\n", esrow2.dataXO,esrow2.dataYO);


        }
            close(sock);
    }