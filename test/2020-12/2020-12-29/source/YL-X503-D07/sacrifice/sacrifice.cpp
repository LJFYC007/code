/***************************************************************
	File name: sacrifice.cpp
	Author: ljfcnyali
	Create time: 2020年12月29日 星期二 19时53分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
#define x first
#define y second 
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 998244353;
const int INF = 1e18;

int n, m, q, f[maxn], RealAns[2][maxn]; 
pii a[maxn];
struct node 
{
    int ans;
} ;

inline int Get(int l, int r)
{
    if ( l > r ) return 0; if ( l == r ) return f[l];
    int Min = INF, pos = 0;
    REP(i, l, r) if ( f[i] < Min ) { Min = f[i]; pos = i; }
    int ret = (Get(l, pos - 1) + Get(pos + 1, r)) % Mod;
    ret = (ret + f[pos] * (pos - l + 1) * (r - pos + 1)) % Mod;
    return ret;
}

inline void Solve(int op)
{
    vector<int> p[maxn]; mem(f);
    REP(i, 1, q) p[a[i].x].push_back(a[i].y);
    REP(i, 1, n)
    {
        REP(j, 1, m) ++ f[j]; for ( auto it : p[i] ) f[it] = 0;
        RealAns[op][i] = Get(1, m);
    }
}

signed main()
{
    freopen("sacrifice.in", "r", stdin);
    freopen("sacrifice.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &q); REP(i, 1, q) scanf("%lld%lld", &a[i].x, &a[i].y); 
    int ans = 0, sum;
    Solve(0); REP(i, 1, q) a[i].x = n - a[i].x + 1; Solve(1); REP(i, 1, q) a[i].x = n - a[i].x + 1;
    sum = 0; REP(i, 3, n) { sum = (sum + RealAns[0][i - 2]) % Mod; ans = (ans + RealAns[1][n - i + 1] * sum) % Mod; }
    swap(n, m); REP(i, 1, q) swap(a[i].x, a[i].y);
    Solve(0); REP(i, 1, q) a[i].x = n - a[i].x + 1; Solve(1); REP(i, 1, q) a[i].x = n - a[i].x + 1;
    sum = 0; REP(i, 3, n) { sum = (sum + RealAns[0][i - 2]) % Mod; ans = (ans + RealAns[1][n - i + 1] * sum) % Mod; }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
