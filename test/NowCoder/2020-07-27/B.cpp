/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年07月27日 星期一 13时05分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e7 + 10;
const int Mod = 1e9 + 7;
const int inv2 = (Mod + 1) / 2;

int n, f[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10;
    int sum = 1, ret = 1;
    f[0] = 1;
    REP(i, 1, n)
    {
        sum = sum * 2 % Mod;
        ret = ret * inv2 % Mod;
        f[i] = (f[i - 1] * (sum - 1) % Mod) * ret % Mod;
    }
    REP(i, 1, n) f[i] = (f[i] + Mod) % Mod;
    REP(i, 2, n) f[i] = f[i] ^ f[i - 1];
    int T; scanf("%lld", &T);
    while ( T -- ) { scanf("%lld", &n); printf("%lld\n", f[n]); }
    return 0;
}
