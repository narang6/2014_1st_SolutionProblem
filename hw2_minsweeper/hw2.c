#include<stdio.h>

/*
�����ذ���2. ����ã��
0934788 �質��
14-03-11
*/

//�̹��� �� �� �Ǳ�

void myprogram();
void initary( int ary[102][102], int width, int height);
void fillboard(int ary[102][102], int y, int x, int width, int height);
void printboard(FILE *Fout, int ary[102][102], int width, int height);

int main()
{
	myprogram();
	return 0;
}

void myprogram()
{
	FILE *Finp, *Fout;
	char isexit=1;		//EOF����
	int x, y;			//����, ���� ����
	int i, j;			//for�� �ݺ�
	char inp;			//���ڰ���

	int total_board=0;

	int myboard[102][102];

	if((Finp=fopen("hw2.inp","r"))==NULL)
	{
		printf("�Է¿���");
		return;
	}

	if((Fout=fopen("hw2.out","w"))==NULL)
	{
		printf("��¿���");
		return;
	}

	while(isexit!=EOF)
	{
		isexit=fscanf(Finp,"%d %d",&y,&x);		//���� ���� �Է�
		printf("[%d %d]\n",x,y);
		isexit=fscanf(Finp, "%c", &inp);		//����
		if(isexit==EOF)	break;

		initary(myboard,x,y);				//�迭�ʱ�ȭ
		total_board++;

		//�� �� �Է�
		for(j=0;j<y;++j)
		{
			for(i=0;i<x;++i)
			{
				//fscanf(Finp, "%c", &inp);
				do{
					fscanf(Finp, "%c", &inp);
				}while(inp==10);
				printf("%c",inp);
				//���ڸ� @_@ ���θ��� �迭�� ä���

				if(inp == '*')
				{
					fillboard(myboard,j,i,x,y);
				}
			}
			printf("\n");
			fscanf(Finp, "%c", &inp);		//����
		}
		if(x>0 && y>0)
		{
			printf("Field #%d:\n",total_board);
			fprintf(Fout,"Field #%d:\n",total_board);
			printboard(Fout,myboard,x,y);//���
			printf("\n");
			fprintf(Fout,"\n");
		}
	}
	fclose(Finp);
	fclose(Fout);
}

void initary( int ary[102][102], int width, int height)		//w * h �迭�� �ʱ�ȭ�Ѵ�.
{
	int i, j;

	for(i=0;i<height;++i)
	{
		for(j=0;j<width;++j)
		{
			ary[i][j]=0;
		}
	}
}

void fillboard(int ary[102][102], int y, int x, int width, int height)
{
	int i,  j;
	//x,y�� �߽����� �ѹ����� ä���

	ary[y][x]=-1;
	for(j=y-1; j<=y+1; ++j)
	{
		if(j>=0 && j<height)
		for(i=x-1; i<=x+1; ++i)
		{
			if(x>=0 && x<width && ary[j][i]>=0)		//���� ���� ĭ�� ä���.
			{
				ary[j][i]++;
			}
		}
	}
}

void printboard(FILE *Fout, int ary[102][102], int width, int height)
{
	int i, j;

	for(j=0;j<height;++j)
	{
		for(i=0;i<width;++i)
		{
			if(ary[j][i]==-1)
			{
				printf("*");
				fprintf(Fout,"*");
			}
			else
			{
				printf("%d",ary[j][i]);
				fprintf(Fout,"%d",ary[j][i]);
			}
		}
		printf("\n");
		fprintf(Fout,"\n");
	}

	printf("\n");
}
