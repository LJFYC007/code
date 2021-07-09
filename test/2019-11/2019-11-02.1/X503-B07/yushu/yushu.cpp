/***************************************************************
	File name: yushu.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 14时20分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 1e9 + 7;
const int inv = 500000004;

int n, ans;

signed main()
{
    freopen("yushu.in", "r", stdin);
    freopen("yushu.out", "w", stdout);
    scanf("%lld", &n);
    for ( int i = 1, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        int x = n % i, y = n % j;
        int sum = (x + y) % Mod, sum2 = (j - i + 1) % Mod;
        ans = (ans + (sum * sum2 % Mod) * inv) % Mod;
    }
    printf("%lld\n", ans);
    return 0;
}
