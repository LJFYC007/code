/***************************************************************
	File name: ARC089F.cpp
	Author: ljfcnyali
	Create time: 2021年06月17日 星期四 09时58分14秒
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
const int maxn = 71;
const int maxm = 210;

int n, m, fac[maxm], inv[maxm], a[maxn], id[maxn], f[maxn][maxn][maxn], ans;
char s[maxn], t[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return (n < m || n < 0) ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = maxm - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld%lld", &n, &m); scanf("%s", s + 1);
	REP(x1, 0, m) REP(x2, 0, m - x1)
	{
		int sum = 0;
		REP(i, 1, m) t[i] = s[i];		
		REP(i, 1, x1 + x2) 
		{
			bool flag = false;
			REP(j, 1, m) if ( t[j] == 'r' ) 
			{ 
				if ( i > x1 ) flag = true;
				else REP(k, j + 1, m) if ( t[k] == 'b' ) { t[k] = '1'; flag = true; id[i] = k; break ; }
				t[j] = '0'; break ; 
			}
			if ( !flag ) goto Next;
		}
		REP(i, 1, x1) { a[i] = 0; REP(j, id[i], m) if ( t[j] != '0' ) ++ a[i]; }
		reverse(a + 1, a + x1 + 1);

		mem(f); f[0][0][0] = 1;
		REP(i, 0, x1) REP(j, 0, m) REP(k, 0, m) if ( f[i][j][k] ) 
			REP(t, k + 1, m) REP(l, 1, x1 - i) 
			{
				if ( a[i + l] < j + l * t ) break ; 
				f[i + l][j + l * t][t] = (f[i + l][j + l * t][t] + f[i][j][k] * C(i + l, l)) % Mod;
			}

		REP(j, 0, m) REP(k, 0, m)
		{
			int A = 2 * (j + x2) - 1, B = 2 * x1 + 2;
			sum = (sum + f[x1][j][k] * C(n + B - 1, A + B - 1)) % Mod;
		}
		ans = (ans + sum * C(x1 + x2, x2)) % Mod;
Next : ; 
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
