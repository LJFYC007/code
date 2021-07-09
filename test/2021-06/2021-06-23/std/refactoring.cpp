#include<bits/stdc++.h>
const int maxn=100000+10;
long long ans=1LL<<60; int n,a[maxn],b[maxn],ansp[maxn],op;
struct node
{
	int x;
	inline bool friend operator < ( const node &p,const node &q )
	{
		if ( op== 1 ) return a[q.x]<a[p.x];
		if ( op==-1 ) return a[p.x]<a[q.x];
		return true;
	}
} ;
inline void calc ( int *A,int m )
{
	std::priority_queue<node> Q;
	for ( int i=1;i<=m;i++ )
		if ( A[i]>0 ) Q.push((node){A[i]});
		else b[-A[i]]=a[Q.top().x],Q.pop();
}
inline void solve ( int *S,int *T,int m )
{
	int A[maxn]={0},B[maxn]={0};
	for ( int i=1;i<=m;i++ ) A[S[i]]++,B[T[i]]++;
	for ( int l=1,r=1;l<=n;l=r+1 )
	{
		int w=A[l]-B[l]; r=l;
		while ( r<=n and w!=0 ) r++,w+=A[r]-B[r];
		int tag=0;
		for ( int i=l;i<=r;i++ )
		{
			if ( A[i] ) { tag= 1;break; }
			if ( B[i] ) { tag=-1;break; }
		}
		if ( !tag ) continue;
		int C[maxn]={0},tot=0;
		if ( tag== 1 ) for ( int i=l;i<=r;i++ )
		{
			if ( A[i] ) C[++tot]=i;
			if ( B[i] ) C[++tot]=-i;
		}
		if ( tag==-1 ) for ( int i=r;i>=l;i-- )
		{
			if ( A[i] ) C[++tot]=i;
			if ( B[i] ) C[++tot]=-i;
		}
		op=tag; calc(C,tot);
	}
}
inline void calc ( int k )
{
	int AS[maxn]={0},BS[maxn]={0},totAS=0,totBS=0;
	int AT[maxn]={0},BT[maxn]={0},totAT=0,totBT=0;
	for ( int i=1;i<=n;i++ ) ((a[i]&1)^k) ? AS[++totAS]=i : BS[++totBS]=i;
	for ( int i=1;i<=n;i++ ) ((i&1)^1) ? AT[++totAT]=i : BT[++totBT]=i;
	long long res=0;
	for ( int i=1;i<=totAS;i++ ) res+=std::abs(AS[i]-AT[i]);
	for ( int i=1;i<=totBS;i++ ) res+=std::abs(BS[i]-BT[i]);
	if ( res>ans ) return;
	for ( int i=1;i<=n;i++ ) b[i]=0;
	solve(AS,AT,totAS);
	solve(BS,BT,totBS);
	if ( res<ans or b[1]<ansp[1] )
	{
		ans=res;
		for ( int i=1;i<=n;i++ ) ansp[i]=b[i];
	}
}
signed main()
{
	scanf("%d",&n); int cnt[2]={0};
	for ( int i=1;i<=n;i++ ) scanf("%d",&a[i]),cnt[a[i]&1]++;
	if ( cnt[1]>=cnt[0] ) calc(1);
	if ( cnt[0]>=cnt[1] ) calc(0);
	for ( int i=1;i<=n;i++ ) printf("%d%c",ansp[i]," \n"[i==n]);
	return 0;
}
