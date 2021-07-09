/***************************************************************
	File name: std.cpp
	Author: huhao
	Create time: Sun 16 Jun 2019 02:37:19 PM CST
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
#define i64 long long
const int N=100010;
const i64 inf=1ll<<60;
i64 n,m,f[N],p[N],q[N],x[N],s[N],t,c[N],l[N],r[N],id[N];
i64 query(int l,int r,i64 _p)
{
//	printf(" %d %d %d\n",l,r,_p);
	if(l==r)
		return f[c[l]]*_p+q[c[l]];
	if((f[c[r]]-f[c[r-1]])*_p<=q[c[r]]-q[c[r-1]])
		return f[c[r]]*_p+q[c[r]];
	r--;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if((f[c[mid+1]]-f[c[mid]])*_p<=q[c[mid+1]]-q[mid])
			r=mid;
		else
			l=mid+1;
		//p=(q[j]-q[i])/(f[i]-f[j])
	}
//	printf("  %d %d %d %d\n",l,c[l],f[c[l]],q[c[l]]);
	return f[c[l]]*_p+q[c[l]];
}
int cmp(int a,int b)
{
	return f[a]>f[b];
}
int main()
{
	n=read();
	f[1]=read();
	m=read();
	f[1]%=m;
	fr(i,1,n)
		p[i]=read();
	fr(i,1,n)
		q[i]=read();
	fr(i,1,n)
		x[i]=read();
	s[t=1]=1;
	c[l[1]=r[1]=1]=1;
	fr(i,2,n)
	{
		f[i]=inf;
		fr(j,1,t)
			f[i]=min(f[i],query(l[j],r[j],p[i]));
		f[i]=(f[i]+x[i])%m;
		s[++t]=i;
//		printf("%d %d %d %d\n",t,s[t],s[t-1],s[t-2]);
		while(t!=1&&s[t]+s[t-2]==s[t-1]*2)
		{
			s[t-1]=s[t];
			t--;
		}
//		printf("%d %d %d\n",t,s[t-1]+1,s[t]);
		l[t]=r[t-1]+1;
		r[t]=r[t-1];
		fr(i,s[t-1]+1,s[t])
			id[i]=i;
		sort(id+s[t-1]+1,id+s[t]+1,cmp);
//		fr(j,s[t-1]+1,s[t])
//			printf("%d%c",id[j],j==s[t]?'\n':' ');
		fr(j,s[t-1]+1,s[t])
		{
			if(j!=s[t-1]+1&&f[id[j]]==f[c[r[t]]]&&q[id[j]]>=q[c[r[t]]])
				continue;
			c[++r[t]]=id[j];
			while(r[t]!=l[t]&&(q[c[r[t]]]<=q[c[r[t]-1]]||(r[t]-l[t]>1&&(f[c[r[t]]]-f[c[r[t]-1]])*(q[c[r[t]-1]]-q[c[r[t]-2]])<=(q[c[r[t]-1]]-q[c[r[t]]]*(f[c[r[t]-2]]-f[c[r[t]-1]])))))
			/*
			 * f[c[t-1]]p+q[c[t-1]]==f[c[t-2]]p+q[c[t-2]]
			 * p=(q[c[t-1]]-q[c[t-2]])/(f[c[t-2]]-f[c[t-1]])
			 * (f[c[t]]-f[c[t-1]])p<=q[c[t-1]]-q[c[t]]
			 */
			{
				c[r[t]-1]=c[r[t]];
				r[t]--;
			}
		}
//		printf("%d %lld\n",i,f[i]);
//		fr(j,1,t)
//			fr(k,l[j],r[j])
//				printf("(%lld %lld)%c",f[c[k]],q[c[k]],k==r[j]?'\n':' ');
	}
	fr(i,1,n)
		printf("%lld%c",f[i],i==n?'\n':' ');
	return 0;
}
