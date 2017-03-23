#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{

  FILE *file = fopen(argv[1], "r");
  int i=0;
  char **process;
  float *at;
  float *bt;
  float *interrupt;
  float *wt;
  float *priority;
  int size=1;

  // initial alloc
  process = (char**)calloc(size,sizeof(char*));
  for(i=0;i<size;i++){
    process[i]=(char*)calloc(3,sizeof(char));
  }
  at = (float*)calloc(size,sizeof(float));
  bt = (float*)calloc(size,sizeof(float));
  interrupt = (float*)calloc(size,sizeof(float));
  wt = (float*)calloc(size,sizeof(float));
  priority = (float*)calloc(size,sizeof(float));
  size=0;
  if (file == NULL)
    {
        printf("File does not exists \n");
        return 1;
    }
  char id[2];
  float a[5];
  int j;

  while(1){
     int k=fscanf(file, "%s", id);
     if(id[0]=='x'){
      printf("Reached EOF\n");
      break;
     }
     size++;
    // printf("%d\n",size);

     if(size!=1)
      { at = (float*)realloc(at, sizeof(float)*(size));
      bt = (float*)realloc(bt, sizeof(float)*(size));
      interrupt = (float*)realloc(interrupt, sizeof(float)*(size));
      wt = (float*)realloc(wt, sizeof(float)*(size));
      priority = (float*)realloc(priority, sizeof(float)*(size));
      process = (char **) realloc(process,sizeof(char*)*(size));
      process[size-1] =(char*)calloc(3,sizeof(char));
    }
     for(j=0;j<5;j++)
      fscanf(file,"%f",&a[j]);
      //printf("%f\n",a[j] );
      *(at+size-1)=a[0];
      *(bt+size-1)=a[1];
      *(interrupt+size-1)=a[2];
      *(wt+size-1)=a[3];
      *(priority+size-1)=a[4];
      process[size-1][0]=id[0];process[size-1][1]=id[1];process[size-1][2]='\0';
  }

  float w_time[size],tat[size];

  w_time[0]=0;

  for (i = 0; i < size; ++i)
  {
    bt[i]=bt[i]+interrupt[i]+wt[i];

  }
  for(i=1;i<size;i++)
  {
     float sum=0;
    for(j=0;j<i;j++)
    {
       sum=sum+bt[j];
    }
     w_time[i]=sum-at[i];
  }
  for (i = 0; i < size; ++i)
     {
       tat[i]=w_time[i]+bt[i];
     }


  printf("Process\tWaiting_Time\tTurn_a_time\n");
  for (int i = 0; i <size; i++)
  {
      printf("%s\t %f\t %f\n",process[i],w_time[i],tat[i]);
  }



  return 0;
}
