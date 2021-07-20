/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月18日 星期日 12时50分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int id, n, m, a[maxn], f[maxn], size[maxn], p[maxn];
vector<int> Edge[maxn];

inline void Solve(int u)
{
	size[u] = 1; 
	for ( auto v : Edge[u] ) { Solve(v); size[u] += size[v]; }
	f[u] = a[u] - size[u] + 1;
	sort(Edge[u].begin(), Edge[u].end(), [](const int &x, const int &y) { return f[x] < f[y]; });
	int sum = 1;
	for ( auto v : Edge[u] ) 
	{
		f[u] = max(f[u], f[v] - sum);
		sum += size[v];
	}
}

inline void DFS(int u)
{
	p[u] = ++ m;
	for ( auto v : Edge[u] ) DFS(v);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &id, &n); REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 2, n) { int x; scanf("%d", &x); Edge[x].push_back(i); }
	Solve(1);
	if ( f[1] != 1 ) { puts("-1"); return 0; }
	DFS(1);
	REP(i, 1, n) printf("%d ", p[i]); puts("");
    return 0;
}
