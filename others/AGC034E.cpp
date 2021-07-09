/***************************************************************
	File name: AGC034E.cpp
	Author: ljfcnyali
	Create time: 2021年02月22日 星期一 11时46分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, Size[maxn], f[maxn], Begin[maxn], Next[maxn], To[maxn], e, ret, ans = INF;
char s[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS1(int u, int fa)
{
	Size[u] = s[u] == '1'; f[u] = 0;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		DFS1(v, u); Size[u] += Size[v]; f[u] += f[v] + Size[v];
	}
}

inline bool DFS2(int u, int fa, int num)
{
	vector<pii> p;
	for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) p.push_back(pii(f[To[i]] + Size[To[i]], To[i]));
	if ( !p.size() ) return false;
	sort(p.begin(), p.end());
	if ( p.back().first * 2 > f[u] ) 
	{
		num -= f[u] - p.back().first;
		if ( num <= 0 ) return true;
		return DFS2(p.back().second, u, num);
	}
	return num * 2 <= f[u];
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); scanf("%s", s + 1);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
	REP(i, 1, n) { DFS1(i, 0); if ( f[i] % 2 == 0 && DFS2(i, 0, f[i] / 2) ) ans = min(ans, f[i] / 2); }
	printf("%lld\n", ans == INF ? -1 : ans);
    return 0;
}
