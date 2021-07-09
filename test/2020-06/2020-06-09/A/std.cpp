/**************************************************************
    Problem: 3681
    User: ez_dcx
    Language: C++
    Result: Accepted
    Time:826 ms
    Memory:44120 kb
****************************************************************/
 
 
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define inf 1000000000
 
struct node { int s,t,v; }h[100010];
 
vector<int> v[100010],g[200010];
 
int fa[200010][20],val[200010],mn[200010],mx[200010],from[200010];
int num[100010],dfn[100010],out[100010],n,m,cl,tt,root,type;
 
inline int rd()
{
    int x=0;char ch=getchar();
    for (;ch<'0'||ch>'9';ch=getchar());
    for (;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
    return x;
}
 
inline void print(ll x)
{
    static char s[233];
    if (!x) { putchar('0');putchar('\n');return; }
    int tot=0;
    for (;x;x/=10) s[++tot]=x%10+'0';
    for (;tot;tot--) putchar(s[tot]);
    putchar('\n');
}
 
inline int find(int x) { return (x==from[x])?x:from[x]=find(from[x]); }
 
inline bool cmp(const node &x,const node &y) { return x.v>y.v; }
 
inline void pre_dfs(int x)
{
    dfn[x]=++cl;
    for (int t:v[x]) if (!dfn[t]) pre_dfs(t);
    out[x]=cl;
}
 
inline void pre_dfs1(int x)
{
    for (int i=1;i<20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
    mn[x]=n+1;mx[x]=0;
    if (x<=n) { mn[x]=mx[x]=++cl;return; }
    for (int t:g[x]) fa[t][0]=x,pre_dfs1(t),mn[x]=min(mn[x],mn[t]),mx[x]=max(mx[x],mx[t]);
}
 
inline int jump(int x,int y)
{
    for (int i=19;~i;i--) if (fa[x][i]&&val[fa[x][i]]>=y) x=fa[x][i];
    return x;
}
 
struct point
{
    int x,y,id;
    point(int xx=0,int yy=0,int id1=0):x(xx),y(yy),id(id1) {}
}a[100010];
 
struct tree
{
    int mn[2],mx[2],ls,rs;
    ll tag,sum;
}t[100010];
 
int fat[100010],id[100010];
 
inline bool cmp1(const point &x,const point &y) { return x.x<y.x; }
inline bool cmp2(const point &x,const point &y) { return x.y<y.y; }
 
inline void pushup(const int &o)
{
    t[o].sum=num[a[o].id];
    t[o].mn[0]=t[o].mx[0]=a[o].x;
    t[o].mn[1]=t[o].mx[1]=a[o].y;
    for (int i=0;i<2;i++)
    {
        t[o].mn[i]=min(t[o].mn[i],min(t[t[o].ls].mn[i],t[t[o].rs].mn[i]));
        t[o].mx[i]=max(t[o].mx[i],max(t[t[o].ls].mx[i],t[t[o].rs].mx[i]));
    }
}
 
inline int build(int l,int r,bool flag)
{
    int mid=(l+r)>>1;
    nth_element(a+l,a+mid,a+r+1,(!flag)?cmp1:cmp2);
    if (l<mid) fat[t[mid].ls=build(l,mid-1,flag^1)]=mid;
    if (r>mid) fat[t[mid].rs=build(mid+1,r,flag^1)]=mid;
    pushup(mid);
    return mid;
}
 
inline void modify(int o,pii h1,pii h2,int hh)
{
    if (t[o].mn[0]>h1.second||t[o].mx[0]<h1.first||t[o].mn[1]>h2.second||t[o].mx[1]<h2.first) return;
    if (t[o].mn[0]>=h1.first&&t[o].mx[0]<=h1.second&&t[o].mn[1]>=h2.first&&t[o].mx[1]<=h2.second) { t[o].tag+=hh;return; }
    if (a[o].x>=h1.first&&a[o].x<=h1.second&&a[o].y>=h2.first&&a[o].y<=h2.second) t[o].sum+=hh;
    if (t[o].ls) modify(t[o].ls,h1,h2,hh);
    if (t[o].rs) modify(t[o].rs,h1,h2,hh);
}
 
int main()
{
    freopen("A.in", "r", stdin);
    freopen("A1.out", "w", stdout);
    n=rd();m=rd();type=rd();
    for (int i=1;i<=n;i++) num[i]=rd();
    for (int i=1;i<n;i++)
    {
        int x=rd(),y=rd(),z=rd();
        v[x].push_back(y);
        v[y].push_back(x);
        h[i]=(node){x,y,z};
    }
    cl=0;pre_dfs(1);
    tt=n;sort(h+1,h+n,cmp);
    for (int i=1;i<=n;i++) from[i]=i,val[i]=inf;
    for (int i=1;i<n;i++)
    {
        int x=h[i].s,y=h[i].t,z=h[i].v;
        int f1=find(x),f2=find(y);val[++tt]=z;
        g[tt].push_back(f1);g[tt].push_back(f2);
        from[f1]=from[f2]=from[tt]=tt;
    }
    cl=0;pre_dfs1(tt);
    for (int i=1;i<=n;i++) a[i]=point(dfn[i],mn[i],i);
    t[0].mn[0]=t[0].mn[1]=n+1;
    root=build(1,n,0);
    for (int i=1;i<=n;i++) id[a[i].id]=i;
    ll ans=0;
    while (m--)
    {
        int p=rd();
        if (p==1)
        {
            int x=rd();
            if (type) x=(x+ans)%n+1;
            ans=t[id[x]].sum;
            for (int i=id[x];i;i=fat[i]) ans+=t[i].tag;
            print(ans);
        }
        else
        {
            int y=rd(),d=rd(),x=rd();
            if (type) x=(x+ans)%n+1;
            int hh=jump(x,d);
            modify(root,pii(dfn[x],out[x]),pii(mn[hh],mx[hh]),y);
        }
    }
    return 0;
}
/*
5 8 0
0 0 0 0 0
4 3 1
1 3 2
1 5 4
2 3 3
2 4 1 1
2 3 2 5
2 6 3 1
1 1
1 2
1 3
1 4
1 5
*/
