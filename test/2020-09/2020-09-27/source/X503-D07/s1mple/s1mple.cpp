/***************************************************************
	File name: s1mple.cpp
	Author: ljfcnyali
	Create time: 1818年09月27日 星期日 11时02分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 18;

int n, q, a[maxn][maxn], ans, B[1 << 18], A[1 << 18];
int f[1 << 18][maxn], Num[1 << 18], F[1 << 18];
vector<int> p, g[maxn];
int t[1 << 18];
map<vector<int>, int> Map;

inline int sgn(int x) { return x & 1 ? -1 : 1; }

inline void FWT(vector<int> &f, int n, int inv)
{
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
        for ( int i = 0; i < n; i += (Mid << 1) )
            for ( int j = 0; j < Mid; ++ j ) f[i + j + Mid] += f[i + j] * inv;
}

inline void FWT1(int n, int inv)
{
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
        for ( int i = 0; i < n; i += (Mid << 1) )
            for ( int j = 0; j < Mid; ++ j ) t[i + j + Mid] += t[i + j] * inv;
}

inline void Solve()
{
    REP(i, 0, (1 << n) - 1) 
    {
        t[i] = 1;
        for ( auto j : p ) t[i] *= g[j][i];
    }
    FWT1(1 << n, -1); Map[p] = t[(1 << n) - 1];
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
    scanf("%lld", &n);
    REP(i, 1, n) REP(j, 1, n) scanf("%1lld", &a[i][j]);
    REP(i, 1, n) f[1 << i - 1][i] = 1;
    REP(i, 1, (1 << n) - 1) REP(j, 1, n)
    {
        if ( !f[i][j] ) continue ;
        F[i] += f[i][j];
        REP(k, 1, n) 
        {
            if ( (i >> k - 1) & 1 ) continue ;
            if ( a[j][k] ) f[i + (1 << k - 1)][k] += f[i][j];
        }
    }
    REP(i, 0, (1 << n) - 1) REP(j, 1, n) if ( (i >> j - 1) & 1 ) ++ Num[i];
    REP(i, 0, n) 
    {
        g[i].resize(1 << n); 
        REP(j, 0, (1 << n) - 1) if ( Num[j] == i ) g[i][j] = F[j]; 
        FWT(g[i], 1 << n, 1);
    }

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
