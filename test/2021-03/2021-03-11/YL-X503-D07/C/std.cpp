#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
 
const int maxn = 2e5 + 10;
 
int n, a[maxn], q, f[maxn][2];
 
inline void Solve()
{
    if ( (n - 1) & 1 ) { f[n - 1][0] = max(a[n - 1], a[n]); f[n - 1][1] = a[n - 1] + a[n]; } 
    else { f[n - 1][0] = 0; f[n - 1][1] = min(a[n - 1], a[n]); }
    for ( int i = n - 2; i >= 1; -- i ) 
        if ( i & 1 ) 
        {
            f[i][1] = f[i + 1][1] + a[i];
            f[i][0] = max(f[i + 1][0] + a[i], f[i + 1][1]);
        }
        else
        {
            f[i][0] = f[i + 1][0];
            f[i][1] = min(f[i + 1][1], f[i + 1][0] + a[i]);
        }
    printf("%lld\n", f[1][1]);
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]); Solve();
    scanf("%lld", &q);
    while ( q -- ) 
    {
        int p, d; scanf("%lld%lld", &p, &d); a[p] -= d;
        Solve();
    }
    return 0;
}
