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
#define i64 long long
const int M=110,N=100010,mod=998244353;
i64 n,m,f[M][N],s[M][N],ans,T;
int main()
{
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	n=100000;
	m=100;
	f[0][0]=1;
	fr(i,0,n)
		s[0][i]=1;
	fr(i,1,m)
		fr(j,1,n)
		{
			f[i][j]=(s[i-1][j-1]*(2*j-i))%mod;
			s[i][j]=(s[i][j-1]+f[i][j])%mod;
		}
	/*
		f_{i,j}=(2j-i)sum_{k<j}f_{i-1,k}
	*/
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		printf("%lld\n",s[m][n]);
	}
	return 0;
}
