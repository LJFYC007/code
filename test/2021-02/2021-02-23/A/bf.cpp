/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 15时17分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;
const int Mod = 998244353;

int n, m, q, f[maxn];
vector<pii> Edge[maxn];
bool vis[maxn], unuse[maxn];

inline void DFS(int x)
{
	vis[x] = true; if ( unuse[x] ) return ; 
	if ( x <= m ) { f[x] = 1; return ; } 
	for ( auto it : Edge[x] ) 
	{
		if ( !vis[it.first] ) DFS(it.first);
		if ( !vis[it.second] ) DFS(it.second);
		if ( f[it.first] == -1 || f[it.second] == -1 ) continue ; 
		if ( f[x] == -1 ) f[x] = f[it.first] + f[it.second];
		else f[x] = max(f[x], f[it.first] + f[it.second]);
	}
}

inline void Solve(int x) { REP(i, 1, n) { vis[i] = false; f[i] = -1; } DFS(x); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &q);
	while ( q -- ) 
	{
		int op, x, y, z; scanf("%d", &op);
		if ( op == 1 ) 
		{
			scanf("%d%d", &x, &y); unuse[y] = true; Solve(x); unuse[y] = false;
			if ( f[x] == -1 ) { Solve(x); printf("%d\n", f[x] == -1 ? -1 : 1); }
			else puts("0");
		}
		if ( op == 2 ) { scanf("%d", &x); Solve(x); printf("%d\n", f[x]); }
		if ( op == 3 ) 
		{
			scanf("%d%d%d", &x, &y, &z);
			Edge[z].push_back(pii(x, y));
		}
	}
    return 0;
}
