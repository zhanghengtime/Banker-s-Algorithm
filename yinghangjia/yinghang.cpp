#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include "iostream.h"

int  n,m;
struct info
{
	int claim[50]; //最大需求
	int allocation[50]; //资源分配矩阵
	int need[50]; //需求矩阵
}pro[50];
int available[50]; //可分配空闲资源矩阵
int request[50];

void init()  //初始化
{   
	int i,j;
	printf("请输入资源种类数:");
	scanf("%d",&n);
    for(i=0;i<n;i++)
    {   
		printf("请输入第%d个资源的最大资源数:\n",i);
		scanf("%d",&available[i]);
	}
    printf("请输入进程数:");
	scanf("%d",&m);	
	printf("请输入各进程对各资源的最大需求数:\n");
	for(i=0;i<m;i++)
    {   
		printf("请输入第%d进程对各资源的最大需求数:\n",i);
        for(j=0;j<n;j++)
		{
			scanf("%d",&pro[i].claim[j]);
			pro[i].allocation[j]=0;
			pro[i].need[j]=pro[i].claim[j];
		}
	} 
    printf("\n");
}

int safe() //安全状态检查
{ 
	int work[50];
	for(int j=0; j<n;j++)
		work[j] = available[j];
	bool finish[50];
	for(int i=0; i<m;i++)
		finish[i]=false;
	for(i=0;i<m;i++)
	{
		if(finish[i]==false)
		{
			for(j=0;j<n;j++)
			{
				if(pro[i].need[j]>work[j])
				{	
					break;
				}
				if(j==n-1)
				{
					for(int ji=0;ji<n;ji++)
						work[ji] = work[ji] + pro[i].allocation[ji];
					finish[i] = true;
					printf("%d、 ",i);
					i = -1; 
				}
			}
		}
	}	
	for(i=0; i<m;i++)
	{
		if(finish[i]==false)
			return 0;
	}
	return 1;
}

void allo() //申请资源    
{   
	int flag=0;
	int number;
	printf("请输入要申请资源的进程号:\n");
	scanf("%d",&number);
	if(number>=m)
	{
		printf("错误\n");
		return ;
	}
	printf("请输入要申请的资源数:\n");
	for(int i=0;i<n;i++)
		scanf("%d",&request[i]);
	for(int j=0;j<n;j++)
	{
		if(request[j] + pro[number].allocation[j]>pro[number].claim[j])
		{
			printf("进程%d阻塞!\n",number);
			flag = 1;
			break;
		}
		if(request[j] > available[j])
		{
			printf("进程%d阻塞!\n",number);
			flag = 1;
			break;
		}
		available[j] = available[j] - request[j];
		pro[number].allocation[j] = pro[number].allocation[j] + request[j];
		pro[number].need[j] = pro[number].need[j] - request[j];
	}
	if(flag==0)
	{
		if(!safe())
		{
			for(j=0;j<n;j++)
			{
				available[j] = available[j] + request[j];
				pro[number].allocation[j] = pro[number].allocation[j] - request[j];
				pro[number].need[j] = pro[number].need[j] + request[j];
			}
			printf("进程%d阻塞!\n",number);
		}
		else
		{	
		    int f =0; 
			for(int ff=0; ff<n ;ff++)
			{
				if(pro[number].allocation[ff] == pro[number].claim[ff]&&pro[number].allocation[ff]!=0)
					f++;
			}
			if(f == 3)
			{
				for(ff=0; ff<n; ff++)
					available[ff]=available[ff] + pro[number].allocation[ff];
			}
			printf("满足申请!\n");
		}
	}
}

void print(void)
{	
	int i = 0;
	cout<<"可利用资源: ";
	while(i<n)
	{
		cout<<available[i]<<"   ";
		i++;
	}
	cout<<endl;
}

int main()
{ 
  int i;
  init();
  do
  {
	  printf("选择1--用银行家算法;选择0--退出");
      scanf("%d",&i);
      if(i==1)
	  {
	    allo();
		print();
	  }
  }while(i==1);
  return 1;
}