#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define REP(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define DREP(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
#define EREP(i,u) for(int i=start[u];i;i=e[i].next)
#define fi first
#define se second
#define mkr(a,b) make_pair(a,b)
#define SZ(A) ((int)A.size())
template<class T>inline void chkmax(T &a,T b){ if(a<b)a=b;}
template<class T>inline void chkmin(T &a,T b){ if(a>b)a=b;}
inline int read()
{
    int s=0,f=1; char ch=getchar();
    while(!isdigit(ch) && ch!='-')ch=getchar();
    if(ch=='-')ch=getchar(),f=-1;
    while(isdigit(ch))s=s*10+ch-'0',ch=getchar();
    return ~f?s:-s;
}

const int maxn=5e5+20;

struct interval {
    int l,r;
};
interval a[maxn];
int N;
ll ans=1;

#define y1 LJBIANLIANG

int x1[maxn],y1[maxn],x2[maxn],y2[maxn],n,X,Y;

inline void init()
{
    n=read();X=read();Y=read();
    REP(i,1,n)x1[i]=read(),y1[i]=read(),x2[i]=read(),y2[i]=read();
}

#define ull unsigned ll

struct node {
    int x,id;
};
node b[maxn<<1];
int btot;
ull w[maxn];

inline ull Rand()
{
    return (ull)rand()*rand()*rand()+(ull)rand()*rand()+(ull)rand();
}

inline void work()
{
    unordered_map<ull,int>mp;
    btot=0;
    REP(i,1,n)w[i]=Rand();
    REP(i,1,n)b[++btot]=(node){a[i].l,i},b[++btot]=(node){a[i].r,i};
    sort(b+1,b+btot+1,[](node a,node b){ return a.x<b.x;});
    ll now=0,sum=0;
    b[++btot]=(node){N,0};
    REP(i,1,btot)
    {
	mp[sum]+=b[i].x-now;
	now=b[i].x;
	sum^=w[b[i].id];
    }
    ll mx=0;
    for(pair<ull,int> x:mp)
	chkmax(mx,1ll*x.se);
    printf("%lld\n", mx);
    ans=ans*mx;
}

inline void doing()
{
    REP(i,1,n)a[i].l=x1[i],a[i].r=x2[i]; N=X;
    work();
    REP(i,1,n)a[i].l=y1[i],a[i].r=y2[i]; N=Y;
    work();
    printf("%lld\n",ans);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("master.in","r",stdin);
    freopen("master.out","w",stdout);
#endif
    init();
    doing();
    return 0;
}
