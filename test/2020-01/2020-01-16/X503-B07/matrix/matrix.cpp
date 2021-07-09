/***************************************************************
	File name: matrix.cpp
	Author: ljfcnyali
	Create time: 2020年01月16日 星期四 10时55分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 10;
const int Mod = 998244353;

int a[maxn][maxn], n, m, ans;
map<int, bool> Map;

inline int Solve()
{
    int ret = 0;
    REP(i, 1, n) 
    {
        REP(j, 1, m) if ( a[i][j] ) { ret = ret * 10 + j; goto NEXT1; }
        ret = ret * 10 + m + 1;
NEXT1 : ; 
    }
    REP(i, 1, m)
    {
        REP(j, 1, n) if ( a[j][i] ) { ret = ret * 10 + j; goto NEXT2; }
        ret = ret * 10 + n + 1;
NEXT2 : ; 
    }
    REP(i, 1, m)
    {
        for ( int j = n; j >= 1; -- j ) if ( a[j][i] ) { ret = ret * 10 + j; goto NEXT3; }
        ret = ret * 10;
NEXT3 : ; 
    }
    return ret;
}

inline void DFS(int x, int y)
{
    if ( y == m + 1 ) { DFS(x + 1, 1); return ; }
    if ( x == n + 1 ) 
    {
        int t = Solve();
        if ( !Map.count(t) ) { Map[t] = true; ++ ans; }
        return ;
    }
    a[x][y] = true;
    DFS(x, y + 1);
    a[x][y] = false;
    DFS(x, y + 1);
}

inline int power(int a, int b)
{
    int r = 1; 
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    if ( m == 1 ) { printf("%lld\n", power(2, n)); return 0; }
    DFS(1, 1); 
    printf("%lld\n", ans);
    return 0;
}
