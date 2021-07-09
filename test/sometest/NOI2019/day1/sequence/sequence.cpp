/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2019年07月16日 星期二 09时39分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 110;

LL T, n, k, l, ans, a[maxn], b[maxn], sum[maxn];

inline void DFS(LL x, LL k1, LL k2, LL k3, LL s)
{
    if ( k1 > k || k2 > k ) return ;
    if ( sum[n] - sum[x - 1] + s <= ans ) return ;
    if ( n - x + 1 + k3 < l ) return ;
    if ( x == n + 1 )
    {
        if ( k1 == k && k2 == k && k3 >= l ) ans = max(ans, s); 
        return ; 
    }
    DFS(x + 1, k1 + 1, k2 + 1, k3 + 1, s + a[x] + b[x]);
    if ( a[x] > b[x] ) 
    {
        DFS(x + 1, k1 + 1, k2, k3, s + a[x]);
        DFS(x + 1, k1, k2 + 1, k3, s + b[x]);
    }
    else 
    {
        DFS(x + 1, k1, k2 + 1, k3, s + b[x]);
        DFS(x + 1, k1 + 1, k2, k3, s + a[x]);
    }
    DFS(x + 1, k1, k2, k3, s);
}

int main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        ans = 0; 
        scanf("%lld%lld%lld", &n, &k, &l);
        REP(i, 1, n) scanf("%lld", &a[i]);
        REP(i, 1, n) { scanf("%lld", &b[i]); sum[i] = sum[i - 1] + a[i] + b[i]; }
        DFS(1, 0, 0, 0, 0);
        printf("%lld\n", ans);
    }
    return 0;
}
