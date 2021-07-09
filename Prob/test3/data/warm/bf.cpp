/***************************************************************
	File name: bf.cpp
	Author: huhao
	Create time: Sun 16 Jun 2019 10:11:55 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define i64 long long
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
const int N=100010;
i64 n,f[N],k,p[N],q[N],r[N];
int main()
{
	n=read();
	f[1]=read();
	k=read();
	f[1]%=k;
	fr(i,1,n)
		p[i]=read();
	fr(i,1,n)
		q[i]=read();
	fr(i,1,n)
		r[i]=read();
	fr(i,2,n)
	{
		f[i]=1ll<<60;
		fr(j,1,i-1)
			f[i]=min(f[i],p[i]*f[j]+q[j]);
		f[i]=(f[i]+r[i])%k;
	}
	fr(i,1,n)
		printf("%lld%c",f[i],i==n?'\n':' ');
	return 0;
}
