/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 14时10分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 998244353;
const int maxn = 1e5 + 10;
const int N = 1e5 + 9;

int T, inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int D(int n, int k)
{
    int ret = 1, ans = 1;
    REP(i, 1, k)
    {
        ret = ret * (n - i + 1) % Mod * inv[i] % Mod;
        ans = (ans + ret) % Mod;
    }
    return ans;
}

signed main()
{
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    scanf("%lld", &T);
    REP(i, 1, N) inv[i] = power(i, Mod - 2);
    while ( T -- ) 
    {
        int opt, l, r, k, n;
        scanf("%lld", &opt);
        if ( opt == 1 ) 
        {
            scanf("%lld%lld", &n, &k); printf("%lld\n", D(n, k));
            continue ;
        }
        scanf("%lld%lld%lld", &l, &r, &k);
        int ans = (D(r + 1, k + 1) - D(l, k + 1) + Mod) % Mod;
        printf("%lld\n", ans);
    }
    return 0;
}
