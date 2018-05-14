#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

int s1=0,s,inputread;
int threadcount;
struct sockaddr_in sadrs;
int length=sizeof(sadrs);

struct client_struct{
int startvalue;
int endvalue;
int ppstartvalue;
int ppendvalue;
};

void *transfer(void *input)
{
 char *b1=(char *)malloc(s*sizeof(char));
 int x,y;
 struct client_struct v=*((struct client_struct*)input);
 int start_add=v.startvalue;
 int end_add=v.endvalue;
for(x=start_add;x<end_add;x+=s)
 {
 memset(b1,'6',s);
 send(s1, b1, s, 0);
 }
}


void *transferpingpong(void *input)
{
 char *b1=(char *)malloc(s*sizeof(char));
 int x,y;
 struct client_struct v=*((struct client_struct*)input);
  int start_add=v.ppstartvalue;
 int end_add=v.ppendvalue;
 for(int i=0;i<1000;i++)
 {
  memset(b1,'6',s);
 send(s1, b1, s, 0);
 inputread=recv(s1, b1, s, 0);
  }
}


void *transferudp(void *input)
{
 char *b1=(char *)malloc(s*sizeof(char));
 int x,y;
 struct client_struct v=*((struct client_struct*)input);
 int start_add=v.startvalue;
 int end_add=v.endvalue;
 for(x=start_add;x<end_add;x+=s)
{
 memset(b1,'6',s);
 sendto(s1, b1, s, 0,&sadrs,length);
  }
}


void *transferpingpongudp(void *input)
{
 char *b1=(char *)malloc(s*sizeof(char));
 int x,y;
 struct client_struct v=*((struct client_struct*)input);
  int start_add=v.ppstartvalue;
 int end_add=v.ppendvalue;
for(x=0;x<1000;x++)
{
 memset(b1,'6',s);
 sendto(s1, b1, s, 0, &sadrs,length);
 inputread=recvfrom(s1, b1, s, 0, &sadrs,length);
  }
}


int main(int argc,int **argv[])
{
    threadcount=atoi(argv[1]);
    char *block=(char *)argv[2];
    char *ap=(char *)argv[3];
    if(block[1]=='b')
    {
      s=1;
     }
    else if(block[1]=='k')
    {
        s=1*1024;
        
    }
     else if(block[1]=='2')
    {
        s=32*1024;
     }
   clock_t trestart,trestop,trestart1,trestop1;
   int ac,u,v;
  double bytestransfer1,bytestransfer2;
  pthread_t threads[threadcount];
  int initcount=0,initcount2=0;
  int totaldata=1000000000;
  int spreaddata=1000000000/threadcount;
  int r2=1000000000/threadcount;
  int r3=1000000000/threadcount;
  int totalppdata=1000000;
  int spreadppdata=1000000/threadcount;
  int r4=1000000/threadcount;
  int r5=1000000/threadcount;
 struct client_struct cs;
 cs.startvalue=initcount;
 cs.endvalue=r3;
 cs.ppstartvalue=initcount2;
 cs.ppendvalue=r4;
 switch(ap[0])
{
    case 't':
    printf("TCP Connection\n");
          if ((s1 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }  
    memset(&sadrs, '0', sizeof(sadrs));  
    sadrs.sin_family = AF_INET;
    sadrs.sin_port = htons(8080);      
    if(inet_pton(AF_INET, "127.0.0.1", &sadrs.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(s1, (struct sockaddr *)&sadrs, sizeof(sadrs)) < 0)

    {
        printf("\nConnection Failed \n");
        return -1;
    }
     if(s==1)
    {
    printf("Ping pong\n");
    trestart1=clock();
    for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,&transferpingpong,(void *)&cs);
    sleep(1);
    initcount2=initcount2+spreadppdata;
    cs.ppstartvalue=initcount2;
    r5=r4+r5;
    cs.ppendvalue=r5;
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
     trestop1=clock();
     double totaltime=trestop1-trestart1;
      double total1=(totaltime/CLOCKS_PER_SEC);
     bytestransfer1=(1/total1)/1000;
     printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
     printf("Latency:%lf ms\n",bytestransfer1);
    printf("********************\n");
     }
    else{
    trestart=clock();
    for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,&transfer,(void *)&cs);
    sleep(1);
    initcount=initcount+spreaddata;
    cs.startvalue=initcount;
    r3=r3+r2;
    cs.endvalue=r3;
    if (ac) {
     printf("Could not create thread %d \n", v);
     }
     }
     for (u = 0; u < threadcount; u++) {
     ac = pthread_join(threads[u], NULL);
     if (ac) {
     printf("Could not join thread %d \n",u);
     }
     }
    trestop=clock();
    double tot1=trestop-trestart;
   double total1=(tot1/CLOCKS_PER_SEC);
     bytestransfer1=(1*1000/total1);
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Mbps:%lf\n",bytestransfer1);
    printf("********************\n");
     }
    break;

   case 'u':
   printf("UDP Connection\n");
      if ((s1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }  
    memset(&sadrs, '0', sizeof(sadrs));  
    sadrs.sin_family = AF_INET;
    sadrs.sin_port = htons(8080);      
    if(inet_pton(AF_INET, "127.0.0.1", &sadrs.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(s1, (struct sockaddr *)&sadrs, sizeof(sadrs)) < 0)

    {
        printf("\nConnection Failed \n");
        return -1;
    }
      if(s==1)
    {
    trestart=clock();
    for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,&transferpingpongudp,(void *)&cs);
    sleep(1);
    initcount2=initcount2+spreadppdata;
    cs.ppstartvalue=initcount2;
    r5=r4+r5;
    cs.ppendvalue=r5;
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
    trestop=clock();
    double tot2=trestop-trestart; 
    double total2=(tot2/CLOCKS_PER_SEC);
    bytestransfer2=(1/total2)/100000;
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Latency:%lf\n",bytestransfer2);
    printf("********************\n");
    }
    else{
    trestart=clock();
    for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,&transferudp,(void *)&cs);
        sleep(1);
    initcount=initcount+spreaddata;
    cs.startvalue=initcount;
    r3=r3+r2;
    cs.endvalue=r3;
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
    trestop=clock();
    double tot2=trestop-trestart;
    double total2=(tot2/CLOCKS_PER_SEC);
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    bytestransfer2=(1*1000/total2);
    printf("Mbps:%lf\n",bytestransfer2);
    printf("********************\n");
     }
   break;
} 
return 0;
}



