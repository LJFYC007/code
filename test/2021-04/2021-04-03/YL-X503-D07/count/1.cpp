/***************************************************************
	File name: count.cpp
	Author: ljfcnyali
	Create time: 2021年04月03日 星期六 09时04分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 40;
const int Mod = 10007;

int n, k, c, ret, ans[maxn], fac[maxn], inv[maxn], ttt[maxn], f[2][100];
vector<int> p;
bool use[maxn][maxn], vis[maxn], del[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &k, &c); fac[0] = inv[0] = ttt[0] = 1; 
	REP(i, 1, n) { fac[i] = fac[i - 1] * i % Mod; ttt[i] = ttt[i - 1] * 2 % Mod; }
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, k) { int x, y; scanf("%d%d", &x, &y); vis[y] = true; use[x][y] = true; } 
	k = 0; REP(i, 1, n) if ( vis[i] ) { ++ k; p.push_back(i); }
	REP(i, 1, n) REP(j, 1, n) 
	{
		if ( use[i][i] || use[j][n + 1 - j] ) continue ; 
		REP(s, 0, (1 << k) - 1)
		{
			int num = 0; mem(del);
			REP(o, 0, k - 1) if ( (s >> o) & 1 )
			{
				++ num; del[p[o]] = true;
				if ( i == p[o] || n + 1 - j == p[o] ) goto Next ;
			}
			REP(o, 0, (1 << n) - 1) 
			{
				int op = 0, cnt = num;
				REP(y, 1, n) if ( (o >> y - 1) & 1 )
				{
					++ cnt;
					if ( vis[y] ) goto Finish ;
				}
				if ( (o >> i - 1) & 1 ) goto Finish;
				if ( (o >> n - j) & 1 ) goto Finish;
				mem(f); f[op][1 + (i != j || i != n + 1 - j)] = 1;
				REP(x, 1, n) 
				{
					int val = n - num;
					REP(y, 1, n) if ( !del[y] ) 
					{
						if ( vis[y] && use[x][y] ) { -- val; continue ; }
						if ( ((o >> y - 1) & 1) || (x == y && x <= i) || (x + y == n + 1 && x <= j) ) -- val;
					}
					if ( x != i && x != j ) 
						REP(u, 0, c) REP(v, 1, val) f[op ^ 1][u + v] = (f[op ^ 1][u + v] + f[op][u] * C(val, v)) % Mod;
					else
						REP(u, 0, c) REP(v, 0, val) f[op ^ 1][u + v] = (f[op ^ 1][u + v] + f[op][u] * C(val, v)) % Mod;
					REP(u, 0, c) f[op][u] = 0; op ^= 1;
				}
				ans[cnt] = (ans[cnt] + f[op][c]) % Mod;
Finish : ;
			}
Next : ;
		}
	}
	REP(i, 0, n) ret = (ret + sgn(i) * ans[i]) % Mod;
	printf("%d\n", (ret + Mod) % Mod);
    return 0;
}
