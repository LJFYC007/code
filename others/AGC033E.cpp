/***************************************************************
	File name: AGC033E.cpp
	Author: ljfcnyali
	Create time: 2021年02月24日 星期三 20时17分32秒
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
const int Mod = 1e9 + 7;

int n, m, k, f[maxn], ans;
char s[maxn];

inline int Solve()
{
	if ( n == 1 || n == 2 ) { printf("%d\n", n == 1 ? 1 : 3); return 0; } 
	f[0] = 1; f[1] = 2; REP(i, 2, n) f[i] = (f[i - 1] + f[i - 2]) % Mod;	
	ans = (f[n - 1] + f[n - 3]) % Mod;
	printf("%lld\n", ans); return 0; 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m); scanf("%s", s + 1); k = m + 1;
	if ( s[1] == 'B' ) { REP(i, 1, m) s[i] = s[i] == 'B' ? 'R' : 'B'; }
	bool flag = false; REP(i, 1, m) if ( s[i] != 'R' ) flag = true;
	if ( !flag ) return Solve();
	for ( int i = 1, j; i <= m; i = j + 1 ) 
	{
		j = i; if ( s[i] == 'B' ) continue ;
		while ( s[j + 1] == 'R' ) ++ j;
		if ( i == 1 ) k = min(k, (j - i + 1) | 1);
		else if ( ((j - i + 1) & 1) && j != m ) k = min(k, j - i + 1);
	}
	int sum0 = 1, sum1 = 0; f[0] = 1; 
	REP(i, 1, n) 
	{
		swap(sum0, sum1); f[i] = sum0;
		sum0 = (sum0 + f[i]) % Mod;
		if ( k + 1 <= i ) sum0 = (sum0 - f[i - (k + 1)]) % Mod;
	}
	for ( int i = 2; i <= n; i += 2 ) if ( i - 1 <= k ) ans = (ans + f[n - i] * i) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
