/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 19时56分06秒
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

int n, ans, f[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) for ( int j = i; j <= n; j += i ) ++ f[j];
	REP(i, 1, n) f[i] += f[i - 1];
	REP(i, 1, n) ans += f[n / i];
	printf("%lld\n", ans);
    return 0;
}
