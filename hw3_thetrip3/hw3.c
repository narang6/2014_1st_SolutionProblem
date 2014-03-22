/*
^_^
0934788 �質��
140314
�����ذ��� 3
10137 the trip
4��°�� ���� «^_^
^_^ ^_^*/

#include <stdio.h>
//#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//���� �л����� Ŭ���� �����
//�ų� ������ ���� �ݱ� ������
//�׵��� �������� �ε�Ƴ������� ���н� ������ �ʶ��Ǿ� ��ȣ�� ��Ʋ��Ÿ
//�ú��� �׵��� �ε�ȣ��?�� ��
//�׷��� �����ߴ� ������ ����� �Ȱ��� ���ڰ�
//��ġ�� �Ƚ��� ��� ����� �߻��Ҷ�����
//�׷��� ������ Ư�� ���� ������ ����, ȣ�� �ؽ� ����� ���
//��������� ���� �л��� ����� ����ǰ� ���� ��ȯ�� �׷����ν� 1��Ʈ�̳��� ������??
//���ſ��� �� ���� ��ȯ�ߴ� ��������? �׸��� �ð��Һ�Ǵ�
//�� ���� ����Ѵ� ��븮��Ʈ�κ���, �ּұݾ� ��ȯ������ �����ϱ����ؼ�(1��Ʈ�̳���) ��� �л����� �ڽ�Ʈ

//�Է�
//ǥ���Է��� �����Ұ��̴� ������ ��� ����
//���� ���� ������ �����Ǿ��ִ� �� ���ο� �����Ѵ� ��� ��Ƽ�� n, 
//�л��� ���డ��, n������ �ٿ��� ���� �����Ѵ� �޷��� ��Ʈ�� ��
//�л����κ��ͤ� �ҿ��
//1000�� �̻��� �л��� �ƴ�
//10000�� �̻� ���� �ֵ� ����
//0���� �����ϴ� ���� ������ ����

//���
//������ ���࿡��, ����� �������Ѵ� �� �� ��
//�޷� �� ��Ʈ
// �װ��� �ٲ����Ѵ� �����ϰ� �л����� ���

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
double totalc;		//��
double average;		//���
double restc;		//������
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
	file_init();		//�ʱ�ȭ	
	input_data();		//�Է�


	fclose(Finp);
	fclose(Fout);
	return 0;
}

void file_init()
{
	if((Finp=fopen("hw3.inp","r"))==NULL)
	{
		printf("�Է� ����");
		return;
	}
	if((Fout=fopen("hw3.out","w"))==NULL)
	{
		printf("��� ����");
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
		my_calc();//�ҽ�

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

	mysort();//�������� ����

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

void mysort()			//ppl��ŭ �������� ����
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

//�ѹ��� �ǰ� ���ּ���̤�
void mitoa(int n, char* ptr, int binary)  // (10���� ������ - > ���ϴ� �������� ���ڿ��� ��ȯ) 
{
 int i=0, j=0, len;
 char temp[255];        // �ٲ��� �迭 ����
 while( n != 0 )        // n �� 0�� �ɶ����� ����
 {
  temp[i] = (n % binary)+'0';    // temp�� ���� �ڸ����� ������� ����.
  n = n / binary;       // n�� ���� �Լ� �ٿ���.
  i++;
 }
 len = i;         // ���⼭ len�� '\0'�� �� �ڸ�.
 for(i=len-1; i>=0; i--)      // len-1���� �ݴ��������
  ptr[j++] = temp[i];      // ptr�迭�� ����.
 
 ptr[len]='\0';        // �� ���ڸ� ���峡�� �����ֱ� ���� �־���.
}
