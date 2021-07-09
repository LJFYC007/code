/***************************************************************
	File name: angry.cpp
	Author: ljfcnyali
	Create time: 2021年03月27日 星期六 10时06分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 1e9 + 7;

int n, k, a[maxn], C[510][510], p[maxn];
vector<int> f[maxn][2];
char s[maxn];

inline vector<int> DFS(int x, bool num, bool op)
{
	if ( x == n + 1 ) { vector<int> a(k); a[0] = !op && !num; return a; }
	if ( !op && !f[x][num].empty() ) return f[x][num];
	int tmp = op ? s[x] - '0' : 1; vector<int> g(k);
	REP(i, 0, tmp)
	{
		vector<int> h = DFS(x + 1, num ^ i, op & (i == tmp));
		if ( i == 1 ) REP(m, 0, k - 1) 
		{
			int val = 1;
			REP(j, 0, m) 
			{
				g[m] = (g[m] + val * C[m][j] % Mod * h[m - j]) % Mod;
				val = val * p[n - x] % Mod;
			}
		}
		else REP(m, 0, k - 1) g[m] = (g[m] + h[m]) % Mod;
	}
	if ( !op ) f[x][num] = g; return g;
}

signed main()
{
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);
	scanf("%s", s + 1); n = str(s + 1);
	scanf("%lld", &k); REP(i, 0, k - 1) scanf("%lld", &a[i]);
	p[0] = C[0][0] = 1; REP(i, 1, n) p[i] = p[i - 1] * 2 % Mod;
	REP(i, 1, k) { C[i][0] = 1; REP(j, 1, i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod; } 
	vector<int> f = DFS(1, 1, 1); int ans = 0;
	REP(i, 0, k - 1) ans = (ans + f[i] * a[i]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
