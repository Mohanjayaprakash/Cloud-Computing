#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#define _GNU_SOURCE

struct disk_struct{
     int tc;
     int bs;
     int acp;
     int work;
     int* arraystart;
     int  startvalue;
     int  endvalue;
     int* arraydest;
};

void *diskoperationssqwr(void* m)
{
   struct disk_struct v=*((struct disk_struct*)m);
   FILE *fileseqwrite;
   int start_add=v.startvalue;
   int end_add=v.endvalue;
   //printf("Start Value:%d\n",start_add);
   //printf("End Value:%d\n",end_add);
   for(int p=0;p<10;p++)
    {
        fileseqwrite = fopen("/tmp/Diskbench.txt","w");
        int fdint=fileno(fileseqwrite);
        for(int k=start_add;k<end_add;k+=v.bs)
       {       
         pwrite(fdint,v.arraystart[k],v.bs,k);
       } 
      fclose(fileseqwrite);
    }
    return 0;
  }

void *diskoperationssqre(void* m)
{
   struct disk_struct v=*((struct disk_struct*)m);
   FILE *fileseqwrite;
   int start_add=v.startvalue;
   int end_add=v.endvalue;
   for(int p=0;p<10;p++) 
    {
        fileseqwrite = fopen("/tmp/Diskbench.txt","w");
        int fdint=fileno(fileseqwrite);
        for(int k=start_add;k<end_add;k+=v.bs)
       {       
          pread(fdint,&v.arraydest[k],v.bs,k);
       } 
      fclose(fileseqwrite);
    }
    return 0;
}

void *diskoperationsrawr(void* m)
{
   struct disk_struct v=*((struct disk_struct*)m);
   FILE *fileseqwrite;
   int start_add=v.startvalue;
   int end_add=v.endvalue;
   for(int p=0;p<10;p++)
    {
        fileseqwrite = fopen("/tmp/Diskbench.txt","w");
        int fdint=fileno(fileseqwrite);
        for(int k=start_add;k<end_add;k+=v.bs)
       {       
        int interval=((end_add-v.bs)-start_add)+1;
        int rage=start_add+rand()%interval;
        pwrite(fdint,v.arraystart[rage],v.bs,k);
       } 
      fclose(fileseqwrite);
    }
    return 0;
}

void *diskoperationsrare(void* m)
{
   struct disk_struct v=*((struct disk_struct*)m);
   FILE *fileseqwrite;
   int start_add=v.startvalue;
   int end_add=v.endvalue;    
    for(int p=0;p<10;p++)
    {
         fileseqwrite = fopen("/tmp/Diskbench.txt","w");
        int fdint=fileno(fileseqwrite);
        for(int k=start_add;k<end_add;k+=v.bs)
       {       
       int interval=((end_add-v.bs)-start_add)+1;
       int rage=start_add+rand()%interval;
        pread(fdint,&v.arraydest[k],v.bs,rage);
       } 
      fclose(fileseqwrite);
     }
   return 0;
}


