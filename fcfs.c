#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[])
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
        int temp;
        float current_time=0,avg_wt=0,avg_tat=0;

        // initial allocation
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

        if (file == NULL){

            printf("File does not exists \n");
            return 1;
        }
        char id[2];
        float a[5];
        int j;

        while(1){                                               //end of file condition

            int k=fscanf(file, "%s", id);
            if(id[0]=='x'){
                printf("Reached EOF\n");
                break;
            }
            size++;

            if(size!=1){

                at = (float*)realloc(at, sizeof(float)*(size));
                bt = (float*)realloc(bt, sizeof(float)*(size));
                interrupt = (float*)realloc(interrupt, sizeof(float)*(size));
                wt = (float*)realloc(wt, sizeof(float)*(size));
                priority = (float*)realloc(priority, sizeof(float)*(size));
                process = (char **) realloc(process,sizeof(char*)*(size));
                process[size-1] =(char*)calloc(3,sizeof(char));
            }

            for(j=0;j<5;j++)
                fscanf(file,"%f",&a[j]);
                at[size-1]=a[0];
                bt[size-1]=a[1];
                interrupt[size-1]=a[2];
                wt[size-1]=a[3];
                priority[size-1]=a[4];
                process[size-1][0]=id[0];process[size-1][1]=id[1];process[size-1][2]='\0';
        }

        for(i=1;i<size;i++){                               //actual arrival times

            at[i]=at[i]+at[i-1];
        }

        for(i=0;i<size;i++){                                //total burst time

            bt[i]= bt[i] + interrupt[i]+wt[i];
        }
        for (i=0;i<size-1;i++){                             //sort according to arrival time

            for (j=0;j<size-i-1;j++){

                if(at[j]>at[j+1]){

                    temp=process[j+1];
                    process[j+1]=process[j];
                    process[j]=temp;
                    temp=at[j+1];
                    at[j+1]=at[j];
                    at[j]=temp;
                    temp=bt[j+1];
                    bt[j+1]=bt[j];
                    bt[j]=temp;
                }
            }
        }

  float w_time[size],tat[size];

  for (i = 0; i < size; ++i)
  {
    if(at[i]<=current_time)
    {
      w_time[i]=current_time-at[i];
      tat[i]=bt[i]+w_time[i];
      current_time=current_time+bt[i];
    }
    else
    {
      current_time=at[i];
      w_time[i]=current_time-at[i];
      tat[i]=bt[i]+w_time[i];
      current_time=current_time+bt[i];
    }
  }

  printf("Process\tWaiting_Time\tTurn_a_time\n");
  for (i = 0; i <size; i++)
  {
      printf("%s\t %f\t %f\n",process[i],w_time[i],tat[i]);
  }

  for(i=0;i<size;i++)
    {
         avg_wt+=w_time[i];     //Calculating TurnAround Time (TAT)
         avg_tat+=tat[i];
    }

     avg_wt=avg_wt/size;
     avg_tat=avg_tat/size;

     printf("\n\nAverage Waiting Time=%f",avg_wt);
     printf("\nAverage Turnaround Time=%f\n",avg_tat);

  return 0;
}

