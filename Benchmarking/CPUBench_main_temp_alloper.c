#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

struct timeval timer;

struct cpupar{
int tc;
int input;
char precision;
int startvalue;
int endvalue;
};

void *operationsqp(void* m)
{
    char qs='8';
    char qt='2';
    char c=10,d=10,e=10;
    struct cpupar v=*((struct cpupar*)m);
    int proceedfrom=v.startvalue;
    int endat=v.endvalue;
    //printf("Start:%d and End:%d\n",proceedfrom,endat);
    for(int j=proceedfrom;j<endat;j++)
     {
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt; 
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt;
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt;
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt;
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt; 
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt; 
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt;
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt;
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt;
        c+=qs+qt*1;d+=qs-qt;e+=qs*qt;
     }
    printf("Values in qp are %c %c %c\n",c,d,e);
    return 0;
}

void *operationshp(void* m)
{
    short int a=10,b=5;
    short int c=10,d=10,e=10;    
    struct cpupar v=*((struct cpupar*)m);
    int proceedfrom=v.startvalue;
    int endat=v.endvalue;
    for(int j=proceedfrom;j<endat;j++)
     {
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;  
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;  
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;     
    }
    printf("Values in hp are %d %d %d\n",c,d,e);
    return 0;
}

void *operationssp(void* m)
{
    int a=10,b=5;
    int c=10,d=10,e=10;
    struct cpupar v=*((struct cpupar*)m);
    int proceedfrom=v.startvalue;
    int endat=v.endvalue;
    for(int j=proceedfrom;j<endat;j++)
    {
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;  
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;  
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;     
     }    
    printf("Values in sp are %d %d %d\n",c,d,e);
    return 0;
}


void *operationsdp(void* m)
{
    double a=10.55,b=5.68;
    double c=10.00,d=10.00,e=10.00;
    struct cpupar v=*((struct cpupar*)m);
    int proceedfrom=v.startvalue;
    int endat=v.endvalue;
    for(int j=proceedfrom;j<endat;j++)
    {
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;  
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;  
        c+=a+b*1;d+=a-b;e+=a*b; 
        c+=a+b*1;d+=a-b;e+=a*b;         
    }    
    printf("Values in dp are %f %f %f\n",c,d,e);
    return 0;
}

