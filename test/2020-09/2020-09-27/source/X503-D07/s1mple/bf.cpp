/***************************************************************
	File name: s1mple.cpp
	Author: ljfcnyali
	Create time: 2020年09月27日 星期日 11时02分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 20;

int n, q, a[maxn][maxn], ans, B[1 << 20], fac[maxn], A[1 << 20];
int f[1 << 20][maxn], Num[1 << 20], cnt;
vector<int> p;
map<vector<int>, int> Map;
bool vis[maxn];

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline void Solve()
{
    int now = 0;
    for ( auto i : p ) { REP(j, 1, i - 1) vis[++ now] = true; vis[++ now] = false; }
    REP(i, 0, (1 << n) - 1) REP(j, 1, n) f[i][j] = 0;
    REP(i, 1, n) f[1 << i - 1][i] = 1;
    REP(i, 1, (1 << n) - 1) REP(j, 1, n)
    {
        if ( !f[i][j] ) continue ; 
        int num = Num[i];
        REP(k, 1, n) 
        {
            if ( (i >> k - 1) & 1 ) continue ;
            if ( !vis[num] || a[j][k] == 1 ) f[i + (1 << k - 1)][k] += f[i][j];
        }
    }
    int ret = 0; REP(i, 1, n) ret += f[(1 << n) - 1][i];
    for ( auto i : p ) printf("%d ", i); printf("%d\n", ret);
    Map[p] = ret;
}

inline void DFS(int lst, int sum)
{
    if ( sum == 0 ) { Solve(); return ; }
    REP(i, lst, sum) { p.push_back(i); DFS(i, sum - i); p.pop_back(); }
}

signed main()
{
    freopen("s1mple.in", "r", stdin);
    freopen("s1mple.out", "w", stdout);
    fac[0] = 1; REP(i, 1, 17) fac[i] = fac[i - 1] * i;
    scanf("%lld", &n);
    REP(i, 1, n) REP(j, 1, n) scanf("%1lld", &a[i][j]);

    REP(i, 0, (1 << n) - 1) REP(j, 1, n) if ( (i >> j - 1) & 1 ) ++ Num[i];
    DFS(1, n);
    REP(i, 0, (1 << n - 1) - 1)
    {
        p.clear(); int sum = 1;
        REP(j, 1, n - 1)
            if ( !((i >> j - 1) & 1) ) ++ sum;
            else { p.push_back(sum); sum = 1; }
        p.push_back(sum); sort(p.begin(), p.end()); 
        B[i] = Map[p];
    }
    REP(i, 0, (1 << n - 1) - 1) for ( int j = i; ; j = (j - 1) & i )
    {
        A[i] += B[j] * sgn(Num[i] - Num[j]);
        if ( !j ) break ; 
    }

    scanf("%lld", &q);
    while ( q -- ) 
    {
        int x = 0, y = 0;
        REP(i, 1, n - 1) { scanf("%1lld", &x); y = y * 2 + x; }
        y = (1 << n - 1) - 1 - y;
        printf("%lld\n", A[y]);
    }
    return 0;
}
