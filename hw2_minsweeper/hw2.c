#include<stdio.h>

/*
문제해결기법2. 지뢰찾기
0934788 김나랑
14-03-11
*/

//이번엔 좀 잘 되길

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
	char isexit=1;		//EOF감지
	int x, y;			//가로, 세로 길이
	int i, j;			//for문 반복
	char inp;			//지뢰감지

	int total_board=0;

	int myboard[102][102];

	if((Finp=fopen("hw2.inp","r"))==NULL)
	{
		printf("입력에러");
		return;
	}

	if((Fout=fopen("hw2.out","w"))==NULL)
	{
		printf("출력에러");
		return;
	}

	while(isexit!=EOF)
	{
		isexit=fscanf(Finp,"%d %d",&y,&x);		//가로 세로 입력
		printf("[%d %d]\n",x,y);
		isexit=fscanf(Finp, "%c", &inp);		//엔터
		if(isexit==EOF)	break;

		initary(myboard,x,y);				//배열초기화
		total_board++;

		//각 줄 입력
		for(j=0;j<y;++j)
		{
			for(i=0;i<x;++i)
			{
				//fscanf(Finp, "%c", &inp);
				do{
					fscanf(Finp, "%c", &inp);
				}while(inp==10);
				printf("%c",inp);
				//지뢰면 @_@ 따로만든 배열을 채운다

				if(inp == '*')
				{
					fillboard(myboard,j,i,x,y);
				}
			}
			printf("\n");
			fscanf(Finp, "%c", &inp);		//엔터
		}
		if(x>0 && y>0)
		{
			printf("Field #%d:\n",total_board);
			fprintf(Fout,"Field #%d:\n",total_board);
			printboard(Fout,myboard,x,y);//출력
			printf("\n");
			fprintf(Fout,"\n");
		}
	}
	fclose(Finp);
	fclose(Fout);
}

void initary( int ary[102][102], int width, int height)		//w * h 배열을 초기화한다.
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
	//x,y를 중심으로 한바퀴를 채운다

	ary[y][x]=-1;
	for(j=y-1; j<=y+1; ++j)
	{
		if(j>=0 && j<height)
		for(i=x-1; i<=x+1; ++i)
		{
			if(x>=0 && x<width && ary[j][i]>=0)		//지뢰 없는 칸만 채운다.
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
