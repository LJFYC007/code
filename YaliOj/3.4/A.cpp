/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月17日 星期五 14时18分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), -0x3f, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, dis[maxn], Min = 0x3f3f3f3f, Max;
bool vis[maxn];

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void Spfa()
{
	queue<int> Q;
	Q.push(Min);
	mem(dis);
	dis[Min] = 0;
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		vis[u] = false;
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( dis[v] < dis[u] + W[i] ) 
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
	printf("%d\n", dis[Max]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n)
	{
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		-- u;
		Min = min(Min, u); Max = max(Max, v);
		add(u, v, w);
	}
	REP(i, Min, Max)
	{
		add(i, i + 1, 0);
		add(i + 1, i, -1);
	}
	Spfa();
    return 0;
}
