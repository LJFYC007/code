/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2020年07月22日 星期三 15时44分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define mp make_pair
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;
const int Mod = 1e9 + 7;

int n, m, k, cnt, Edge[maxn][5], fac[maxn], inv[maxn], h[200][100][2];
int dp[600][200][100][2], F[100][2], G[100][100][2];
struct data
{
    int f[3][3];
    bool operator < (const data &a) const { REP(i, 0, 2) REP(j, 0, 2) if ( f[i][j] != a.f[i][j] ) return f[i][j] < a.f[i][j]; return false; } 
} ;
struct node
{ 
    data f[2];
    bool operator < (const node &a) const { return mp(f[0], f[1]) < mp(a.f[0], a.f[1]); }
} g[maxn];
int f[100][maxn][130];
map<node, int> Map;
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }
inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }
inline int Find(int n, int m)
{
    if ( n < m ) return 0;
    int ret = 1;
    REP(i, n - m + 1, n) ret = ret * i % Mod;
    REP(i, 2, m) ret = ret * power(i, Mod - 2) % Mod;
    return ret;
}

inline bool Check(node x) { return x.f[1].f[0][0] >= k; }

inline data max(data a, data b)
{
    REP(i, 0, 2) REP(j, 0, 2) a.f[i][j] = max(a.f[i][j], b.f[i][j]);
    return a;
}

inline data Trans(data x, int y)
{
    data X;
    REP(i, 0, 2) REP(j, 0, 2) X.f[i][j] = -1;
    REP(i, 0, 2) REP(j, 0, 2) 
    {
        if ( x.f[i][j] == -1 ) continue ;
        if ( y - i - j <= 2 && y >= i + j ) X.f[j][y - i - j] = max(X.f[j][y - i - j], x.f[i][j] + y - i - j);
        if ( y >= i + j + 3 ) X.f[j][y - i - j - 3] = max(X.f[j][y - i - j - 3], x.f[i][j] + y - i - j - 2);
    }
    REP(i, 0, 2) REP(j, 0, 2) X.f[i][j] = min(X.f[i][j], k);
    return X;
}

inline node Trans(node x, int y)
{
    node X; X.f[0] = Trans(x.f[0], y); X.f[1] = Trans(x.f[1], y); 
    if ( y >= 2 ) X.f[1] = max(X.f[1], Trans(x.f[0], y - 2)); 
    return X;
}

inline int DFS(node x)
{
    if ( Map.count(x) ) return Map[x]; 
    g[++ cnt] = x; Map[x] = cnt; int now = cnt; 
    if ( !Check(x) ) REP(i, 1, 4) Edge[now][i] = DFS(Trans(x, i)); 
    else vis[now] = true;
    return now;
}

signed main()
{
    freopen("majsoul.in", "r", stdin);
    freopen("majsoul.out", "w", stdout);
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld%lld%lld", &m, &n, &k);
    REP(i, 0, 2) REP(j, 0, 2) g[1].f[0].f[i][j] = g[1].f[1].f[i][j] = -1;
    g[1].f[0].f[0][0] = 0; DFS(g[1]);

    f[0][1][0] = 1;
    REP(i, 1, 3 * k + 2) REP(j, 1, cnt) REP(x, 0, 3 * k + 2)
    {
        if ( !f[i - 1][j][x] ) continue ;
        REP(o, 1, 4)
        {
            int t = Edge[j][o]; if ( !t ) continue ;
            f[i][t][x + o] = (f[i][t][x + o] + f[i - 1][j][x] * C(4, o)) % Mod;
        }
    }
    REP(i, 1, 3 * k + 2) REP(j, 1, cnt) 
    {
        int t = g[j].f[0].f[0][0];
        if ( t != -1 ) h[i][t][0] = (h[i][t][0] + f[i][j][3 * t]) % Mod;
        t = g[j].f[1].f[0][0];
        if ( t != -1 ) h[i][t][1] = (h[i][t][1] + f[i][j][3 * t + 2]) % Mod;
    }

    dp[0][0][0][0] = 1;
    REP(i, 0, 3 * k + 2) REP(j, 0, 3 * k + 2) REP(t, 0, k) 
    {
        if ( !dp[i][j][t][0] && !dp[i][j][t][1] ) continue ;
        REP(x, 1, 3 * k + 2) REP(y, 0, k)
        {
            dp[i + x][j + 1][t + y][0] = (dp[i + x][j + 1][t + y][0] + dp[i][j][t][0] * h[x][y][0]) % Mod;
            dp[i + x][j + 1][t + y][1] = (dp[i + x][j + 1][t + y][1] + dp[i][j][t][0] * h[x][y][1]) % Mod;
            dp[i + x][j + 1][t + y][1] = (dp[i + x][j + 1][t + y][1] + dp[i][j][t][1] * h[x][y][0]) % Mod;
        }
    }

    REP(i, 1, 3 * k + 2) REP(j, 1, 3 * k + 2) REP(o, 0, k) REP(op, 0, 1)
        F[o][op] = (F[o][op] + Find(m - i + 1, j) * dp[i][j][o][op]) % Mod;
    G[0][0][0] = 1;
    REP(i, 0, k) REP(j, 0, k) REP(o, 0, k)
    {
        if ( o ) G[i + 1][j + o][0] = (G[i + 1][j + o][0] + G[i][j][0] * F[o][0]) % Mod;
        if ( o ) G[i + 1][j + o][1] = (G[i + 1][j + o][1] + G[i][j][1] * F[o][0]) % Mod;
        G[i + 1][j + o][1] = (G[i + 1][j + o][1] + G[i][j][0] * F[o][1]) % Mod;
    }
    int ans = 0;
    REP(i, 0, k + 1) ans = (ans + G[i][k][1] * Find(n, i)) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
