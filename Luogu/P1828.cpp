/***************************************************************
	File name: P1828.cpp
	Author: ljfcnyali
	Create time: 2019年05月08日 星期三 14时59分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0x3f, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 300010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, p, c, a[maxn], dis[maxn], ans = 0x3f3f3f3f, sum;
bool vis[maxn];

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void BFS(int x)
{
	queue<int> Q;
	Q.push(x);
	vis[x] = true;
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop();
		vis[u] = false;
		for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i];
			if ( dis[v] > dis[u] + W[i] )
			{
				dis[v] = dis[u] + W[i];
				if ( !vis[v] ) 
				{
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &p, &c);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, c)
	{
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		add(u, v, w); add(v, u, w);
	}
	REP(i, 1, p)
	{
		mem(dis); dis[i] = 0;
		memset ( vis, 0, sizeof ( vis ) ) ;
		BFS(i);
		sum = 0;
		REP(j, 1, n) sum += dis[a[j]];
		ans = min(ans, sum);
	}
	printf("%d\n", ans);
    return 0;
}
