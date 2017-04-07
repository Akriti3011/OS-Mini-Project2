    #include<stdio.h>
    #include<stdlib.h>
    #include<time.h>
    struct node      //structure
        {
            float at;
            float bt;
            char **pid;
               struct node *link;
        } ;
    struct node *start = NULL;

    void insert(float a, float b, char **pid)                 //insert processes in linked list
    {
        struct node *ptr = (struct node *)malloc(sizeof(struct node));
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        if(start==NULL)
        {
            temp->at=a;
            temp->bt=b;
            temp->pid=pid;
            temp->link=NULL;
            start=temp;
        }
        else
        {
            ptr=start;
            while(1)
            {
                if(ptr->link != NULL)
                    ptr=ptr->link;
                else
                    break;
            }
            temp->at=a;
            temp->bt=b;
            temp->pid=pid;
            temp->link=NULL;
            ptr->link=temp;
        }
    }

    void delete(int n)                                  //delete processes at a given pos from linked list
    {
        struct node *ptr1,*ptr2;
        ptr1=start;
        int i;
        if(n==0)
        {
            start=ptr1->link;
        }
        else
        {
            for(i=0;i<n;i++)
            {
                ptr2=ptr1;
                ptr1=ptr1->link;
            }
            if(ptr1->link!=NULL)
                ptr2->link=ptr1->link;
            else
                ptr2->link =NULL;
        }
    }
    void display()                                        //display current processes in linked list
    {
        struct node *ptr;
        ptr = start;
        printf("PID of remaining processes :-  ");
        if (ptr==NULL)
            printf("NONE");
        else
        {
            while(ptr!=NULL)
            {
                printf("%s->",ptr->pid);
                ptr=ptr->link;
            }
        }
        printf("\n");
    }

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
        for(i=0;i<size;i++){                              //insert processes in linked list
            insert(at[i],bt[i],process[i]);
        }
        srand(time(NULL));                                //generate random no from cpu time

        printf("Process\t\t Waiting time\tTurn around time\n");
        while(size>0){

            struct node *ptr;
            ptr=start;
            float wait=0,tat=0;
            int count=0;

            while(ptr!=NULL){                              //track the arrived processes

                if(ptr->at <=current_time)
                count++;
                ptr=ptr->link;
            }
            //printf("count = %d\n",count);
            if(count>0){

                int rno=(rand()%count);                    //generate random no if process arrived
                //printf("rno=%d\n",rno);
                ptr=start;
                int counter=0;
                while(ptr!=NULL){                          //find required parameters and delete that process
                    if(counter==rno){

                        wait=current_time-ptr->at;
                        tat=ptr->bt+wait;
                        current_time=current_time+ptr->bt;
                        printf("\n|%s\t\t|%f\t|%.4f\n",ptr->pid,wait,tat);
                        printf("|---------------|---------------|-------\n");
                        avg_wt+=wait;
                        avg_tat+=tat;
                        delete(rno);
                        //display();
                    }
                    counter++;
                    ptr=ptr->link;
                }

            }

            else{                                            //condition for idle state
                ptr=start;
                current_time=ptr->at;
            }
        }
        avg_wt=avg_wt/size;
        avg_tat=avg_tat/size;

        printf("\n\nAverage Waiting Time=%f",avg_wt);
        printf("\nAverage Turnaround Time=%f\n",avg_tat);

      return 0;
    }

