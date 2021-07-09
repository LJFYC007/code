/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2019年10月24日 星期四 08时29分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define inv(x) (Inv[x] ? Inv[x] : Inv[x] = power(x, Mod - 2))
#define getchar() (p1 == p2 and (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++)
typedef long long LL;

char buf[1 << 21], *p1 = buf, *p2 = buf;

const int maxn = 300010;
const int maxx = 800010;
const LL Mod = 19491001;
const int maxm = Mod + 10; 

int n, m, Begin[maxx], Next[maxx], To[maxx], e, W[maxx], Inv[maxm];
int f[maxn], top[maxn], dis[maxn], son[maxn], size[maxn], w[maxn];
LL ans;
struct node 
{ 
    LL a, b; 
    node ( LL A = 0, LL B = 0 ) { a = (A % Mod + Mod) % Mod; b = (B % Mod + Mod) % Mod; }
} pre[maxn], suf[maxn];
node operator + (const node x, LL y) { return node(x.a, x.b + y); }
node operator - (const node x, LL y) { return node(x.a, x.b - y); }
node operator * (const node x, LL y) { return node(x.a * y, x.b * y); }
node operator + (LL x, const node y) { return node(y.a, y.b + x * y.a); }
node operator - (LL x, const node y) { return node(y.a, y.b - x * y.a); }
node operator * (LL x, const node y) { return node(x * y.a, y.b); }

inline void add(const int u, const int v, const int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS1(const int u, const int fa)
{
    size[u] = 1; register int Max = 0;
    for( int i = Begin[u]; i; i = Next[i] ) 
    {
        const int v = To[i]; 
        if ( v ^ fa ) 
        {
            f[v] = u; dis[v] = dis[u] + 1; 
            pre[v] = W[i] == 1 ? pre[u] + w[v] : (W[i] == 2 ? pre[u] - w[v] : pre[u] * w[v]);
            suf[v] = W[i] == 1 ? w[u] + suf[u] : (W[i] == 2 ? w[u] - suf[u] : w[u] * suf[u]);
            DFS1(v, u);
            if ( size[v] > Max ) { Max = size[v]; son[u] = v; }
            size[u] += size[v];
        }
    }
}

inline void DFS2(const int u, const int t)
{
    top[u] = t; if ( son[u] ) DFS2(son[u], t);
    for ( int i = Begin[u]; i; i = Next[i] ) if ( (To[i] ^ f[u]) && (To[i] ^ son[u]) ) DFS2(To[i], To[i]);
}

inline int LCA(register int x, register int y) 
{
    while ( top[x] ^ top[y] ) { if ( dis[top[x]] <= dis[top[y]] ) swap(x, y); x = f[top[x]]; }
    return dis[x] < dis[y] ? x : y;
}

inline int power(LL a, register int b)
{
    LL r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

inline void read(register int &x) 
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { LL x; scanf("%lld", &x); w[i] = x % Mod; pre[i] = suf[i] = node(1, 0); }
    REP(i, 1, n - 1) { int u, v, w; read(u); read(v); read(w);; add(u, v, w); add(v, u, w); }
    DFS1(1, 0); DFS2(1, 1);
    REP(i, 1, m)
    {
        int u, v; read(u); read(v); const int t = LCA(u, v);
        const LL a = suf[u].a, b = suf[u].b, c = suf[t].a, d = suf[t].b;
        const LL e = (a * inv(c)) % Mod, f = ((b - d) * inv(c)) % Mod;
        const LL A = pre[t].a, B = pre[t].b, C = pre[v].a, D = pre[v].b;
        const LL E = (C * inv(A)) % Mod, F = (D - B * E) % Mod;
        ans = (w[u] * e + f) % Mod;
        ans = (ans * E + F) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
