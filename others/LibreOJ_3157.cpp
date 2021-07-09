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

int n, a[maxn], b[maxn], Stack[maxn * 2], tot, L, R, fac[maxn], inv[maxn], num, id[maxn][maxn];
int pre[maxn], suf[maxn], g[3010], ex1[maxn], ex2[maxn], iinv[maxn];
bool vis[3010];
vector<int> f[3010];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline vector<int> DFT(vector<int> a, int n, int op)
{
	a.resize(n); vector<int> b; b.resize(n);	
	if ( op == 1 ) REP(i, 0, n - 1) REP(j, 0, i) b[i] = (b[i] + a[j] * ex1[i - j]) % Mod;
	else		   REP(i, 0, n - 1) REP(j, 0, i) b[i] = (b[i] + a[j] * ex2[i - j]) % Mod; 
	return b;
}
inline vector<int> up(vector<int> a)
{
	int n = a.size();
	REP(i, 1, n - 1) a[i - 1] = (a[i - 1] + a[i] * i) % Mod;
	return a;
}
inline vector<int> down(vector<int> a)
{
	int n = a.size();
	for ( int i = n - 1; i >= 1; -- i ) a[i - 1] = (a[i - 1] - a[i] * i) % Mod;
	return a;
}
vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size() + b.size() - 1;
	a = DFT(a, n, 1); b = DFT(b, n, 1);
	REP(i, 0, n - 1) a[i] = a[i] * b[i] % Mod * fac[i] % Mod;
	a = DFT(a, n, -1); return a;
}
vector<int> operator +(vector<int> a, vector<int> b)
{
	int n = max(a.size(), b.size()); a.resize(n); b.resize(n);
	REP(i, 0, n - 1) a[i] = (a[i] + b[i]) % Mod;
	return a;
}
inline int Get(int t, int x)
{
	int ret = f[t][0], sum = x;
	REP(i, 1, f[t].size() - 1)
	{
		ret = (ret + f[t][i] * sum) % Mod;
		sum = sum * (x - i) % Mod;
	}
	return ret;
}

inline void Solve(int l, int r)
{
	if ( vis[id[l][r]] || l > r ) return ; id[l][r] = ++ num;
	int x = num; vis[x] = true;
	REP(i, (l + r - 1) / 2, (l + r + 2) / 2)
	{
		if ( i < l || i > r ) continue ;
		Solve(l, i - 1); Solve(i + 1, r);
		int ls = id[l][i - 1], rs = id[i + 1][r];
		if ( L >= a[i] && R <= b[i] ) f[x] = f[x] + f[ls] * down(f[rs]);
	}
	f[x].resize(f[x].size() + 1); int t = f[x][0];
	for ( int i = f[x].size() - 1; i >= 1; -- i ) f[x][i] = f[x][i - 1] * iinv[i] % Mod; f[x][0] = 0;
	f[x] = up(f[x]); f[x][0] = (f[x][0] + g[x] - t) % Mod;
}

signed main()
{
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);
	scanf("%lld", &n); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 0, n) { ex1[i] = inv[i]; ex2[i] = i & 1 ? -inv[i] : inv[i]; iinv[i] = power(i, Mod - 2); }

	REP(i, 1, n) { scanf("%lld%lld", &a[i], &b[i]); Stack[++ tot] = a[i]; Stack[++ tot] = b[i] + 1; }
	sort(Stack + 1, Stack + tot + 1);
	f[0].resize(1); f[0][0] = 1;
	REP(i, 1, tot - 1)
	{
		L = Stack[i]; R = Stack[i + 1] - 1;
		num = 0; Solve(1, n);
		REP(j, 1, num) { vis[j] = false; g[j] = Get(j, R - L + 1); f[j].clear(); }
	}
	printf("%lld\n", (g[id[1][n]] + Mod) % Mod);
    return 0;
}
