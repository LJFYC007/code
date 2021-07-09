/***************************************************************
	File name: AGC024D.cpp
	Author: ljfcnyali
	Create time: 2021年06月19日 星期六 15时00分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;
const int INF = 1e18;

int n, Begin[maxn], Next[maxn], To[maxn], e, ans = INF, num = INF;
pii Edge[maxn]; bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 
pii operator +(pii a, pii b) { return pii(a.first + b.first, a.second + b.second); }

inline pii Solve(vector<int> p, int x)
{
	for ( auto it : p ) vis[it] = true;
	int Max = 0; vector<int> q;
	for ( auto it : p ) 
	{
		int sum = 0;
		for ( int i = Begin[it]; i; i = Next[i] ) if ( !vis[To[i]] ) { ++ sum; q.push_back(To[i]); }
		Max = max(Max, sum);
	}
	if ( !Max ) return pii(1, x);
	return Solve(q, x * Max) + pii(1, 0);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); Edge[i] = pii(u, v); } 
	REP(i, 1, n)
	{
		vector<int> p; p.push_back(i);
		mem(vis); pii t = Solve(p, 1);
		if ( t.first < num ) { num = t.first; ans = INF; } 
		if ( t.first == num ) ans = min(ans, t.second);
	}
	REP(i, 1, n - 1)
	{
		vector<int> p; p.push_back(Edge[i].first); p.push_back(Edge[i].second);
		mem(vis); pii t = Solve(p, 2);
		if ( t.first < num ) { num = t.first; ans = INF; } 
		if ( t.first == num ) ans = min(ans, t.second);
	}
	printf("%lld %lld\n", num, ans);
    return 0;
}
