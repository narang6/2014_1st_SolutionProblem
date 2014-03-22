/*
^_^
0934788 김나랑
140314
문제해결기법 3
10137 the trip
4번째로 새로 짬^_^
^_^ ^_^*/

#include <stdio.h>
//#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//많은 학생들이 클럽의 멤버다
//매년 여행을 간다 왹구 지역에
//그들의 목적지는 인디아나폴리스 포닉스 나쉬빌 필라델피아 산호세 아틀란타
//올봄에 그들은 인드호븐?에 감
//그룹은 동의했다 사전에 비용을 똑같이 내자고
//그치만 안쉽다 모든 비용을 발생할때마다
//그래서 개인이 특정 띵을 지불함 음식, 호텔 텍시 비행기 등등
//여행끄나고 각각 학생들 비용은 집계되고 돈이 교환됨 그럼으로써 1센트이내로 같아짐??
//과거에는 이 돈은 교환했다 지긋지긋? 그리고 시간소비되는
//니 일은 계산한다 비용리스트로부터, 최소금액 교환대어야할 같게하기위해서(1센트이내로) 모든 학생들의 코스트

//입력
//표준입력은 포함할것이다 정보를 몇몇 팁들
//각각 팁의 정보는 구성되어있다 한 라인에 포함한다 양수 인티저 n, 
//학생수 여행가는, n다음의 줄에는 각각 포함한다 달러와 센트의 양
//학생으로부터ㅓ 소요된
//1000명 이상의 학생이 아님
//10000불 이상 쓰는 애도 없다
//0으로 시작하는 줄이 마지막 여행

//출력
//각각의 여행에서, 출력은 ㅅㅣ작한다 총 양 돈
//달러 랑 센트
// 그것은 바뀌어야한다 동등하게 학생들의 비용

FILE *Finp, *Fout;

void file_init();
void input_data();
void my_calc();
void mysort();
double ddabs(double a);
double roundm(double x, int digits)  ;
void mitoa(int n, char* ptr, int binary);

int ppl_num;
double charge[1002];
double totalc;		//총
double average;		//평균
double restc;		//나머지
double result_me;

double td;
double ti;

/*
10
323.46
318.13
300.94
188.69
188.63
175.38
145.24
143.65
97.60
4.72
0

average 188.64
REST = 0.04
exchange
323.46-188.64-0.01 = 134.81
318.13-188.64-0.01 = 129.48
300.94-188.64-0.01 = 112.29
188.69-188.64-0.01 = 0.04
188.64-188.63 = 0.01
188.64-175.38 = 13.26
188.64-145.24 = 43.4
188.64-143.65 = 44.99
188.64-97.60 = 91.04
188.64-4.72 = 183.92
0

TOTAL = 753.24/2 = 376.62
*/


int main()
{
	//generateinput();
	file_init();		//초기화	
	input_data();		//입력


	fclose(Finp);
	fclose(Fout);
	return 0;
}

void file_init()
{
	if((Finp=fopen("hw3.inp","r"))==NULL)
	{
		printf("입력 에러");
		return;
	}
	if((Fout=fopen("hw3.out","w"))==NULL)
	{
		printf("출력 에러");
		return;
	}
}

void input_data()
{
	int i;
	double res2;
	while(fscanf(Finp,"%d",&ppl_num)!=EOF)
	{
		totalc=0;
		if(ppl_num==0) break;
		for(i=0;i<ppl_num;++i)
		{
			fscanf(Finp,"%lf",&charge[i]);
			charge[i] = roundm(charge[i],2);
			//charge[i]+=0.005;
			//total+=(double)(int)(charge[i]*100)/100;
			totalc+= (double)(int)(charge[i]*100+0.5)/100;
			totalc = roundm(totalc,2);
			//total+=charge[i];
			//printf("%d + %lf\n",i,charge[i]);
		}
		ti=0; td=0;
		my_calc();//소스

		//hiscode4();
	}
}

void my_calc()
{
	int i, restrest=0;
	double exchange=0.00, tmp=0.00;
	average = ((double)(int)((totalc/ppl_num)*100))/100;
	average = roundm(average,2);
	restc= (totalc-(average*ppl_num))*100;
	restc = roundm(restc,2);

	printf("total : %lf, average %lf, rest : %lf ppl : %d\n",totalc,average,restc,ppl_num);
	fprintf(Fout,"total : %lf, average %lf, rest : %lf ppl : %d\n",totalc,average,restc,ppl_num);

	mysort();//내림차순 정렬

	for(i=0;i<ppl_num;++i)
	{
		//if(ddabs(charge[i]-188.69)<0.1)
		//	printf(",");
		if((restc-i)>0.5)
		{
			tmp=ddabs(charge[i]-(average+0.01));
			printf("%d tmp : %lf %lf(%lf)\n",i,tmp,charge[i],exchange+tmp);
			fprintf(Fout,"%d tmp : %lf %lf(%lf)\n",i,tmp,charge[i],exchange+tmp);
			//restc-=0.01;
		}
		else
		{
			tmp=ddabs(charge[i]-average);
			printf("%d tmp : %lf\n",i,tmp);
			fprintf(Fout,"%d tmp : %lf\n",i,tmp);
		}
		tmp = roundm(tmp,2);
		exchange+=tmp;
		//	printf("tmp : %lf\n",tmp);
	}
	//printf("total : %.2lf\n",exchange);
	exchange = roundm(exchange,2);
	result_me = (exchange+0.005)/2;
	printf("$%lf $%.2lf\n",(exchange+0.005),result_me);
	fprintf(Fout,"$%.2lf\n",result_me);
}

void mysort()			//ppl만큼 내림차순 정렬
{
	int i,j;
	double tmp;
	for(i=0;i<ppl_num;++i)
	{
		for(j=i+1;j<ppl_num;++j)
		{
			if(charge[i]<charge[j])
			{
				tmp=charge[i];
				charge[i] = charge[j];
				charge[j]=tmp;
			}
		}
	}
}

double ddabs(double a)
{
	if(a<0)
		return -a;
	else return a;
}

double roundm(double x, int digits)  
{
	char format[5 + 1] = "%.";
	char temp[2 + 1];
	char result[500 + 1];

	mitoa(digits, temp, 10); 
	strcat(format, temp); 
	strcat(format, "f"); 

	sprintf(result, format, x); 
	return atof(result); 
}

//한번만 되게 해주세요ㅜㅠ
void mitoa(int n, char* ptr, int binary)  // (10진수 정수형 - > 원하는 진수형의 문자열로 전환) 
{
 int i=0, j=0, len;
 char temp[255];        // 바꿔줄 배열 선언
 while( n != 0 )        // n 이 0이 될때까지 루프
 {
  temp[i] = (n % binary)+'0';    // temp에 일의 자리부터 순서대로 저장.
  n = n / binary;       // n의 값을 게속 줄여줌.
  i++;
 }
 len = i;         // 여기서 len은 '\0'이 들어갈 자리.
 for(i=len-1; i>=0; i--)      // len-1부터 반대방향으로
  ptr[j++] = temp[i];      // ptr배열에 저장.
 
 ptr[len]='\0';        // 널 문자를 문장끝을 보여주기 위해 넣어줌.
}
