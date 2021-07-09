/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月08日 星期一 11时10分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(vector<int> &f, int inv)
{
    int n = f.size();
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) ) 
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod ) 
            {
                int x = f[i + j], y = sum * f[i + Mid + j] % Mod;
                f[i + j] = (x + y) % Mod; f[i + Mid + j] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
}

int n, m, k, f[maxn][2][2], Begin[maxn], Next[maxn], To[maxn], e = 1, a[maxn];
int dfn[maxn], tot, b[maxn];
bool use[maxn], vis[maxn];
vector<int> p;
vector< vector<int> > t;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Mul(vector<int> &a, vector<int> b)
{
    int len1 = a.size(), len2 = b.size();
    int len = 1; while ( len <= (len1 + len2) ) len <<= 1;
    a.resize(len); b.resize(len);
    NTT(a, 1); NTT(b, 1);
    REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod;
    NTT(a, -1); a.resize(len1 + len2); 
}

inline vector<int> Solve(int l, int r)
{
    vector<int> a;
    if ( l == r ) { a = t[l]; return a; }
    int Mid = l + r >> 1;
    vector<int> b; a = Solve(l, Mid); b = Solve(Mid + 1, r);
    Mul(a, b); return a;
}

inline void DFS(int u, int fa)
{
    vector< vector<int> > g[2];
    dfn[u] = ++ tot; int k = 0; bool flag = false; 
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[i] ) continue ; vis[i] = vis[i ^ 1] = true;
        if ( !dfn[v] ) 
        {
            DFS(v, u); ++ k;
            if ( !use[u] ) 
            {
                p.resize(2); p[0] = f[v][0][0]; p[1] = f[v][1][0];
                g[0].emplace_back(p);
                p.resize(2); 
                if ( !f[v][0][1] && !f[v][1][1] ) p[0] = f[v][0][0], p[1] = f[v][1][0];
                else p[0] = f[v][0][1], p[1] = f[v][1][1];
                g[1].emplace_back(p);
            }
            else
            {
                use[u] = false;
                p.resize(3); p[0] = f[v][0][0]; p[1] = (f[v][1][0] + f[v][0][1]) % Mod; p[2] = f[v][1][1];
                g[0].emplace_back(p); g[1].emplace_back(p);
            }
        }
        else if ( dfn[v] < dfn[u] ) { flag = true; use[v] = true; }
    }
    if ( !k ) 
    {
        if ( flag ) 
        {
            if ( b[u] > 1 ) f[u][0][0] = 1;
            if ( b[u] > 0 ) f[u][1][0] = f[u][0][1] = 1;
            f[u][1][1] = 1;
        }
        else
        {
            if ( b[u] > 0 ) f[u][0][0] = 1;
            f[u][1][0] = 1;
        }
        return ;
    }
    t = g[0]; p = Solve(0, k - 1);
    for ( int i = 0; i < p.size(); ++ i ) 
    {
        if ( flag + 1 + i <= b[u] ) f[u][0][0] = (f[u][0][0] + p[i]) % Mod;
        if ( flag + i <= b[u] ) f[u][1][0] = (f[u][1][0] + p[i]) % Mod;
    }
    t = g[1]; p = Solve(0, k - 1);
    for ( int i = 0; i < p.size(); ++ i )
    {
        if ( 1 + i <= b[u] ) f[u][0][1] = (f[u][0][1] + p[i]) % Mod;
        if ( i <= b[u] ) f[u][1][1] = (f[u][1][1] + p[i]) % Mod;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) scanf("%lld", &b[i]);
    DFS(1, 0);
    printf("%lld\n", (f[1][1][0] + Mod) % Mod);
    return 0;
}
