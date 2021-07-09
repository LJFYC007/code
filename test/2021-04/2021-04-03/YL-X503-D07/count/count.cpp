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

int n, k, c, ret, ans[maxn], fac[maxn], inv[maxn], ttt[maxn], f[2][41 * 41], C[100][100];
vector<int> p;
bool use[maxn][maxn], vis[maxn], del[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 

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

	REP(i, 0, n) { C[i][0] = 1; REP(j, 1, i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod; }
	
	// 对角线无限制
	REP(s, 0, (1 << k) - 1)
	{
		int num = 0; 
		REP(o, 0, k - 1) if ( (s >> o) & 1 ) ++ num; 
		REP(o, 0, n - k)
		{
			int cnt = num + o, op = 0;
			mem(f); f[op][0] = 1;
			REP(x, 1, n)
			{
				int val = n - num - o;
				REP(y, 0, k - 1) if ( !((s >> y) & 1) && use[x][p[y]] ) -- val;
				REP(i, 0, c) REP(j, 1, val) f[op ^ 1][i + j] = (f[op ^ 1][i + j] + f[op][i] * C[val][j]) % Mod;
				REP(i, 0, c) f[op][i] = 0; op ^= 1;
			}
			ans[cnt] = (ans[cnt] + f[op][c] * C[n - k][o]) % Mod;
		}
	}

	// 正对角线必须为空
	/*
	REP(s, 0, (1 << k) - 1)
	{
		int num = 0; 
		REP(o, 0, k - 1) if ( (s >> o) & 1 ) ++ num;
		REP(o, 0, n - k)
		{
			int cnt = num + o, op = 0, t = o;
			mem(f); f[op][0] = 1;
			REP(x, 1, n)
			{
				int val = n - num - o;
				REP(y, 0, k - 1) if ( !((s >> y) & 1) && (use[x][p[y]] || x == p[y]) ) -- val;
				if ( !vis[x] ) 
				{
					-- t; if ( t < 0 ) -- val;
				}
				REP(i, 0, c) REP(j, 1, val) f[op ^ 1][i + j] = (f[op ^ 1][i + j] + f[op][i] * C(val, j)) % Mod;
				REP(i, 0, c) f[op][i] = 0; op ^= 1;
			}
			ans[cnt] = (ans[cnt] - f[op][c] * C(n - k, o)) % Mod;
		}
	}
	*/
	REP(s, 0, (1 << k) - 1)
	{
		int num = 0; mem(del);
		REP(o, 0, k - 1) if ( (s >> o) & 1 ) { ++ num; del[p[o]] = true; }
		REP(o, 0, (1 << n) - 1) 
		{
			int op = 0, cnt = num;
			REP(y, 1, n) if ( (o >> y - 1) & 1 ) { ++ cnt; if ( vis[y] ) goto Finish2 ; }
			mem(f); f[op][0] = 1;
			REP(x, 1, n) 
			{
				int val = n - num;
				REP(y, 1, n) if ( !del[y] ) 
				{
					if ( vis[y] && use[x][y] ) { -- val; continue ; }
					if ( ((o >> y - 1) & 1) || (x == y) ) -- val;
				}
				REP(u, 0, c) REP(v, 1, c - val) f[op ^ 1][u + v] = (f[op ^ 1][u + v] + f[op][u] * C[val][v]) % Mod;
				REP(u, 0, c) f[op][u] = 0; op ^= 1;
			}
			ans[cnt] = (ans[cnt] - f[op][c]) % Mod;
Finish2 : ; 
		}
	}

	// 负对角线必须为空
	REP(s, 0, (1 << k) - 1)
	{
		int num = 0; mem(del);
		REP(o, 0, k - 1) if ( (s >> o) & 1 ) { ++ num; del[p[o]] = true; }
		REP(o, 0, (1 << n) - 1) 
		{
			int op = 0, cnt = num;
			REP(y, 1, n) if ( (o >> y - 1) & 1 ) { ++ cnt; if ( vis[y] ) goto Finish3 ; }
			mem(f); f[op][0] = 1;
			REP(x, 1, n) 
			{
				int val = n - num;
				REP(y, 1, n) if ( !del[y] ) 
				{
					if ( vis[y] && use[x][y] ) { -- val; continue ; }
					if ( ((o >> y - 1) & 1) || (x + y == n + 1) ) -- val;
				}
				REP(u, 0, c) REP(v, 1, c - val) f[op ^ 1][u + v] = (f[op ^ 1][u + v] + f[op][u] * C[val][v]) % Mod;
				REP(u, 0, c) f[op][u] = 0; op ^= 1;
			}
			ans[cnt] = (ans[cnt] - f[op][c]) % Mod;
Finish3 : ;
		}
	}
	
	// 两侧都为空
	REP(s, 0, (1 << k) - 1)
	{
		int num = 0; mem(del);
		REP(o, 0, k - 1) if ( (s >> o) & 1 ) { ++ num; del[p[o]] = true; }
		REP(o, 0, (1 << n) - 1) 
		{
			int op = 0, cnt = num;
			REP(y, 1, n) if ( (o >> y - 1) & 1 ) { ++ cnt; if ( vis[y] ) goto Finish4 ; }
			mem(f); f[op][0] = 1;
			REP(x, 1, n) 
			{
				int val = n - num;
				REP(y, 1, n) if ( !del[y] ) 
				{
					if ( vis[y] && use[x][y] ) { -- val; continue ; }
					if ( ((o >> y - 1) & 1) || (x == y) || (x + y == n + 1) ) -- val;
				}
				REP(u, 0, c) REP(v, 1, c - val) f[op ^ 1][u + v] = (f[op ^ 1][u + v] + f[op][u] * C[val][v]) % Mod;
				REP(u, 0, c) f[op][u] = 0; op ^= 1;
			}
			ans[cnt] = (ans[cnt] + f[op][c]) % Mod;
Finish4 : ;
		}
	}

	REP(i, 0, n) ret = (ret + sgn(i) * ans[i]) % Mod;
	printf("%d\n", (ret + Mod) % Mod);
    return 0;
}
