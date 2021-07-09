/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年10月31日 星期六 19时58分45秒
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

signed main()
{
    int n, m, k; cin >> n >> m >> k;
    int ans = (n * (n + 1) / 2) % Mod;
    ans = (ans * (((m + 1) * m / 2) % Mod)) % Mod;
    ans = (ans * (((k + 1) * k / 2) % Mod)) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
