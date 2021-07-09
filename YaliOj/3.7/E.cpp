/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月23日 星期四 15时34分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

int k, m, ans[maxn];
bool vis[maxn];

inline bool dfs(int x, int dis)
{
	if ( vis[x] ) return false ; vis[x] = true;
	ans[dis] = x >> (k - 1);
	if ( dis == m ) return true;
	if ( dfs((x << 1) & (m - 1), dis + 1) ) return true;
	if ( dfs((x << 1 | 1) & (m - 1), dis + 1) ) return true;
	vis[x] = false; return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &k); printf("%d ", m = 1 << k);
	dfs(0, 1);
	REP(i, 1, m) printf("%d", ans[i]); puts("");
    return 0;
}
