/***************************************************************
    File name: C.cpp
    Author: ljfcnyali
    Create time: 2020年07月23日 星期四 09时38分08秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;
 
const int maxn = 1010;
 
int T, n, k, a[maxn];
bool f[maxn][maxn];
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C1.out", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        mem(f); scanf("%lld%lld", &n, &k);
        REP(i, 1, n) scanf("%lld", &a[i]);
        REP(i, 2, n) a[i] += a[i - 1];
        f[k][k] = 1;
        REP(len, 1, n) REP(i, 1, n - len + 1)
        {
            int j = i + len - 1;
            if ( !f[i][j] ) continue ;
            if ( j < n && a[j + 1] - a[i] <= 0 ) f[i][j + 1] = true;
            if ( i > 1 && a[j] - a[i - 1] <= 0 ) f[i - 1][j] = true;
        }
        if ( f[1][n] ) puts("Yes");
        else puts("No");
    }
    return 0;
}
