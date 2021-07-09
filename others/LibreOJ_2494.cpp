/***************************************************************
	File name: LibreOJ_2494.cpp
	Author: ljfcnyali
	Create time: 2021年03月26日 星期五 19时31分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 1e9 + 7;

int n, m, q, M, a[maxn][maxn], p[maxn], r[maxn];
struct node 
{
	int val, id; vector<int> a;
	bool operator <(const node &g) const 
	{
		REP(i, 0, n - 1)
		{
			if ( a[i] < g.a[i] ) return true;
			if ( a[i] > g.a[i] ) return false;
		}
		return false;
	}
} f[maxn];

inline char get() { char c = getchar(); while ( c < '0' || c > '9' ) c = getchar(); return c; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &q);
	M = 1; REP(i, 1, n) M = M * 2 % Mod;
	REP(i, 1, n) REP(j, 1, m) a[i][j] = get() - '0';
	REP(i, 1, m)
	{
		f[i].id = i;
		for ( int j = n; j >= 1; -- j ) { f[i].a.push_back(a[j][i]); f[i].val = (f[i].val * 2 + a[j][i]) % Mod; } 
	}
	sort(f + 1, f + m + 1); f[m + 1].val = M; f[m + 1].id = m + 1;
	REP(i, 1, m) p[f[i].id] = i;
	REP(o, 1, q)
	{
		REP(i, 1, m) r[i] = get() - '0';
		int L = 0, R = m + 1;
		REP(i, 1, m) 
			if ( r[i] == 1 ) R = min(R, p[i]);
			else L = max(L, p[i]);
		int ans = (f[R].val - f[L].val) % Mod;
		if ( L >= R ) puts("0");
		else printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
} 
