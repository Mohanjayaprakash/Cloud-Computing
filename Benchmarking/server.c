#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

int inputread=1,nsocket,fserver;
int s=0,data;
struct sockaddr_in *restrict adrs;
struct sockaddr_in *restrict adrsnew;
int length1=sizeof(adrsnew);
int length=sizeof(adrs);

void *getinfo(void *data)
{
char *b1 =(char *)malloc(s*sizeof(char));
int nsoc=data;
while(inputread>0)
{
  inputread=recv(nsoc, b1, s, 0);
}
}

void *getinfopingpong(void *data)
{
char *b1 =(char *)malloc(s*sizeof(char));
int nsoc=data;
while(inputread>0)
{ 
 inputread=recv(nsoc, b1, s, 0);
 memset(b1,'8',s);
 send(nsoc,b1,s,0);
}
}

void *getinfoudp(void *data)
{
char *b1 =(char *)malloc(s*sizeof(char));
int nsoc=data;
while(inputread>0)
{
  inputread=recvfrom(nsoc, b1, s, 0,adrs,length);
}
}

void *getinfopingpongudp(void *data)
{
char *b1 =(char *)malloc(s*sizeof(char));
char *b2 =(char *)malloc(s*sizeof(char));
int nsoc=data;
while(inputread>=0)
{
  inputread=recvfrom(nsoc, b1, s, 0,&adrsnew,&length1);
 memset(b2,'8',s);
 sendto(nsoc, b2, s, 0, &adrsnew,length1);
}
}


int main(int argc,int **argv[])
{
 clock_t trestart,trestop;
 double bytestransfer,bytestransfer1;
  int v,u,ac,p=1;
 int threadcount=atoi(argv[1]);
 char *block=(char *)argv[2];
 char *ap=(char *)argv[3];
     if(block[1]=='b')
    {
      s=1;
    }
 else if(block[0]=='1')
 {
  s=1*1024;
}
   else if(block[0]=='3')
    {
        s=32*1024;
    }
   switch(ap[0])
  {
   case 't':
   printf("TCP connection\n");
   struct sockaddr_in adrs;
   int length=sizeof(adrs);
     if ((fserver = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
     if (setsockopt(fserver, SOL_SOCKET, SO_REUSEADDR,
                                                  &p, sizeof(p)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    adrs.sin_family = AF_INET;
    adrs.sin_addr.s_addr = INADDR_ANY;
    adrs.sin_port = htons( 8080 );
     if (bind(fserver, (struct sockaddr *)&adrs, 
                                 sizeof(adrs))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(fserver, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((nsocket = accept(fserver, (struct sockaddr *)&adrs, 
                       (socklen_t*)&length))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    if(s==1)
   {
   printf("Ping pong\n");
   pthread_t threads[threadcount];
    for (v = 0; v < threadcount; v++) {
     ac = pthread_create(&threads[v],NULL,&getinfopingpong,(void *) nsocket);  
     if (ac) {
     printf("Could not create thread %d \n", u);
     }
     }
     for (u = 0; u < threadcount; u++) {
     ac = pthread_join(threads[u], NULL);
     if (ac) {
     printf("Could not join thread %d \n",u);
     }
     }
   }
else{
    pthread_t threads[threadcount];
    for (v = 0; v < threadcount; v++) {
     ac = pthread_create(&threads[v],NULL,&getinfo,(void *) nsocket);  
      if (ac) {
     printf("Could not create thread %d \n", u);
     }
     }
     for (u = 0; u < threadcount; u++) {
      ac = pthread_join(threads[u], NULL);
      if (ac) {
     printf("Could not join thread %d \n",u);
     }
     }
   }
   break;
  
   case 'u':
   printf("UDP Connection\n");
    if ((fserver = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(fserver, SOL_SOCKET, SO_REUSEADDR,
                                                  &p, sizeof(p)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    adrs.sin_family = AF_INET;
    adrs.sin_addr.s_addr = INADDR_ANY;
    adrs.sin_port = htons( 8080 );
      
   if (bind(fserver, (struct sockaddr *)&adrs, 
                                 sizeof(adrs))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
     if(s==1)
   {
   printf("Ping pong\n");
   pthread_t threads[threadcount];
    for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,&getinfopingpongudp,(void *) fserver); 
    if (ac) {
     printf("Could not create thread %d \n", u);
     }
     }
     for (u = 0; u < threadcount; u++) {
     ac = pthread_join(threads[u], NULL);
     if (ac) {
     printf("Could not join thread %d \n",u);
     }
     }
   }
else{
    pthread_t threads[threadcount];
    for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,&getinfoudp,(void *) fserver);  
     printf("Fserver Value:%d\n",fserver);
    if (ac) {
     printf("Could not create thread %d \n", u);
     }
     }
     for (u = 0; u < threadcount; u++) {
     ac = pthread_join(threads[u], NULL);
     if (ac) {
     printf("Could not join thread %d \n",u);
     }
     }
   }
}
  return 0;
}     

