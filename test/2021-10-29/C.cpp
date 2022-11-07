/***************************************************************
	File name: HaHa
	Author: ljfcnyali
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

int m, l, r, x, f[maxn];
char s[maxn];

inline int calc(int x) { return (x * (x + 1) / 2) % Mod; }

signed main()
{
	scanf("%lld%lld%lld%lld", &m, &l, &r, &x);
	scanf("%s", s + 1);
	int n = m * x;
	REP(i, 1, m) if ( s[i] == '1' ) ++ n;

	f[0] = 1;
	REP(i, 1, m) f[i] = f[i - 1] * 233 % Mod;
	
	if ( l == m && r == m ) 
	{
		int len = n - m + 1;
		int ans = len * (len + 1) / 2;
		ans %= Mod;
		REP(i, 1, m) ans = ans * 233 % Mod;
		printf("%lld\n", (ans + Mod) % Mod);
		return 0;
	}
	if ( x == 1 && m == n ) 
	{
		int ans = 0;
		REP(i, l, r)
		{
			if ( i == 0 ) 
			{
				ans ^= f[i] * calc(n) % Mod;
				continue ; 
			}
			ans ^= f[i] * ((n - i) / 2 + 1) % Mod * (n - i - (n - i) / 2 + 1) % Mod;
		}
		printf("%lld\n", ans);
		return 0;
	}
	if ( l == 0 && r == 1 ) 
	{
			
	}
    return 0;
}
