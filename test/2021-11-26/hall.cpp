#include "hall.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1 << 20;

int f[maxn], vis[maxn], cnt, match[maxn];
bool flag;

inline int DFS(int n, int x)
{
	if ( vis[x] == cnt ) return 0;
	vis[x] = cnt;
	REP(j, 0, n - 1) if ( (x >> j) & 1 ) 
	{
		int y = x ^ (1 << j);
		if ( !match[y] || DFS(n, match[y]) ) 
		{
			match[x] = y; match[y] = x;
			return true;
		}
	}
	return false;
}

int solve(int n, int k, int s)
{
	if ( !flag ) 
	{
		flag = true;
		REP(i, 0, (1 << n) - 1)
			REP(j, 0, n - 1) if ( (i >> j) & 1 ) ++ f[i];
		REP(i, 0, (1 << n) - 1) if ( f[i] == k ) { ++ cnt; DFS(n, i); }
	}
	return match[s];
}
