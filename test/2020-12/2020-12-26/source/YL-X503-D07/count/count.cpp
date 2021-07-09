/***************************************************************
	File name: count.cpp
	Author: ljfcnyali
	Create time: 2020年12月26日 星期六 08时33分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 61;
const int Mod = 998244353;

int n, m, ans;
vector<int> a[maxn][maxn];
int f[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline pii operator + (pii a, pii b) { return pii((a.x + b.x) % Mod, (a.y + b.y) % Mod); }
inline pii operator - (pii a, pii b) { return pii((a.x - b.x) % Mod, (a.y - b.y) % Mod); }
inline pii operator * (pii a, pii b) { return pii((a.x * b.x + a.y * b.y) % Mod, (a.x * b.y + a.y * b.x) % Mod); }
inline pii operator / (pii x, pii y) 
{ 
    int a = x.first, b = x.second, c = y.first, d = y.second;
    int t = (a * c - b * d) % Mod;
    int n = t * power((c * c - d * d) % Mod, Mod - 2) % Mod;
    return pii(n, (b - n * d) % Mod * power(c, Mod - 2) % Mod);
}

inline int Solve()
{
    int ret = 1;
    REP(i, 1, n - 1)
    {
        int pos = -1;
        REP(j, i, n - 1) if ( f[j][i] ) { pos = j; break ; } 
        if ( pos == -1 ) return 0; 
        if ( pos != i ) ret = -ret;
        REP(j, 1, n - 1) swap(f[i][j], f[pos][j]);
        REP(j, 1, n - 1) if ( i != j ) 
        {
            int tmp = f[j][i] * power(f[i][i], Mod - 2) % Mod;
            REP(k, 1, n - 1) f[j][k] = (f[j][k] - tmp * f[i][k]) % Mod;
        }
    }
    REP(i, 1, n - 1) ret = ret * f[i][i] % Mod;
    return ret;
}

signed main()
{
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) 
    { 
        int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); 
        a[u][v].push_back(w); a[v][u].push_back(w); 
    }
    REP(i, 0, 7)
    {
        mem(f); 
        REP(x, 1, n) REP(y, 1, n) for ( auto it : a[x][y] ) { -- f[x][y]; ++ f[x][x]; }
        ans = (ans + (1 << i) * Solve()) % Mod;
        mem(f); 
        REP(x, 1, n) REP(y, 1, n) for ( auto it : a[x][y] ) 
            if ( (it >> i) & 1 ) { ++ f[x][y]; -- f[x][x]; }
            else { -- f[x][y]; ++ f[x][x]; }
        ans = (ans - (1 << i) * Solve()) % Mod;
    } 
    printf("%lld\n", (ans * power(2, Mod - 2) % Mod + Mod) % Mod);
    return 0;
}
