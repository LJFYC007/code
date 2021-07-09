/***************************************************************
	File name: ARC096F.cpp
	Author: ljfcnyali
	Create time: 2021年06月16日 星期三 20时23分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 51;
const int maxm = 51 * 51 * 51;
const int INF = 1e18;

int n, m, d, num, v[maxn], w[maxn], a[maxn], b[maxn], p[maxn], f[maxm], ans;
vector<int> Edge[maxn];

inline void DFS(int u)
{
	w[u] = 1;
	for ( auto i : Edge[u] ) 
	{
		DFS(i); w[u] += w[i];
		v[u] += v[i];
	}
}

inline bool cmp(int x, int y) { return v[x] * w[y] < v[y] * w[x]; }

inline void Insert(int v, int w)
{
	for ( int i = num; i >= 0; -- i ) f[i + w] = min(f[i + w], f[i] + v);
	num += w;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld%lld", &n, &m, &d, &v[1]);
	REP(i, 1, n) { a[i] = min(n, d); b[i] = d - a[i]; p[i] = i; } 
	a[1] = n; b[1] = INF;
	REP(i, 2, n) { int x; scanf("%lld%lld", &v[i], &x); Edge[x].push_back(i); }
	DFS(1); sort(p + 1, p + n + 1, cmp);
	f[0] = 0; REP(i, 1, maxm - 1) f[i] = INF;
	REP(i, 1, n) 
	{
		int x = 1;
		while ( x <= a[i] ) { Insert(v[i] * x, w[i] * x); a[i] -= x; x *= 2; } 
		Insert(v[i] * a[i], w[i] * a[i]);
	}
	REP(i, 0, num) if ( f[i] <= m ) 
	{
		int sum = m - f[i], val = i;
		REP(j, 1, n)
		{
			int x = min(b[p[j]], sum / v[p[j]]);
			sum -= x * v[p[j]]; val += x * w[p[j]];
		}
		ans = max(ans, val);
	}
	printf("%lld\n", ans);
    return 0;
}
