#include <stdio.h>
/*
5. Jolly Jumpers
10038
0934788 김나랑
*/

int main()
{
	
	int input[3002]={0,};
	int checks[3002]={0,};
	int i,j,tmp,num,k;
	int ch=1, ch2=1;
	int max=0;
	FILE *Finp, *Fout;

	if((Finp=fopen("p10038.inp","r"))==NULL)	return 1;
	if((Fout=fopen("p10038.out","w"))==NULL)	return 1;

	//입력
	
	//while((ch2=fscanf(Finp,"%d",&num))!=EOF)
	for(k=0;(ch2=fscanf(Finp,"%d",&num))!=EOF;++k)
	{
		//printf("%d. ",k);
		//fprintf(Fout,"%d. ",k);
		//ch2=fscanf(Finp,"%d%c",&num,&ch);
		if(num>1)
		{
			for(i=0;i<num;++i)
			{
				checks[i]=0;			//check 배열 초기화
				ch2=fscanf(Finp,"%d%c",&input[i],&ch);
				if(ch2==EOF)	break;
			}
			if(ch2==EOF && i==0)	break;
			//배열에 입력 하고 나면 입력한 수의 차를 기록
			for(j=1;j<i;++j)
			{
				if(input[j]-input[j-1]>=1)
					tmp=input[j]-input[j-1];
				else
					tmp=(input[j]-input[j-1])*(-1);
				if(tmp>=1)
					checks[tmp-1]=1;
				/*else
					printf("*%d\n",tmp);*/

				//if(tmp>max)	max=tmp;
			}
			//차를 기록한 배열을 검사하여 모두 1인지 확인
			for(j=0;j<num-1;++j)
			{
				if(checks[j]!=1)
				{
					printf("Not jolly\n");
					fprintf(Fout,"Not Jolly\n");
					break;
				}
			}
			if(j==num-1)	
			{
				printf("Jolly\n");
				fprintf(Fout,"Jolly\n");
			}
			ch=1;
		}
		else if(num==1)
		{
			printf("Not jolly\n");
			fprintf(Fout,"Not Jolly\n");
		}
		else
		{
			printf("Not jolly\n");
			fprintf(Fout,"Not Jolly\n");
		}
	}

	fclose(Finp);
	fclose(Fout);
	return 0;
}