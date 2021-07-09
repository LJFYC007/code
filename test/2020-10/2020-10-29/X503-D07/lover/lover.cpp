/***************************************************************
	File name: lover.cpp
	Author: ljfcnyali
	Create time: 2020年10月29日 星期四 08时29分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int T, n, a[maxn], prime[maxn], tot, p[110][70], l[110], f[110], g[110];
bool vis[maxn];

inline int Solve(int x, int n)
{
    int ans = 0, sum = 1;
    REP(i, 1, l[x]) { f[i] = sum * (prime[x] - 1); g[i] = sum; sum += p[x][i]; }

    int val = 0;
    for ( int i = l[x]; i >= 1; -- i )
    {
        int num = 0;
        while ( n - g[i] >= 0 && n > f[i - 1] ) { n -= g[i]; ++ num; }
        ans = ans * prime[x] + num;
        val += num * g[i];
    }
    if ( n ) ++ ans;
    return ans * prime[x];
}

signed main()
{
    freopen("lover.in", "r", stdin);
    freopen("lover.out", "w", stdout);
    scanf("%lld", &T); 
    REP(i, 2, 1000)
    {
        if ( !vis[i] ) prime[++ tot] = i;
        for ( int j = 1; j <= tot && i * prime[j] <= 1000; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) break ; 
        }
    }
    REP(i, 1, 100)    
    {
        p[i][0] = 1; int j = 0;
        while ( p[i][j] <= INF / prime[i] ) { ++ j; p[i][j] = p[i][j - 1] * prime[i]; }
        l[i] = j;
    }
    while ( T -- ) 
    {
        scanf("%lld", &n);         
        int ans = 1;
        REP(i, 1, n) scanf("%lld", &a[i]);
        REP(i, 1, n) ans = max(ans, Solve(i, a[i])); 
        printf("%lld\n", ans);
    }
    return 0;
}
