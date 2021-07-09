/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年06月27日 星期日 20时08分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int maxm = 10010;
const int Mod = 998244353;

int n, a[maxn], f[maxn][maxm], sum, ans, fac[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	REP(i, 1, n) { scanf("%lld", &a[i]); sum += a[i]; } 
	if ( sum & 1 ) { puts("0"); return 0; } 
	sum /= 2;
	f[0][0] = 1;
	REP(i, 1, n) for ( int j = sum; j >= a[i]; -- j ) for ( int k = n; k >= 1; -- k )
		f[k][j] = (f[k][j] + f[k - 1][j - a[i]]) % Mod;
	REP(i, 1, n) ans = (ans + f[i][sum] * fac[i] % Mod * fac[n - i]) % Mod;
	printf("%lld\n", ans);
    return 0;
}
