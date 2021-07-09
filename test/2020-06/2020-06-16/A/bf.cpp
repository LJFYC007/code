/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月16日 星期二 08时39分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int T, n, a, ans, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    fac[0] = 1; REP(i, 1, maxn - 10) fac[i] = fac[i - 1] * i % Mod;
    scanf("%lld", &T);
    while ( T -- ) 
    {
        ans = 0; scanf("%lld%lld", &n, &a);
        if ( a >= n ) { puts("0"); continue ; }
        REP(i, 0, (1 << a) - 1)
        {
            int num = 0, ret = 1;
            REP(j, n - a + 1, n)
            {
                int pos = j - n + a - 1;
                if ( !((i >> pos) & 1) ) 
                {
                    ret = ret * (j - n + a - num) % Mod;
                    ++ num;
                }
            }
            ret = ret * power(a - num, n - a) % Mod;
            ret = ret * fac[a - num] % Mod;
            ans = (ans + ret * (num & 1 ? -1 : 1)) % Mod;
        }
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
