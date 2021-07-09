/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2021年05月05日 星期三 19时51分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6e5 + 10;

int n, m, x, Begin[maxn], Next[maxn], To[maxn], e = 1, a[maxn], sum;
vector<int> ans1, ans2; bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u)
{
	vis[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( vis[v] ) continue ; 
		DFS(v); 
		if ( a[v] >= x ) { a[u] += a[v] - x; ans1.push_back(i / 2); }
		else ans2.push_back(i / 2);
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &x);
	REP(i, 1, n) { scanf("%lld", &a[i]); sum += a[i]; }
	if ( sum < (n - 1) * x ) { puts("NO"); return 0; } 
	REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); } 
	puts("YES"); DFS(1);
	reverse(ans2.begin(), ans2.end());
	for ( auto it : ans1 ) printf("%lld\n", it);
	for ( auto it : ans2 ) printf("%lld\n", it);
    return 0;
}
