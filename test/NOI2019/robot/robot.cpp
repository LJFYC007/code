/***************************************************************
	File name: LibreOJ_3157.cpp
	Author: ljfcnyali
	Create time: 2021年02月18日 星期四 14时35分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 310;
const int Mod = 1e9 + 7;

int n, a[maxn], b[maxn], f[3010][maxn], Stack[maxn * 2], tot, L, R, fac[maxn], inv[maxn], num, id[maxn][maxn];
bool vis[3010];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get(int t, int x)
{
	int ret = 1, ans = 0;
	if ( x <= n ) return f[t][x];
	REP(i, 0, n) ret = ret * (x - i) % Mod;
	REP(i, 0, n)
	{
		int sum = ret * power(x - i, Mod - 2) % Mod;
		sum = sum * inv[i] % Mod;
		sum = sum * inv[n - i] % Mod;
		ans = (ans + sum * f[t][i]) % Mod;
	}
	return ans;
}

inline void Solve(int l, int r)
{
	if ( vis[id[l][r]] || l > r ) return ; id[l][r] = ++ num;
	int x = num; REP(i, 1, n) f[x][i] = 0; vis[x] = true;
	REP(i, (l + r - 1) / 2, (l + r + 2) / 2)
	{
		if ( i < l || i > r ) continue ;
		Solve(l, i - 1); Solve(i + 1, r);
		int ls = id[l][i - 1], rs = id[i + 1][r];
		if ( L >= a[i] && R <= b[i] ) REP(j, 1, n) f[x][j] = (f[x][j] + f[ls][j] * f[rs][j - 1]) % Mod;
	}
	REP(i, 1, n) f[x][i] = (f[x][i] + f[x][i - 1]) % Mod;
}

signed main()
{
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);
	scanf("%lld", &n); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, n) { scanf("%lld%lld", &a[i], &b[i]); Stack[++ tot] = a[i]; Stack[++ tot] = b[i] + 1; }
	sort(Stack + 1, Stack + tot + 1);
	REP(i, 0, n) f[0][i] = 1;
	REP(i, 1, tot - 1)
	{
		L = Stack[i]; R = Stack[i + 1] - 1;
		num = 0; Solve(1, n);
		REP(j, 1, num) { vis[j] = false; f[j][0] = Get(j, R - L + 1); }
	}
	printf("%lld\n", (f[id[1][n]][0] + Mod) % Mod);
    return 0;
}
