#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n,q,a[1000005],k,rt[1000005],dp[1000005],up[1000005],f[1000005],ft;
int ls[20000005],rs[20000005],ct,pn=2e6;
double sum[20000005],lg[2000005];
bool cmp(const int x,const int y)
{
	return x>y;
}
void pushup(int x)
{
	sum[x]=max(sum[ls[x]],sum[rs[x]]);
}
int modify(int x,int l,int r,int qx,double v)
{
	if(l>qx||r<qx) return x;
	if(!x)
	{
		x=++ct;
		sum[x]=ls[x]=rs[x]=0;
	}
	if(l==r)
	{
		sum[x]=v;
		return x;
	}
	int mid=(l+r)/2;
	ls[x]=modify(ls[x],l,mid,qx,v);
	rs[x]=modify(rs[x],mid+1,r,qx,v);
	pushup(x);
	return x;
}
void query(int x,int l,int r,int qx,double &ans)
{
	if(l>qx||!x||sum[x]+lg[qx-l+k]<ans) return;
	if(l==r)
	{
		ans=max(ans,sum[x]+lg[qx-l+k]);
		return;
	}
	int mid=(l+r)/2;
	if(r>qx)
	{
		query(rs[x],mid+1,r,qx,ans);
		query(ls[x],l,mid,qx,ans);
		return;
	}
	double q1=sum[ls[x]]+lg[qx-l+k],q2=sum[rs[x]]+lg[qx-(mid+1)+k];
	if(q2>q1)
	{
		query(rs[x],mid+1,r,qx,ans);
		query(ls[x],l,mid,qx,ans);
	}
	else
	{
		query(ls[x],l,mid,qx,ans);
		query(rs[x],mid+1,r,qx,ans);
	}
}
int main()
{
//	freopen("ex_years2.in","r",stdin);
	for(int i=1;i<=pn;i++)
		lg[i]=log(i); 
	sum[0]=-1e9;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=n;i>0;i--)
	{
		int u=lower_bound(f+1,f+ft+1,a[i],cmp)-f;
		f[u]=a[i];
		up[i]=u;
		if(u>ft) ft++;
	}
	ft=0;
	for(int i=1;i<=n;i++)
	{
		int u=lower_bound(f+1,f+ft+1,a[i])-f;
		f[u]=a[i];
		dp[i]=u;
		if(u>ft) ft++;
	}
	printf("%d\n",ft);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&k);
		ct=0;
		for(int j=1;j<=ft;j++)
			rt[j]=0;
		double ans=-1e9;
		for(int j=1;j<=n;j++)
		{
			if(dp[j]+up[j]!=ft+1) continue;
			double nw=-1e9;
			if(dp[j]==1) nw=0;
			else query(rt[dp[j]-1],1,n,a[j],nw);
			rt[dp[j]]=modify(rt[dp[j]],1,n,a[j],nw);
			if(dp[j]==ft) ans=max(ans,nw);
		}
		printf("%.15f\n",ans);
	}
	return 0;
}
