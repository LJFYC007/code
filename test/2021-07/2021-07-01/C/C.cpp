/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月01日 星期四 08时41分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, a[maxn], m, k, c[maxn], ans;
double f[maxn], g[maxn], ret; vector<int> p[maxn];

inline int lowbit(int x) { return x & -x; } 
inline void modify(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] = max(c[i], val); }
inline int query(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = max(ret, c[i]); return ret; }

inline void Solve(int x, int l1, int r1, int y, int l2, int r2)
{
	if ( l1 > r1 ) return ;
	int Mid = p[x][(l1 + r1) / 2], pos = 0; 
	REP(i, l2, r2)
	{
		int it = p[y][i];
		if ( it < Mid && a[Mid] > a[it] && f[Mid] < f[it] + g[a[Mid] - a[it] + k] )
		{
			pos = i;
			f[Mid] = f[it] + g[a[Mid] - a[it] + k];
		}
	}
	Solve(x, l1, (l1 + r1) / 2 - 1, y, l2, pos);
	Solve(x, (l1 + r1) / 2 + 1, r1, y, pos, r2);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	REP(i, 1, maxn - 10) g[i] = log(i);
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);

	REP(i, 1, n) 
	{
		int x = query(a[i] - 1) + 1;
		modify(a[i], x); ans = max(ans, x);
		p[x].push_back(i);
	}
	printf("%d\n", ans);
			
	scanf("%d", &m);
	while ( m -- ) 
	{
		scanf("%d", &k); mem(f);
		REP(i, 2, ans) Solve(i, 0, p[i].size() - 1, i - 1, 0, p[i - 1].size() - 1);
		ret = 0; for ( auto it : p[ans] ) ret = max(ret, f[it]);
		printf("%.9lf\n", ret);
	}
    return 0;
}
