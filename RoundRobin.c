    #include <stdio.h>
    #include <malloc.h>
    #include <ctype.h>

    struct node
    {
      int pid;
      struct node *next;
    }*front,*rear,*newnode,*ptr;

    void enqueue(int value)
    {
      newnode=(struct node*)malloc(sizeof(struct node));
      newnode->pid=value;
      if((front==NULL)&&(rear==NULL))
      {
        front=newnode;
        rear=newnode;
        newnode->next=NULL;
      }
      else
      {
        rear->next=newnode;
        newnode->next=NULL;
        rear=newnode;
      }
    }

    int dequeue()
    {
      int a=front->pid;
      if(front==rear)
      {
        front=NULL;
        rear=NULL;
      }
      else
      {
        front=front->next;
      }
      return a;
    }

    int isempty()
    {
      if((front==NULL)&&(rear==NULL))
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
    int check(int a[],int s)
    {
      int i;
      for(i=0;i<s;i++)
      if(a[i]!=2)
      return 1;
      return 0;
    }

    int main(int argc, char *argv[])
    {
      FILE *file = fopen(argv[1], "r");
      int i=0;
      float *at;
      float *bt;
      float *burst;
      float *interrupt;
      float *wt;
      int size=1;

      at = (float*)calloc(size,sizeof(float));
      bt = (float*)calloc(size,sizeof(float));
      burst = (float*)calloc(size,sizeof(float));
      interrupt = (float*)calloc(size,sizeof(float));
      wt = (float*)calloc(size,sizeof(float));

      size=0;
    
      if (file == NULL)
      {
        printf("File does not exists \n");
        return 1;
      }
      char id[2];
      float a[5];
      int j;

      while(1)
      {
        int k=fscanf(file, "%s", id);
      if(id[0]=='x')
      {
        printf("Reached EOF\n");
        break;
      }
      size++;

      if(size!=1)
      { 
        at = (float*)realloc(at, sizeof(float)*(size));
        bt = (float*)realloc(bt, sizeof(float)*(size));
        burst = (float*)realloc(burst, sizeof(float)*(size));
        interrupt = (float*)realloc(interrupt, sizeof(float)*(size));
        wt = (float*)realloc(wt, sizeof(float)*(size));
      }
      for(j=0;j<5;j++)
      fscanf(file,"%f",&a[j]);

      at[size-1]=a[0];
      bt[size-1]=a[1];
      burst[size-1]=a[1];
      interrupt[size-1]=a[2];
      wt[size-1]=a[3];
      }

      float w_time[size],tat[size],st[size],et[size],tq,swap,ext=0,exec[size];
      int checked[size],inqueue[size];
      int k,pid,twt=0;
      printf("Enter time quantum\n");
      scanf("%f",&tq);
      for(i=0;i<size;i++)
      {
        checked[i]=0;
        inqueue[i]=0;
      }
      for(i=1;i<size;i++)
      {
        at[i]=at[i]+at[i-1];
      }
      for(i=0;i<size;i++)
      {
        bt[i]+=interrupt[i]+wt[i];
        burst[i]+=interrupt[i]+wt[i];
      }

    printf("Arrival time\tBurst time\n");
    for(i=0;i<size;i++)
    {
      printf("%.2f\t\t%.2f",at[i],bt[i]);
      printf("\n");
    }

    i=at[0];pid=0;
    enqueue(pid);
    inqueue[pid]=1;
    int totalsize=size;
    while(totalsize!=0)
    {
	if(isempty()==1)
	{
		pid=size-totalsize;
		enqueue(pid);
		inqueue[pid]=1;
		i=at[pid];
		if(checked[pid]==0)
		{
			st[pid]=i;
			checked[pid]=1;
		}
	}
      pid=dequeue();
      inqueue[pid]=0;
      if(checked[pid]==0)
      {
        st[pid]=i;
        checked[pid]=1;
      }
      if(bt[pid]<=tq && checked[pid]!=2)
      {
        i=i+bt[pid];
        bt[pid]=0;
        checked[pid]=2;
	totalsize--;
        et[pid]=i;
      }
      else if(checked[pid]!=2)
      {
        i=i+tq;
        bt[pid]=bt[pid]-tq;
      }
      printf("Process %d -> Remaining time is %.2f\t\t flag=%d\n",pid+1,bt[pid],checked[pid]);
      for(j=0;at[j]<=i && j<size;j++)
      {
        if(j!=pid && inqueue[j]==0 && checked[j]!=2)
        {
    	     enqueue(j);
    	     printf("Process arrived in queue is %d\n",j+1);
    	     inqueue[j]=1;
        }
      }
      if(checked[pid]!=2)
      {
        enqueue(pid);
        inqueue[pid]=1;
      }
    }
    printf("Process ID\tStart time\t End time\t Waiting time\t Execution time\n");
    for(i=0;i<size;i++)
    {
      printf("%d\t |\t",i+1);
      printf("% .2f\t |\t",st[i]);									
      printf("% .2f\t |\t",et[i]);
      w_time[i]=et[i]-burst[i]-at[i];
      printf("% .2f\t |\t",w_time[i]);
      exec[i]=et[i]-st[i];
      printf("%.2f\t|",exec[i]);
      printf("\n");
      ext=(et[i]-st[i])+ext;
      twt=w_time[i]+twt;
    }
    printf("Total execution time % .2f\n",ext);
    printf("avg wait time =% .2f ",twt/(float)size);
    }
