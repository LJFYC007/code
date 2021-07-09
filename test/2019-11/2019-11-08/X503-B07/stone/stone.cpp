/***************************************************************
	File name: stone.cpp
	Author: ljfcnyali
	Create time: 2019年11月08日 星期五 10时20分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 500010;

int n, m, a[maxn], x[maxn], y[maxn], z[maxn], L, R, ans;

int main()
{
    freopen("stone.in", "r", stdin);
    freopen("stone.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m) scanf("%d%d%d", &x[i], &y[i], &z[i]);
    scanf("%d%d", &L, &R);
    for ( int i = m; i >= 1; -- i ) 
        if ( z[i] == 1 ) 
        {
            if ( (L - 1) % x[i] == y[i] ) -- L;
            if ( R % x[i] == y[i] ) -- R;
        }
        else
        {
            if ( L % x[i] == y[i] ) ++ L;
            if ( (R + 1) % x[i] == y[i] ) ++ R;
        }
    REP(i, 1, n) if ( L <= a[i] && a[i] <= R ) ++ ans;
    printf("%d\n", ans);
    return 0;
}
