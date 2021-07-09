/***************************************************************
	File name: spj.cpp
	Author: huhao
	Create time: Sat 15 Jun 2019 10:53:29 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<fstream>
using namespace std;
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
ifstream fout;
ofstream fscore,freport;
int l,cnt;
int main(int argc,char **argv)
{
    fout.open(argv[2]);
    fscore.open(argv[5]);
    freport.open(argv[6]);
    int score=atoi(argv[4]);
	int check;
	fout>>check;
	if(check!=19260817)
	{
		fscore<<0<<endl;
		freport<<"Dangerous output"<<endl;
		return 0;
	}
	fout>>l>>cnt;
	if(l<0)
	{
		fscore<<0<<endl;
		freport<<"Wrong Answer,id: "<<l<<endl;
	}
	else
	{
		double k;
		if(cnt<=l)
			k=1;
		else
			k=(1-sqrt(1-((double)l/(double)cnt)*((double)l/(double)cnt)))/1.5;
		fscore<<int(k*score)<<endl;
		freport<<"l="<<l<<",cnt="<<cnt<<endl;
	}
	fout.close();
	fscore.close();
	freport.close();
	return 0;
}
