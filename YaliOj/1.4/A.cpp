/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月10日 星期五 09时34分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0x3f, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 510 * 510 * 5;

int Begin[maxn], Next[maxn], e, To[maxn], W[maxn];
int dis[maxn];
bool vis[maxn];

int n, m;

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void BFS()
{
	deque<int> Q;
	int s = 1, t = n * m;
	Q.push_front(s);
	mem(dis); dis[s] = 0;
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop_front();
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
					if ( !Q.empty() && dis[v] <= dis[Q.front()] ) Q.push_front(v);
					else Q.push_back(v);
				}
			}
		}
	}
	if ( dis[t] == 0x3f3f3f3f ) printf("NO SOLUTION\n");
	else printf("%d\n", dis[t]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while ( T -- ) 
	{
		memset ( Begin, 0, sizeof ( Begin ) );
		memset ( vis, 0, sizeof ( vis ) );
		e = 0;
	scanf("%d%d", &n, &m);
	REP(i, 1, n)
	{
		getchar();
		REP(j, 1, m)
		{
			char c = getchar();
			int u1 = (m + 1) * (i - 1) + j, u2 = u1 + 1;
			int v1 = u1 + m + 1, v2 = u2 + m + 1;
//			printf("%d %d %d %d\n", u1, u2, v1, v2);
			if ( c == '\\' ) 
			{
				add(u1, v2, 0); add(v2, u1, 0); 
				add(u2, v1, 1); add(v1, u2, 1);
			}
			else
			{
				add(u1, v2, 1); add(v2, u1, 1);
				add(u2, v1, 0); add(v1, u2, 0);
			}
		}
	}
	++ n; ++ m;
	BFS();
	}
    return 0;
}
