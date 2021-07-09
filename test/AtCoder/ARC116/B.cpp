/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月28日 星期日 20时04分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int n, a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);	
	sort(a + 1, a + n + 1);
	int sum = 0, ans = 0;
	for ( int i = n; i >= 1; -- i ) 
	{
		ans = (ans + (sum + a[i]) * a[i]) % Mod;
		sum = (sum * 2 + a[i]) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
