/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e9;

int n, m, T, t, n1, n2, col[maxn], b[maxn];
vector<int> Edge[maxn]; pii a[maxn];

inline void DFS(int u, int x)
{
	col[u] = x;
	for ( auto v : Edge[u] ) 
		if ( !col[v] ) DFS(v, 3 - x);
		else if ( col[v] != 3 - x ) { puts("IMPOSSIBLE"); exit(0); }
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &t, &T);
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d%d", &a[i].first, &a[i].second);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); Edge[u].push_back(v); Edge[v].push_back(u); } 
	n1 = INF; REP(i, 1, n) { n1 = min(n1, a[i].second); n2 = max(n2, a[i].first); } 
	if ( n1 + n2 < t ) n2 += t - n1 - n2;
	else if ( n1 + n2 > T ) n1 -= n1 + n2 - T;

	if ( n1 < 0 || n2 < 0 ) { puts("IMPOSSIBLE"); return 0; } 
	if ( n1 > n2 ) swap(n1, n2);
	REP(i, 1, n)
	{
		bool flag1 = a[i].first <= n1 && n1 <= a[i].second;
		bool flag2 = a[i].first <= n2 && n2 <= a[i].second;
		if ( !flag1 && !flag2 ) { puts("IMPOSSIBLE"); return 0; } 
		if ( flag1 && !flag2 ) b[i] = 1;
		if ( !flag1 && flag2 ) b[i] = 2;
		if ( flag1 && flag2 ) b[i] = 3;
		if ( b[i] <= 2 && !col[i] ) DFS(i, b[i]);
	}

	REP(i, 1, n) if ( !col[i] ) DFS(i, 1);
	REP(i, 1, n) if ( b[i] != 3 && col[i] != b[i] ) { puts("IMPOSSIBLE"); return 0; } 
	puts("POSSIBLE"); printf("%d %d\n", n1, n2);
	REP(i, 1, n) printf("%d", col[i]); puts("");
    return 0;
}
