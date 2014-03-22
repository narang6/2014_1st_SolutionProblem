#include <stdio.h>
//int inputdata(FILE *Finp, int setdeck[105][55], int mixes)
int inputdata(FILE *Finp, int setdeck[105][55])
{
	int j,k;
	int mixes;
	//섞는 가짓수
	fscanf(Finp,"%d",&mixes);
	for(j=1;j<=mixes;++j)
	{
		for(k=1;k<=52;++k)
		{
			//52개를 읽어서 배열에 넣음
			fscanf(Finp,"%d",&setdeck[j][k]);
			//printf("%d ",setdeck[j][k]);
		}
		//printf("\n");
	}
	fscanf(Finp,"\n");
	return mixes;
}

//int mixing(FILE *Finp, int nowdeck[105],int setdeck[105][55])
void mixing(FILE *Finp, int nowdeck[105],int setdeck[105][55])
{
	int j,k;
	char tmp[100];
	int tmpdeck[55];
	char *isexit=(char *)Finp;
	int mixnum;
	//isexit=fgets(tmp,100,Finp);
	//입력된 번호대로 섞는다.
	for(j=0;isexit!=NULL;++j)
	{
		isexit=fgets(tmp,100,Finp);
		if(tmp[0]=='\n' || isexit==NULL)	break;
		sscanf(tmp,"%d",&mixnum);

		//mixnum대로 섞음
		if(j==0)
		{
			for(k=1;k<=52;++k)
			{
				nowdeck[k] = setdeck[mixnum][k];
			}
		}
		else
		{
			for(k=1;k<=52;++k)
			{
				tmpdeck[k] = nowdeck[setdeck[mixnum][k]];
			}
			for(k=1;k<=52;++k)
			{
				nowdeck[k] = tmpdeck[k];
			}
		}
	}
	//return mixnum;
}

void myprogram()
{
	FILE *Finp, *Fout;
	int i,j,k;

	int cases;
	int mixes;//, mixnum;
	int myshape, mynum;
	//char *isexit;
	//char tmp[10];

	int nowdeck[55]={0,};
	//int tmpdeck[55]={0,};
	int setdeck[105][55]={0,};

	char shapes[4][10]={"Clubs", "Diamonds", "Hearts", "Spades"};
	char numbers[4][10]={"Jack", "Queen", "King", "Ace"};
	char numbers2[13][10]={"2","3","4","5","6","7","8","9","10","Jack", "Queen", "King", "Ace"};

	if((Finp=fopen("p10205.inp","r"))==NULL)
	{
		printf("INPUT ERROR");
		return;
	}
	if((Fout=fopen("p10205.out","w"))==NULL)
	{
		printf("OUTPUT ERROR");
		return;
	}

	//Test case 수
	fscanf(Finp,"%d",&cases);
	for(i=0;i<cases;++i)
	{
		//mixes=inputdata(Finp,setdeck,mixes);
		mixes=inputdata(Finp,setdeck);
		//mixnum = 
		mixing(Finp,nowdeck,setdeck);
		for(j=1;j<=52;++j)
		{
			mynum=nowdeck[j]%13;
			if(!mynum) mynum+=13;
			myshape = (nowdeck[j]-1)/13;
			//printf("%s of %s\n",numbers2[mynum-1],shapes[myshape]);
			fprintf(Fout,"%s of %s\n",numbers2[mynum-1],shapes[myshape]);
		}
		fprintf(Fout,"\n");
		//printf("\n");
	}
	fclose(Finp);
	fclose(Fout);
}

int main()
{
	myprogram();
	return 0;
}


