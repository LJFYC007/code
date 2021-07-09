/***************************************************************
	File name: LibreOJ_6485.cpp
	Author: ljfcnyali
	Create time: 2020年06月11日 星期四 21时08分36秒
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
const int Mod = 998244353;

int n, s, a[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get(int n, int k)
{
    int ret = power(3, (Mod - 1) / n);
    return power(ret, k);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T; scanf("%lld", &T);
    while ( T -- ) 
    {
        ans = 0;
        scanf("%lld%lld", &n, &s);        
        REP(i, 0, 3) scanf("%lld", &a[i]);
        REP(i, 0, 3)
        {
            int ret = 0;
            REP(j, 0, 3)
            {
                int x = Get(4, j);
                ret = (ret + power((s * x + 1) % Mod, n) * power(power(x, i), Mod - 2)) % Mod;
            }
            ans = (ans + ret * a[i]) % Mod;
        }
        ans = ans * power(4, Mod - 2) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
