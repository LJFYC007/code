#define SZ 200003
ll MOD=998244353;
Edg
#define P 19
typedef pair<int,int> pii;
int n,fa[SZ],dep[SZ];
int cc=0,app[SZ],bs[SZ],cx[SZ],c2=0;
pii pp[SZ],minn[SZ][P];
void dfs(int x)
{
    ++cc; app[x]=cc; pp[cc]=pii(dep[x],x); cx[++c2]=x;
    for(int e=fst[x];e;e=nxt[e])
    {
        int b=vb[e]; if(b==fa[x]) continue;
        fa[b]=x; dep[b]=dep[x]+1;
        dfs(b); pp[++cc]=pii(dep[x],x);
    }
}
void build()
{
    for(int i=1;i<=cc;i++) minn[i][0]=pp[i];
    for(int i=1;i<=cc;i++)
    {
        int g=0;
        while((1<<g)<=i) ++g;
        bs[i]=g-1;
    }
    for(int p=1;p<P;p++)
    {
        for(int i=1;i<=cc;i++)
        {
            if(i+(1<<p)-1>cc) break;
            minn[i][p]=min(minn[i][p-1],minn[i+(1<<(p-1))][p-1]);
        }
    }
}
int lca(int a,int b)
{
    a=app[a]; b=app[b];
    if(a>b) swap(a,b);
    int l2=bs[b-a+1];
    return min(minn[a][l2],minn[b-(1<<l2)+1][l2]).second;
}
int dis(int a,int b)
{
    int l=lca(a,b);
    return dep[a]+dep[b]-dep[l]*2;
}
pii mg(pii a,int b)
{
    int s[3]={a.fi,a.se,b};
    pii aa; int ans=-1;
    for(int i=0;i<3;i++)
    {
        for(int j=i+1;j<3;j++)
        {
            int d=dis(s[i],s[j]);
            if(d>ans) ans=d, aa=pii(s[i],s[j]);
        }
    }
    return aa;
}
//a,b为直径，c为衔接处 
pii mg(pii a,pii b,pii c)
{
    pii aa=a; int ans=dis(a.fi,a.se);
    {
        int tmp=dis(b.fi,b.se);
        if(tmp>ans) ans=tmp, aa=b;
    }
    int as[3]={a.fi,a.se,c.fi},bs[3]={b.fi,b.se,c.se};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            int d=dis(as[i],bs[j]);
            if(d>ans) ans=d, aa=pii(as[i],bs[j]);
        }
    }
    return aa;
}
int m;
struct Tuple {int f; pii z;};
int ans=0,ff[SZ];
pii zj[SZ];
int gf(int x)
{
    return (ff[x]>0)?gf(ff[x]):x;
}
struct Msg
{
int ga,gb,fa,fb;
pii pa,pb;
Msg() {ga=gb=0;}
Msg(int a,int b,int c,int d,pii x,pii y) {ga=a; gb=b; fa=c; fb=d; pa=x; pb=y;}
};
//use the return value to reverse!
Msg uni(int u,int v)
{
    int ga=gf(u),gb=gf(v);
    if(ga==gb) return Msg();
    if(ff[ga]>ff[gb]) swap(ga,gb);
    Msg rt=Msg(ga,gb,ff[ga],ff[gb],zj[ga],zj[gb]);
    pii tmp=mg(zj[ga],zj[gb],pii(u,v));
    zj[ga]=tmp; ff[ga]+=ff[gb]; ff[gb]=ga;
    return rt;
}
void rev(Msg p)
{
    if(!p.ga) return;
    ff[p.ga]=p.fa; ff[p.gb]=p.fb;
    zj[p.ga]=p.pa; zj[p.gb]=p.pb;
}
#define ST 8888888
struct edg {int u,v,l,r;}es[SZ];
namespace seg
{
const int M=131072;
int nx[ST],fs[M+M+3],bb[ST],C=0;
Msg tmp[ST];
void split(int l,int r,int g)
{
    for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) 
        {++C; bb[C]=g; nx[C]=fs[l^1]; fs[l^1]=C;}
        if(r&1)
        {++C; bb[C]=g; nx[C]=fs[r^1]; fs[r^1]=C;}
    }
}
int cm[M+M+3];
int tat[ST];
void dfs(int x,int zjj=0)
{
    for(int e=fs[x];e;e=nx[e])
    {
        int b=bb[e];
        tmp[e]=uni(es[b].u,es[b].v);
        int a=tmp[e].ga;
        if(!a) continue;
        zjj=max(zjj,dis(zj[a].fi,zj[a].se));
    }
    if(x>M) cm[x]=zjj;
    else
    {
        dfs(x*2,zjj);
        dfs(x*2+1,zjj);
    }
    int tn=0;
    for(int e=fs[x];e;e=nx[e]) tat[++tn]=e;
    while(tn) rev(tmp[tat[tn--]]);
}
}
#define BUFSIZE 300000
char ch,B[1<<15],*S=B,*T=B;
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?0:*S++)
#define isd(c) (c>='0'&&c<='9')
int aa,bb;int F(){
    while(ch=getc(),!isd(ch)&&ch!='-');ch=='-'?aa=bb=0:(aa=ch-'0',bb=1);
    while(ch=getc(),isd(ch))aa=aa*10+ch-'0';return bb?aa:-aa;
}
#define gi F()
namespace fob {char b[BUFSIZE]={},*f=b,*g=b+BUFSIZE-2;}
#define pob (fwrite(fob::b,sizeof(char),fob::f-fob::b,stdout),fob::f=fob::b,0)
#define pc(x) (*(fob::f++)=(x),(fob::f==fob::g)?pob:0)
struct foce {~foce() {pob; fflush(stdout);}} _foce;
namespace ib {char b[100];}
inline void pint(int x)
{
    if(x==0) {pc(48); return;}
    if(x<0) {pc('-'); x=-x;}
    char *s=ib::b;
    while(x) *(++s)=x%10, x/=10;
    while(s!=ib::b) pc((*(s--))+48);
}
int main()
{
    FO(speed)
    n=gi, m=gi;
    for(int i=1;i<n;i++)
    {
        es[i].u=gi, es[i].v=gi, es[i].l=gi, es[i].r=gi;
        adde(es[i].u,es[i].v);
    }
    for(int i=1;i<=n;i++) ff[i]=-1, zj[i]=pii(i,i);
    dfs(1); build();
    for(int i=1;i<n;i++)
        seg::split(es[i].l,es[i].r,i);
    seg::dfs(1);
    for(int i=1;i<=m;i++)
    {
        int q=gi;
        pint(seg::cm[q+seg::M]); pc(10);
    }
}
