/***************************************************************
	File name: tree.cpp
	Author: huhao
	Create time: Tue 24 Sep 2019 08:54:39 PM CST
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
#include<vector>
#include<set>
const int N=1000010,NN=10000010;
int n,a[N],M[NN],L[N],R[N],cnt,p[N],v[NN],m,f[N];
vector<int>t[N];
void add(int k,int i)
{
	while(k!=1)
	{
		t[M[k]].push_back(i);
		int P=p[M[k]];
		while(k%P==0)
			k/=P;
	}
}
void calc(int l,int r,int F)
{
	if(l>r)
		return;
	fr(i,0,r-l)
	{
		if(L[l+i]<=l&&R[l+i]>=r)
		{
			f[l+i]=F;
			calc(l,l+i-1,l+i);
			calc(l+i+1,r,l+i);
			return;
		}
		if(L[r-i]<=l&&R[r-i]>=r)
		{
			f[r-i]=F;
			calc(l,r-i-1,r-i);
			calc(r-i+1,r,r-i);
			return;
		}
	}
	printf("impossible\n");
	exit(0);
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=10000000;
	fr(i,2,n)
	{
		if(!v[i])
		{
			p[++m]=i;
			M[i]=m;
		}
		fr(j,1,m)
			if((long long)i*p[j]<=n)
			{
				cnt++;
				v[i*p[j]]=1;
				M[i*p[j]]=j;
				if(i%p[j]==0)
					break;
			}
			else
				break;
	}
	n=read();
	fr(i,1,n)
	{
		a[i]=read();
		add(a[i],i);
		L[i]=1;
		R[i]=n;
	}
	fr(i,1,m)
	{
		int k=0;
		for(auto j:t[i])
		{
			if(k)
			{
				L[j]=max(L[j],k+1);
				R[k]=min(R[k],j-1);
			}
			k=j;
		}
	}
	calc(1,n,0);
	fr(i,1,n)
		printf("%d%c",f[i],i==n?'\n':' ');
	return 0;
}
