/***************************************************************
	File name: 5.cpp
	Author: ljfcnyali
	Create time: 2019年06月02日 星期日 08时39分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

int deg[maxn], degg[maxn], T, n, m;
bool vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int T, cnt = 0; scanf("%d", &T);
	while ( T -- ) 
	{
		++ cnt; printf("Case #%d: ", cnt); 
		mem(deg); mem(degg); mem(vis);
		scanf("%d%d", &n, &m);
		REP(i, 1, n - 1) 
		{
			int u, v; scanf("%d%d", &u, &v);
			deg[u] ++; deg[v] ++;
		}
		REP(i, 1, n) if ( deg[i] > 1 ) vis[i] = true;
		REP(i, 1, m - n + 1)
		{
			int u, v; scanf("%d%d", &u, &v);
			degg[u] ++; degg[v] ++;
		}
		int ans = 2147483647;
		REP(i, 1, n)
			if ( !vis[i] ) ans = min(ans, deg[i] + degg[i]);
		printf("%d\n", ans);
	}
    return 0;
}
