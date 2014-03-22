#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int num;
	int flag;
	struct node *lson;
	struct node *rson;
} mnode;
//1<=node<1048576(2^20)
//1048576���� ��带 ���ؼ��� ��ũ�� ����Ʈ(Ʈ��)�� �������� (�迭 ����ȴ�)

mnode *createnode(mnode *parents, int pos);
mnode* maketree(mnode* parent,int max);
int msquare(int a, int b);
int movingball(mnode *root);


int main()
{
	int cases;				//test case��
	int depth, balls;		//����, �� ��
	int maxnum, res;		//Ʈ���� �ִ�, ���(���� �� ������ �����ϴ� ��)

	mnode *root=NULL;		//Ʈ�� ��Ʈ
	int i,j;

	FILE *Finp, *Fout;
	//���������
	if((Finp=fopen("p679.inp","r"))==NULL)
	{
		printf("INPUT ERROR");
		return 0;
	}
	if((Fout=fopen("p679.out","w"))==NULL)
	{
		printf("OUTPUT ERROR");
		return 0;
	}


	//ù�ٿ��� testcase�� ��
	fscanf(Finp,"%d",&cases);
	
	for(i=0;i<cases;++i)
	{
		//2��°���� d:Depth, i:����
		fscanf(Finp,"%d %d",&depth, &balls);
		maxnum = msquare(2,depth)-1;
		root=NULL;
		root=maketree(root,maxnum);

		for(j=0;j<balls;++j)		//balls ���� ���� ����
		{
			res = movingball(root);
		}
		printf("%d\n",res);
		fprintf(Fout,"%d\n",res);
	}
	//-1

	fclose(Finp);
	fclose(Fout);
	return 0;
}
//Depth<=20
//Balls <=524288
//false�� ���� true�� ������

//�� ��带 ����
mnode *createnode(mnode *parents, int pos)			
{
	mnode *tmp = (mnode *)malloc(sizeof(mnode));
	tmp->lson=NULL;
	tmp->rson=NULL;
	tmp->flag=-1;
	
	if(pos==0 || parents->flag!=-1)		//root
	{
		parents=tmp;
		tmp->num=1;
	}
	else if(pos==-1)		//lson
	{
		parents->lson=tmp;
		tmp->num = parents->num*2;
	}
	else if(pos==1)			//rson
	{
		parents->rson=tmp;
		tmp->num = parents->num*2+1;
	}
	return tmp;		//���λ���� ��ȯ
}

mnode* maketree(mnode* parent,int max)
{
	mnode* now_node = parent;
	//��Ʈ ��带 �����
	if(parent==NULL)	
		now_node=createnode(now_node,0);
	if(now_node->num>=(max+1)/2)
	{
		return now_node;
	}
	//if(now_node->num<=(max+1)/2)		//�ڽĵ��� num�� max�� �ʰ��ϸ� �ȵ�
	else
	{
		createnode(now_node,-1);		//�����ڽ�
		createnode(now_node,1);			//�������ڽ�
		maketree(now_node->lson,max);//�� ���� Ʈ��
		maketree(now_node->rson,max);//���� ���� Ʈ��
		return now_node;
	}
}

//a�� b������ ���ϴ��Լ�
int msquare(int a, int b)			
{
	int res=1, i;

	for(i=0;i<b;++i)
	{
		res*=a;
	}
	return res;
}

//���� �ѹ� ��������.
int movingball(mnode *root)	
{
	mnode *node=root;
	if(node)
	while(node->lson!=NULL)
	{
		node->flag*=-1;

		//�̹�-1�������� �ݴ����.
		//1�̸� ����, -1�̸� ���������� ��
		if(node->flag==1)
		{			
			node=node->lson;
		}
		else if(node->flag==-1)
		{
			node=node->rson;
		}
	}
	if(node->num<=0)	printf("ERROR : NODE IS NOT NATURAL NUM!\n");
	return node->num;
}