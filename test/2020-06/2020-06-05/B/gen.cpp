/***************************************************************
	File name: gen.cpp
	Author: huhao
	Create time: Tue 26 Nov 2019 01:35:02 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
#include<assert.h>
#include<random>
mt19937 _rand;
namespace Srand
{
	int Srand()
	{
		FILE *f=fopen("/dev/urandom","r");
		unsigned long long sed=0;
		fr(i,1,100)
		{
			char c;
			int k=fscanf(f,"%c",&c);
			assert(k==1);
			sed=sed*sed+sed+c;
		}
		_rand=mt19937(sed);
		return 0;
	}
	int init=Srand();
}
int randint(int l,int r){ return int(_rand()>>1)%(r-l+1)+l; }
char *randstr(int n,int l,int r)
{
	char *c=new char[n+1];
	fr(i,0,n-1) c[i]=randint(l,r);
	return c;
}
char *randstr(int n,char *s,int m)
{
	char *c=new char[n+1];
	fr(i,0,n-1) c[i]=s[randint(0,m-1)];
	return c;
}
#define i64 long long
int Rand(int l,int r){ return randint(l,r); }
i64 Randll(){ return ((i64)_rand()*(1ll<<31))|((i64)_rand()); }
i64 Randll(i64 l,i64 r){ return Randll()%(r-l+1)+l; }
const int N=200010;
char p[N],x[N],S[N],s[N];
int main()
{
    freopen("B.in","w", stdout);
	int n=(200000/26)*26,a=Rand(1,n),b=Rand(1,n);
	fr(i,0,n-1) s[i]=i%26+'a';
	//                  abcdefghijklmnopqrstuvwxyz
	fr(i,'a','z') p[i]="crgiaxkosmltfpveyjhquzwbnd"[i-'a'];
	fr(i,'a','z') x[i]=i;
	fr(i,1,b) fr(j,'a','z') x[j]=p[(int)x[j]];
	printf("%d %d %d\n%s\n%s\n",n,a,b,p+'a',s);
	std::random_shuffle(s,s+n);
	printf("%s\n",s);
	return 0;
}
