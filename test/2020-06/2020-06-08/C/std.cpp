/**************************************************************
    Problem: 3680
    User: 2019hnyl05
    Language: C++
    Result: Accepted
    Time:565 ms
    Memory:52236 kb
****************************************************************/
 
 
/*
Author: QAQAutomaton
Lang: C++
Code: C.cpp
Mail: lk@qaq-am.com
Blog: https://www.qaq-am.com/
*/
#include<bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
#define x first
#define y second
using namespace std;
typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef complex<double> cp;
typedef pair<int,int> pii;
int inf;
const double eps=1e-8;
const double pi=acos(-1.0);
template<class T,class T2>int chkmin(T &a,T2 b){return a>b?a=b,1:0;}
template<class T,class T2>int chkmax(T &a,T2 b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T,class T2>T mmin(T a,T2 b){return a<b?a:b;}
template<class T,class T2>T mmax(T a,T2 b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
template<class T>int dcmp(T a,T b){return a>b;}
template<int *a>int cmp_a(int x,int y){return a[x]<a[y];}
#define min mmin
#define max mmax
#define abs aabs
struct __INIT__{
    __INIT__(){
        memset(&inf,0x3f,sizeof(inf));
    }
}__INIT___;
namespace io {
    const int SIZE = (1 << 21) + 1;
    char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
    // getchar
    #define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
    // print the remaining part
    inline void flush () {
        fwrite (obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }
    // putchar
    inline void putc (char x) {
        *oS ++ = x;
        if (oS == oT) flush ();
    }
    template<typename A>
    inline bool read (A &x) {
        for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;else if(c==EOF)return 0;
        for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
        return 1;
    }
    inline bool read (char &x) {
        while((x=gc())==' '||x=='\n' || x=='\r');
        return x!=EOF;
    }
    inline bool read(char *x){
        while((*x=gc())=='\n' || *x==' '||*x=='\r');
        if(*x==EOF)return 0;
        while(!(*x=='\n'||*x==' '||*x=='\r'||*x==EOF))*(++x)=gc();
        *x=0;
        return 1;
    }
    template<typename A,typename ...B>
    inline bool read(A &x,B &...y){
        return read(x)&&read(y...);
    }
    template<typename A>
    inline bool write (A x) {
        if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
        while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
        while (qr) putc (qu[qr --]);
        return 0;
    }
    inline bool write (char x) {
        putc(x);
        return 0;
    }
    inline bool write(const char *x){
        while(*x){putc(*x);++x;}
        return 0;
    }
    inline bool write(char *x){
        while(*x){putc(*x);++x;}
        return 0;
    }
    template<typename A,typename ...B>
    inline bool write(A x,B ...y){
        return write(x)||write(y...);
    }
    //no need to call flush at the end manually!
    struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: read;
using io :: putc;
using io :: write;
const int p=998244353;
struct Z{
    uint x;
    Z(){}
    Z(uint a){
        x=a;
    }
};
inline uint modp(const uint x){
    return x<p?x:x-p;
}
inline Z operator+(const Z x1, const Z x2) { return modp(x1.x+x2.x);}
inline Z operator-(const Z x1, const Z x2) { return modp(x1.x+p-x2.x);}
inline Z operator-(const Z x) {return x.x?p-x.x:0;}
inline Z operator*(const Z x1, const Z x2) { return static_cast<ull>(x1.x)*x2.x%p;}
void exgcd(int a,int b,int &x,int &y){
    if(!b){x=1;y=0;return;}
    exgcd(b,a%b,y,x);
    y-=(a/b)*x;
}
inline Z Inv(const Z a){
    int x,y;
    exgcd(p,a.x,x,y);
    return y<0?y+=p:y;
}
inline Z operator/(const Z x1, const Z x2) { return x1*Inv(x2);}
 
inline Z &operator+=(Z &x1, const Z x2) { return x1 = x1 + x2; }
inline Z &operator-=(Z &x1, const Z x2) { return x1 = x1 - x2; }
inline Z &operator*=(Z &x1, const Z x2) { return x1 = x1 * x2; }
inline Z &operator/=(Z &x1, const Z x2) { return x1 = x1 / x2; }
int xto[400005],lst[400005],beg[100005],e=1;
void add(int u,int v){xto[++e]=v;lst[e]=beg[u];beg[u]=e;}
int fa[200005],dfn[200005],t,vis[200005],c;
vector<int> to[200005];
void makec(int x,int y){
    ++c;
    while(x!=y){
        vis[x]=1;
        to[c].emplace_back(x);to[x].emplace_back(c);
        x=fa[x];
    }
    to[c].emplace_back(x);to[x].emplace_back(c);
}
void dfs(int x,int f){
    fa[x]=xto[f];
    dfn[x]=++t;
    for(int i=beg[x];i;i=lst[i])if(i!=f){
        if(!dfn[xto[i]]){dfs(xto[i],i^1);if(!vis[xto[i]]){to[x].emplace_back(xto[i]);to[xto[i]].emplace_back(x);}}
        else if(dfn[xto[i]]<dfn[x])makec(x,xto[i]);
    }
}
 
Z dp[200005][3];
int n,m;
Z w[2000005];
Z *f[200005],*at;
int len[200005];
Z *newI(int m){
    memset(at,0,sizeof(Z)*m);
    Z *od=at;
    at+=m;
    return od;
}
Z fpm(Z a,int b){
    Z c(1);
    for(;b;b>>=1,a*=a)if(b&1)c*=a;
    return c;
}
const int _g=3;
const int mxl=19;
const int mxs=1<<mxl;
Z _w[mxs<<1|5];
int curn=1,rev[mxs|5],N;
Z iN;
void setn(int n){
    for(int i=1;i<n;++i)rev[i]=rev[i>>1]>>1|((i&1)*(n>>1));    
    N=n;
    iN=Inv(N);
    while(curn<n){
        Z w0=fpm(_g,(p-1)/(curn<<1)),w(1);
        for(int i=0;i<curn;++i){_w[i+curn]=w;w*=w0;}
        curn<<=1;
    }
}
void dft(Z *a){
    static ull t[mxs|5];
    for(int i=0;i<N;++i){
        t[i]=a[rev[i]].x;
    }
    for(int i=1;i<N;i<<=1){
        if(i==1048576)for(int j=0;j<N;++j)t[i]%=p;
        for(int j=0;j<N;j+=i+i){
            for(int k=0;k<i;++k){
                const ull x=t[j+k+i]*_w[i+k].x%p;
                t[j+k+i]=t[j+k]+p-x;t[j+k]+=x;
            }
        }
    }
    for(int i=0;i<N;++i)a[i]=t[i]%p;
}
void idft(Z *a){
    reverse(a+1,a+N);
    dft(a);
    for(int i=0;i<N;++i)a[i]*=iN;
}
Z w1[1<<19|5],w2[1<<19|5];
void mul(Z *f,int &n,Z *g,int m){
    int N=1;
    while(N<=n+m)N<<=1;
    for(int i=0;i<=n;++i)w1[i]=f[i];
    for(int i=n+1;i<N;++i)w1[i]=0;
    for(int i=0;i<=m;++i)w2[i]=g[i];
    for(int i=m+1;i<N;++i)w2[i]=0;
    setn(N);
    dft(w1);
    dft(w2);
    for(int i=0;i<N;++i)w1[i]*=w2[i];
    idft(w1);
    n+=m;
    for(int i=0;i<=n;++i)f[i]=w1[i];
}
void solve(int l,int r){
    if(l==r)return; 
    int mid=(l+r)>>1;
    solve(l,mid);
    solve(mid+1,r);
    mul(f[l],len[l],f[mid+1],len[mid+1]);
}
Z h[200005];
int a[200005];
int node[200005];
namespace circle{
    Z dp[2][2],nx[2][2];
    void init(){
        dp[0][0]=dp[1][1]=1;dp[0][1]=dp[1][0]=0;
    }
    void add(Z *f){
        for(int i=0;i<2;++i)for(int j=0;j<2;++j)nx[i][j]=0;
        for(int i=0;i<2;++i)for(int j=0;j<2;++j)for(int k=0;k<2;++k)nx[i][k]+=dp[i][j]*f[(!j)+k];
        for(int i=0;i<2;++i)for(int j=0;j<2;++j)dp[i][j]=nx[i][j];
    }
    void output(Z *f){
        for(int i=0;i<2;++i)for(int j=0;j<2;++j)f[(!i)+j]+=dp[i][j];
    }
}
void calc(int x,int fa){
    for(auto i:to[x])if(i!=fa)calc(i,x);
    //dp[i][j]  j edges to father
    if(x<=n){
        at=w;
        m=0;
        for(auto i:to[x])if(i!=fa){
            if(i<=n){
                f[++m]=newI(2);             
                len[m]=1;
                f[m][1]=dp[i][0];
                f[m][0]=dp[i][1];
            }
            else{
                f[++m]=newI(3);             
                len[m]=2;
                f[m][2]=dp[i][0];
                f[m][1]=dp[i][1];
                f[m][0]=dp[i][2];
            }
        }
        if(m)solve(1,m);
        else{
            m=1;f[1]=newI(1);
            len[1]=0;f[1][0]=1;
        }
        for(int i=0;i<=len[1];++i)h[i]=f[1][i];
        for(int i=1;i<=len[1];++i)h[i]+=h[i-1];
        for(int i=0;i<=2;++i)if(i<=a[x])dp[x][i]=h[min(len[1],a[x]-i)];
    }
    else{
        m=0;
        for(auto i:to[x])node[++m]=i;
        for(int i=1;i<=m;++i)node[i+m]=node[i];
        int at=1;
        while(node[at]!=fa)++at;
        circle::init();
        for(int i=at+1;i<at+m;++i){
            circle::add(dp[node[i]]);
        }
        circle::output(dp[x]);
    }
}
signed main(){
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int u,v;
    read(n,m);
    c=n;
    for(int i=1;i<=m;++i){
        read(u,v);
        add(u,v);
        add(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i)read(a[i]);
    calc(1,0);
    write(dp[1][0].x,'\n');
    return 0;
}
