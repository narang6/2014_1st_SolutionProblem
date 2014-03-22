#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int num;
	int flag;
	struct node *lson;
	struct node *rson;
} mnode;
//1<=node<1048576(2^20)
//1048576개의 노드를 위해서는 링크드 리스트(트리)를 구현하자 (배열 실행안댐)

mnode *createnode(mnode *parents, int pos);
mnode* maketree(mnode* parent,int max);
int msquare(int a, int b);
int movingball(mnode *root);


int main()
{
	int cases;				//test case수
	int depth, balls;		//깊이, 공 수
	int maxnum, res;		//트리의 최댓값, 결과(공이 맨 마지막 도달하는 애)

	mnode *root=NULL;		//트리 루트
	int i,j;

	FILE *Finp, *Fout;
	//파일입출력
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


	//첫줄에는 testcase의 수
	fscanf(Finp,"%d",&cases);
	
	for(i=0;i<cases;++i)
	{
		//2번째부터 d:Depth, i:공수
		fscanf(Finp,"%d %d",&depth, &balls);
		maxnum = msquare(2,depth)-1;
		root=NULL;
		root=maketree(root,maxnum);

		for(j=0;j<balls;++j)		//balls 개의 공을 던짐
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
//false면 왼쪽 true면 오른쪽

//새 노드를 만듬
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
	return tmp;		//새로생긴놈 반환
}

mnode* maketree(mnode* parent,int max)
{
	mnode* now_node = parent;
	//루트 노드를 만든다
	if(parent==NULL)	
		now_node=createnode(now_node,0);
	if(now_node->num>=(max+1)/2)
	{
		return now_node;
	}
	//if(now_node->num<=(max+1)/2)		//자식들의 num도 max를 초과하면 안됨
	else
	{
		createnode(now_node,-1);		//왼쪽자식
		createnode(now_node,1);			//오른쪽자식
		maketree(now_node->lson,max);//왼 서브 트리
		maketree(now_node->rson,max);//오른 서브 트리
		return now_node;
	}
}

//a의 b제곱을 구하는함수
int msquare(int a, int b)			
{
	int res=1, i;

	for(i=0;i<b;++i)
	{
		res*=a;
	}
	return res;
}

//공이 한번 지나간다.
int movingball(mnode *root)	
{
	mnode *node=root;
	if(node)
	while(node->lson!=NULL)
	{
		node->flag*=-1;

		//이미-1곱했으니 반대방향.
		//1이면 왼쪽, -1이면 오른쪽으로 감
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