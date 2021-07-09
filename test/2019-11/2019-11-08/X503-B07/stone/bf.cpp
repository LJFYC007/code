/***************************************************************
	File name: stone.cpp
	Author: ljfcnyali
	Create time: 2019年11月08日 星期五 08时54分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;

int n, q, a[maxn], L, R, ans;

int main()
{
    freopen("stone.in", "r", stdin);
    freopen("stone.out", "w", stdout);
    scanf("%d%d", &n, &q);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(j, 1, q)
    {
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        REP(i, 1, n) if ( a[i] % x == y ) a[i] += z;
    }
    REP(i, 1, n) printf("%d ", a[i]); puts("");
    scanf("%d%d", &L, &R);
    REP(i, 1, n) if ( L <= a[i] && a[i] <= R ) ++ ans;
    printf("%d\n", ans);
    return 0;
}
