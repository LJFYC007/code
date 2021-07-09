/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2020年09月10日 星期四 22时24分59秒
***************************************************************/
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;
const int Mod = 998244353;

int type, n, m, k, q, M, num[maxn], fa[maxn], ans, c[maxn], fac[maxn], inv[maxn], size[maxn], p[11];
int anc[maxn][19], dis[maxn], val1[maxn][11], val2[maxn][11], val3[maxn][11], s[maxn], d[11][11], Pos[maxn];
bool leaf[maxn];
vector<int> f1[maxn][11], f2[maxn][11], Edge[maxn], val4[maxn][11];

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }
inline int sgn(int x) { return x & 1 ? -1 : 1; }
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline vector<int> operator - (vector<int> a, vector<int> b) { REP(i, 0, 10) a[i] = (a[i] - b[i]) % Mod; return a; }

inline int Get(vector<int> a, int x) 
{ 
    int ret = 0, sum = 1; 
    REP(i, 0, a.size() - 1) { ret = (ret + a[i] * sum) % Mod; sum = sum * x % Mod; }
    return ret; 
}

inline vector<int> Modify(vector<int> f, int w)
{
    if ( !w ) return f; vector<int> g; g.resize(f.size());
    REP(i, 0, f.size() - 1) REP(j, 0, i) g[j] = (g[j] + (f[i] * d[i][j] % Mod) * p[i - j]) % Mod;
    return g;
}

inline void DFS1(int u) 
{ 
    int sum = 0; REP(i, 0, 10) f1[u][i].resize(i + 1);
    if ( !Edge[u].size() ) size[u] = 1; s[u] = 1;
    for ( auto v : Edge[u] ) 
    { 
        dis[v] = dis[u] + 1; anc[v][0] = u;
        p[0] = 1; REP(i, 1, 10) p[i] = p[i - 1] * sum % Mod;
        REP(i, 0, 10) 
        {
            val1[v][i] = (val1[u][i] + val3[u][i]) % Mod;
            f1[v][i] = Modify(f1[u][i], sum); ++ f1[v][i][i];
        }
        DFS1(v); s[u] += s[v]; size[u] += size[v]; sum += size[v];
        REP(i, 0, 10) val3[u][i] = (val3[u][i] + val3[v][i]) % Mod;
    } 
    REP(i, 0, 10) val3[u][i] = (val3[u][i] + power(size[u], i)) % Mod;
    REP(j, 0, 10) 
    {
        val4[u][j].resize(Edge[u].size());
        for ( int i = 0; i < Edge[u].size(); ++ i ) 
            val4[u][j][i] = ((i >= 1 ? val4[u][j][i - 1] : 0) + val3[Edge[u][i]][j]) % Mod;
    }
}

inline void DFS2(int u) 
{ 
    int sum = 0; REP(i, 0, 10) { val3[u][i] = 0; f2[u][i].resize(i + 1); }
    for ( int i = (int)Edge[u].size() - 1; i >= 0; -- i ) 
    { 
        int v = Edge[u][i];
        p[0] = 1; REP(i, 1, 10) p[i] = p[i - 1] * sum % Mod;
        REP(i, 0, 10) 
        {
            val2[v][i] = (val2[u][i] + val3[u][i]) % Mod;
            f2[v][i] = Modify(f2[u][i], sum); ++ f2[v][i][i];
        }
        DFS2(v); sum += size[v];
        REP(i, 0, 10) val3[u][i] = (val3[u][i] + val3[v][i]) % Mod;
    } 
    REP(i, 0, 10) val3[u][i] = (val3[u][i] + power(size[u], i)) % Mod;
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
    if ( x == y ) return x;
    for ( int i = 18; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; }
    return anc[x][0];
}

inline int Find(int x, int y, int op) 
{ 
    for ( int i = 18; i >= 0; -- i ) 
        if ( dis[anc[x][i]] > dis[y] ) { x = anc[x][i]; M += op * (1 << i); }
    return x; 
}

inline void Solve1(int l, int r, int x)
{
    REP(i, 0, k)
    {
        ans = (ans + c[i] * (val1[r][i] - val1[l][i])) % Mod;
        ans = (ans + c[i] * (Get(f1[r][i], leaf[r]) - Get(f1[l][i], x))) % Mod;
    }
}

inline void Solve2(int l, int r, int x)
{
    int sum = 1;
    REP(i, 0, k)
    {
        ans = (ans + c[i] * (val2[r][i] - val2[l][i])) % Mod;
        ans = (ans + c[i] * (val3[r][i] - sum)) % Mod; sum = sum * size[r] % Mod;
        ans = (ans + c[i] * (Get(f2[r][i], num[r + s[r] - 1] - num[r - 1]) - Get(f2[l][i], x))) % Mod;
    }
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    fac[0] = inv[0] = 1; REP(i, 1, 10) fac[i] = fac[i - 1] * i % Mod;
    inv[10] = power(fac[10], Mod - 2); for ( int i = 9; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 0, 10) REP(j, 0, 10) d[i][j] = C(i, j);

    scanf("%lld%lld%lld", &type, &n, &q);
    REP(i, 1, n) leaf[i] = true;
    REP(i, 2, n) { scanf("%lld", &fa[i]); Edge[fa[i]].push_back(i); leaf[fa[i]] = 0; Pos[i] = Edge[fa[i]].size() - 1; }
    REP(i, 1, n) num[i] = leaf[i] + num[i - 1];
    dis[1] = 1; DFS1(1); DFS2(1); REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];

    while ( q -- ) 
    {
        int l, r; scanf("%lld%lld%lld", &l, &r, &k);
        l ^= type * ans; r ^= type * ans; ans = M = 0;
        REP(i, 0, k) c[i] = 0; c[k] = 1; m = num[r] - num[l - 1];
        if ( !m ) { ans = 0; printf("%lld\n", ans); continue ; }
        REP(i, 0, k) c[k - i] = (c[k - i] + sgn(k - i) * d[k][i] * power(m, i)) % Mod;

        int Lca = LCA(l, r);
        if ( l == Lca ) { Solve1(l, r, m); ans = (r - l - power(power(m, Mod - 2), k) * ans) % Mod; }
        else 
        {
            int x = Find(l, Lca, 1), y = Find(r, Lca, 0);
            int numx = num[x + s[x] - 1] - num[l - 1], numy = num[r] - num[y - 1];
            Solve1(y, r, numy); Solve2(x, l, numx);
            REP(i, 0, k) ans = (ans + c[i] * (power(numx, i) + power(numy, i))) % Mod;
            REP(i, 0, k)
                ans = (ans + c[i] * (val4[Lca][i][Pos[y] - 1] - val4[Lca][i][Pos[x]])) % Mod;
            ans = (r - l + M + 1 - power(power(m, Mod - 2), k) * ans) % Mod;
        }
        ans = (ans + Mod) % Mod;
        printf("%lld\n", ans);
    }
    return 0;
}
