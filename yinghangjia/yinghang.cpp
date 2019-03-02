#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include "iostream.h"

int  n,m;
struct info
{
	int claim[50]; //�������
	int allocation[50]; //��Դ�������
	int need[50]; //�������
}pro[50];
int available[50]; //�ɷ��������Դ����
int request[50];

void init()  //��ʼ��
{   
	int i,j;
	printf("��������Դ������:");
	scanf("%d",&n);
    for(i=0;i<n;i++)
    {   
		printf("�������%d����Դ�������Դ��:\n",i);
		scanf("%d",&available[i]);
	}
    printf("�����������:");
	scanf("%d",&m);	
	printf("����������̶Ը���Դ�����������:\n");
	for(i=0;i<m;i++)
    {   
		printf("�������%d���̶Ը���Դ�����������:\n",i);
        for(j=0;j<n;j++)
		{
			scanf("%d",&pro[i].claim[j]);
			pro[i].allocation[j]=0;
			pro[i].need[j]=pro[i].claim[j];
		}
	} 
    printf("\n");
}

int safe() //��ȫ״̬���
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
					printf("%d�� ",i);
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

void allo() //������Դ    
{   
	int flag=0;
	int number;
	printf("������Ҫ������Դ�Ľ��̺�:\n");
	scanf("%d",&number);
	if(number>=m)
	{
		printf("����\n");
		return ;
	}
	printf("������Ҫ�������Դ��:\n");
	for(int i=0;i<n;i++)
		scanf("%d",&request[i]);
	for(int j=0;j<n;j++)
	{
		if(request[j] + pro[number].allocation[j]>pro[number].claim[j])
		{
			printf("����%d����!\n",number);
			flag = 1;
			break;
		}
		if(request[j] > available[j])
		{
			printf("����%d����!\n",number);
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
			printf("����%d����!\n",number);
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
			printf("��������!\n");
		}
	}
}

void print(void)
{	
	int i = 0;
	cout<<"��������Դ: ";
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
	  printf("ѡ��1--�����м��㷨;ѡ��0--�˳�");
      scanf("%d",&i);
      if(i==1)
	  {
	    allo();
		print();
	  }
  }while(i==1);
  return 1;
}