int main(int argc, char *argv[])  
{
    int t,ac;    
    int threadcount=atoi(argv[1]);
    char *prec=(char *)argv[2];
    double starttime,endtime,totaltime,totalavg;
    if(argc<2)
    {
    printf("Not enough parameters \n");
    }
    //printf("No of threads is %d \n",threadcount);    
    pthread_t threads[threadcount];
    long int r1=10000000000;
    int r=(100000000/threadcount);
    int r2=(100000000/threadcount);
    int r3=(100000000/threadcount);
    int initcount=0;
    struct cpupar cpu;
    cpu.tc=threadcount;
    cpu.input=r;
    cpu.precision=prec;
    cpu.startvalue=initcount;
    cpu.endvalue=r3;
    switch(prec[0])
   { 
   case 'q'://qp
     printf("Welcome to Quater Precision\n");
    for(int i=0;i<3;i++)
    {
    gettimeofday(&timer,NULL);
    starttime=timer.tv_sec+(timer.tv_usec/1000000.0);
    for (t = 0; t < threadcount; t++) {
    ac = pthread_create(&threads[t],NULL,operationsqp,(void *) &cpu);
    sleep(1);
    initcount=initcount+r;
    cpu.startvalue=initcount;
    r3=r3+r2;
    cpu.endvalue=r3; 
    if (ac) {
     printf("Could not create thread %d \n", t);
     }
     }
     for (t = 0; t < threadcount; t++) {
     ac = pthread_join(threads[t], NULL);
     if (ac) {
     printf("Could not join thread %d \n", t);
     }
     }
    gettimeofday(&timer,NULL);
    endtime=timer.tv_sec+(timer.tv_usec/1000000.0);
    totaltime=endtime-starttime;
    totalavg=((r1)/(totaltime*1000000000))*5;
    printf("********************\n");
    printf("Parameters TC Prec\n");
    printf("Parameters %d %s\n",threadcount,prec);
    printf("gigaops:%lf\n",totalavg);
    printf("********************\n");
   }
    break;

    case 'h'://hp
     printf("Welcome to Half Precision\n");
     for(int i=0;i<3;i++)
    {
    gettimeofday(&timer,NULL);
    starttime=timer.tv_sec+(timer.tv_usec/1000000.0);
    for (t = 0; t < threadcount; t++) {
    ac = pthread_create(&threads[t],NULL,operationshp,(void *) &cpu);
    sleep(1);
    initcount=initcount+r;
    cpu.startvalue=initcount; 
    r3=r3+r2;
    cpu.endvalue=r3;
     if (ac) {
     printf("Could not create thread %d \n", t);
     }
     }
     for (t = 0; t < threadcount; t++) {
     ac = pthread_join(threads[t], NULL);
     if (ac) {
     printf("Could not join thread %d \n", t);
     }
     }
    gettimeofday(&timer,NULL);
    endtime=timer.tv_sec+(timer.tv_usec/1000000.0);
    totaltime=endtime-starttime;
    totalavg=((r1)/(totaltime*1000000000))*5;
    printf("********************\n");
    printf("Parameters TC Prec\n");
    printf("Parameters %d %s\n",threadcount,prec);
    printf("gigaops:%lf\n",totalavg);
    printf("********************\n");
    }
    break;
    
   case 's'://sp
     printf("Welcome to Single Precision\n");
     for(int i=0;i<3;i++)
    {
    gettimeofday(&timer,NULL);
    starttime=timer.tv_sec+(timer.tv_usec/1000000.0);
    for (t = 0; t < threadcount; t++) {
    ac = pthread_create(&threads[t],NULL,operationssp,(void *) &cpu);
    sleep(1);
    initcount=initcount+r;
    cpu.startvalue=initcount; 
    r3=r3+r2;
    cpu.endvalue=r3;    
     if (ac) {
     printf("Could not create thread %d \n", t);
     }
     }
     for (t = 0; t < threadcount; t++) {
     ac = pthread_join(threads[t], NULL);
     if (ac) {
     printf("Could not join thread %d \n", t);
     }
     }
    gettimeofday(&timer,NULL);
    endtime=timer.tv_sec+(timer.tv_usec/1000000.0);
    totaltime=endtime-starttime;
    totalavg=((r1)/(totaltime*1000000000))*5;
    printf("********************\n");
    printf("Parameters TC Prec\n");
    printf("Parameters %d %s\n",threadcount,prec);
    printf("gigaops:%lf\n",totalavg);
    printf("********************\n");
    }
    break;

    case 'd'://dp
     printf("Welcome to Double Precision\n");
     for(int i=0;i<3;i++)
    {
    gettimeofday(&timer,NULL);
    starttime=timer.tv_sec+(timer.tv_usec/1000000.0);
    for (t = 0; t < threadcount; t++) {
    ac = pthread_create(&threads[t],NULL,operationsdp,(void *) &cpu);
    sleep(1);
    initcount=initcount+r;
    cpu.startvalue=initcount; 
    r3=r3+r2;
    cpu.endvalue=r3;
     if (ac) {
     printf("Could not create thread %d \n", t);
     }
     }
     for (t = 0; t < threadcount; t++) {
     ac = pthread_join(threads[t], NULL);
     if (ac) {
     printf("Could not join thread %d \n", t);
     }
     }
    gettimeofday(&timer,NULL);
    endtime=timer.tv_sec+(timer.tv_usec/1000000.0);
    totaltime=endtime-starttime;
    totalavg=((r1)/(totaltime*1000000000))*5;
    printf("********************\n");
    printf("Parameters TC Prec\n");
    printf("Parameters %d %s\n",threadcount,prec);
    printf("gigaops:%lf\n",totalavg);
    printf("********************\n");
    }
    break;
   }
    return 0;
}
  