int main(int argc, char **argv[])
{
    int u,v,ac,s;
    clock_t trestart,trestop;
    double bytestransfer;
    int threadcount=atoi(argv[1]);
    char *block=(char *)argv[2];
    char *ap=(char *)argv[3];
    pthread_t threads[threadcount];
    //printf("Threadcount:%d\n",threadcount);
    if(block[1]=='b')//1byte=0.000001
    {
      s=1;
      //printf("Hello byte\n");
    }
    else if(block[1]=='k')//1kb=0.001
    {
        s=1*1024;
        //printf("Hello 1kb\n");
    }
    else if(block[1]=='m')//1mb=1
    {
        s=(1*1048576);
        //printf("Hello 1mb\n");
    }
    else if(block[2]=='M')//10MB=10
    {
        s=(10*1048576);
        //printf("Hello 10mb\n");
    }
    else if(block[2]=='0')//100MB=100
    {
        s=(100*1048576);
       // printf("Hello 100mb\n");
    }
    //printf("Size of s:%d\n",s);    
    int ini1=250000000/threadcount;
    int r2=(250000000/threadcount);
    int r3=(250000000/threadcount);
    int initcount=0;
    int *arr=(int *)malloc(1000000000);
    srand(time(0));
    int i;
    for(i=0;i<250000000;i++)
    {      
      int b=rand()%100;     
      arr[i]=b;        
    }
    int *destarr=(int *)malloc(1000000000);
    struct disk_struct mm;
    mm.tc=threadcount;
    mm.bs=s;
    mm.acp=ap;  
    mm.work=ini1;  
    mm.arraystart=arr;
    mm.startvalue=initcount;
    mm.endvalue=r3;
    mm.arraydest=destarr;
    switch(ap[1])
   { 
    case 'W': //Use "W" for sequential write (SW)
    printf("Sequential W\n\n");
    trestart=clock();
    for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,diskoperationssqwr,(void *) &mm);
    sleep(1);
    initcount=initcount+ini1;
    mm.startvalue=initcount;
    r3=r3+r2;
    mm.endvalue=r3;
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
    if(s!=1024)
    {
    bytestransfer=(1/total1);
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Mbps:%lf\n",bytestransfer);
    printf("********************\n");
    }
    else
    {
    bytestransfer=((1/total1));
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Latency:%lf\n",bytestransfer);
    printf("********************\n");
    }
    free(arr);
    break;

     case 'R':  //Use "R" for sequential read(SR)
      printf("Sequential R\n\n");
      trestart=clock();
      for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,diskoperationssqre,(void *) &mm);
    sleep(1);
    initcount=initcount+ini1;
    mm.startvalue=initcount;
    r3=r3+r2;
    mm.endvalue=r3;
    if (ac) {
     printf("Could not create thread %d \n",v);
     }
     }
     for (u = 0; u < threadcount; u++) {
     ac = pthread_join(threads[u], NULL);
     if (ac) {
     printf("Could not join thread %d \n", u);
     }
     }
     trestop=clock();
    double tot2=trestop-trestart;
    double total2=(tot2/CLOCKS_PER_SEC);
    if(s!=1024)
    {
    bytestransfer=(1/total2);
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Mbps:%lf\n",bytestransfer);
    printf("********************\n");
    }
    else
    {
    bytestransfer=((1/total2));
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Latency:%lf\n",bytestransfer);
    printf("********************\n");
    }
    free(arr);
     break;
     
     case 'w': //Use "w" for random write (rw)
    printf("Random W\n\n");
    trestart=clock();
    for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,diskoperationsrawr,(void *) &mm);
    sleep(1);
    initcount=initcount+ini1;
    mm.startvalue=initcount;
    r3=r3+r2;
    mm.endvalue=r3;
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
     double tot3=trestop-trestart;
     double total3=(tot3/CLOCKS_PER_SEC);
    if(s!=1024)
    {
    bytestransfer=(1/total3);
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Mbps:%lf\n",bytestransfer);
    printf("********************\n");
    }
    else
    {
    bytestransfer=((1/total3));
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Latency:%lf\n",bytestransfer);
    printf("********************\n");
    }  
    free(arr);
    free(destarr);
     break;

     case 'r':  //Use "r" for random read(rr)
      printf("Random R\n\n");
      trestart=clock();
      for (v = 0; v < threadcount; v++) {
    ac = pthread_create(&threads[v],NULL,diskoperationsrare,(void *) &mm);
    sleep(1);
    initcount=initcount+ini1;
    mm.startvalue=initcount;
    r3=r3+r2;
    mm.endvalue=r3;
    if (ac) {
     printf("Could not create thread %d \n",v);
     }
     }
     for (u = 0; u < threadcount; u++) {
     ac = pthread_join(threads[u], NULL);
     if (ac) {
     printf("Could not join thread %d \n", u);
     }
     }
     trestop=clock();
     double tot4=trestop-trestart;
     double total4=(tot4/CLOCKS_PER_SEC);
     if(s!=1024)
    {
    bytestransfer=(1/total4);
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Mbps:%lf\n",bytestransfer);
    printf("********************\n");
    }
    else
    {
    bytestransfer=((1/total4))/10;
    printf("********************\n");
    printf("Parameters TC BS  MT\n");
    printf("Parameters %d %s %s\n",threadcount,block,ap);
    printf("Latency:%lf\n",bytestransfer);
    printf("********************\n");
    }
    free(arr);
    free(destarr);
     break;
    }
}
