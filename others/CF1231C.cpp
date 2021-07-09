/***************************************************************
	File name: CF1231C.cpp
	Author: ljfcnyali
	Create time: 2019年10月28日 星期一 19时04分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 510;

int a[maxn][maxn], n, m;

inline bool Check()
{
    REP(i, 1, n)
        REP(j, 2, m) if ( a[i][j - 1] >= a[i][j] ) return false;
    REP(j, 1, m)
        REP(i, 2, n) if ( a[i - 1][j] >= a[i][j] ) return false;
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, m) scanf("%d", &a[i][j]);
    for ( int i = n - 1; i >= 2; -- i ) 
        for ( int j = m - 1; j >= 2; -- j ) 
            if ( !a[i][j] ) a[i][j] = min(a[i][j + 1], a[i + 1][j]) - 1;
    if ( !Check() ) { puts("-1"); return 0; }
    int ans = 0;
    REP(i, 1, n) REP(j, 1, m) ans += a[i][j];
    printf("%d\n", ans);
    return 0;
}
