/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2020-03-09 08:37:06
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define i64 long long
#define pii std::pair<i64,i64>
#include<vector>
const int N=100010,M=20000010,mod=998244353,mod1=19491001,mod2=1000000007;
i64 n,m,d[N],r[N],l[N],Q[N],_l,_r,p1[N],p2[N],cnt,p[N],ans,Ans,f[N];
int s[M][2];
pii h[M];
std::vector<pii> e[N];
pii operator*(pii a,i64 b){ return pii(a.first*p1[b]%mod1,a.second*p2[b]%mod2); }
pii operator+(pii a,pii b){ return pii((a.first+b.first)%mod1,(a.second+b.second)%mod2); }
int modify(int k,int l,int r,int p,int w)
{
	cnt++; s[cnt][0]=s[k][0]; s[cnt][1]=s[k][1]; k=cnt;
	if(l==r){ h[k]=pii(w,w); return k; }
	int mid=(l+r)>>1;
	if(p<=mid) s[k][0]=modify(s[k][0],l,mid,p,w);
	else s[k][1]=modify(s[k][1],mid+1,r,p,w);
	h[k]=h[s[k][0]]+h[s[k][1]]*(mid-l+1);
	return k;
}
int cmp(int a,int b,int l,int r)
{
	if(l==r) return h[a].first>h[b].first;
	int mid=(l+r)>>1;
	if(h[s[a][1]]==h[s[b][1]]) return cmp(s[a][0],s[b][0],l,mid);
	else return cmp(s[a][1],s[b][1],mid+1,r);
}
void query(int k,int l,int r)
{
	if(l==r)
	{
		if(h[k].first) Ans=1;
		if(Ans) printf("%d",int(h[k].first));
		return ;
	}
	int mid=(l+r)>>1;
	query(s[k][1],mid+1,r); query(s[k][0],l,mid);
}
int main()
{
	freopen("tried.in","r",stdin); freopen("tried1.out","w",stdout);
	n=read(); m=read();
	p1[0]=p2[0]=1; p1[1]=11; p2[1]=233;
	fr(i,2,n){ p1[i]=p1[i-1]*p1[1]%mod1; p2[i]=p2[i-1]*p2[1]%mod2; }
	fr(i,1,m)
	{
		int u=read(),v=read(),w=read();
		e[u].push_back(pii(v,w)); d[v]++;
		if(w) p[u]=1;
	}
	_l=1;
	fr(i,1,n) if(!d[i]) Q[++_r]=i;
	while(_l<=_r)
	{
		int u=Q[_l++];
		if(!cmp(r[u],0,1,n)) f[u]++;
		fr(i,0,e[u].size()-1)
		{
			int v=e[u][i].first,w=e[u][i].second,R=modify(r[u],1,n,l[u]+1,w);
			if(cmp(R,r[v],1,n)){ r[v]=R; l[v]=l[u]+1; f[v]=f[u]; }
			else if(!cmp(r[v],R,1,n)) f[v]=(f[v]+f[u])%mod;
			d[v]--; if(!d[v]) Q[++_r]=v;
		}
	}
	fr(i,1,n) if(p[i]&&d[i]){ printf("inf\ninf\n"); return 0; }
	fr(i,1,n) if(cmp(r[i],ans,1,n)) ans=r[i];
	query(ans,1,n);
	if(!Ans) putchar('0');
	printf("\n");
	Ans=0;
	fr(i,1,n) if(!cmp(r[i],ans,1,n)&&!cmp(ans,r[i],1,n))
	{
		if(d[i]){ printf("inf\n"); return 0; }
		Ans=(Ans+f[i])%mod;
	}
	printf("%d\n",int(Ans));
	return 0;
}
