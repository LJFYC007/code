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
typedef long long LL;
#define int long long

const int maxn = 1e5 + 10;
const int Mod = 998244353;
int n, m, len;
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int T; scanf("%lld", &T);
	while ( T -- ) 
	{
		scanf("%d", &len);	scanf("%s", s + 1); n = m = 0;
		int ans = 1;
		for ( int i = 1, j; i <= len; i = j )
		{
			j = i + 1;
			if ( s[i] == '0' ) { ++ n; continue ; } 
			while ( j <= len && s[j] == '1' ) ++ j;
			m += (j - i) / 2;
		}
		cerr << n << " " << m << endl;
		REP(i, 1, n + m) ans = ans * i % Mod;
		REP(i, 1, n) ans = ans * power(i, Mod - 2) % Mod;
		REP(i, 1, m) ans = ans * power(i, Mod - 2) % Mod;
		//ans = ans * power(len - n - m, Mod - 2) % Mod;
		printf("%lld\n", ans);
	}

    return 0;
}
