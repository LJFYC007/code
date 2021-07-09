/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月14日 星期二 09时38分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;
const int Mod = 2147483647;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, dis[maxn];
long long sum = 1, ans[maxn];
bool vis[maxn];

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void BFS()
{
	memset ( dis, 0x3f, sizeof ( dis ) ) ; dis[1] = 0;
	queue<int> Q; Q.push(1);
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
				if ( !vis[v])
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
	scanf("%d%d", &n, &m);
	REP(i, 1, m) 
	{
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		add(u, v, w); add(v, u, w);
	}
	BFS();
	REP(u, 1, n)
		for ( int i = Begin[u]; i; i = Next[i] ) 
			if ( dis[To[i]] == dis[u] + W[i] ) ++ ans[To[i]];
	REP(i, 2, n) sum = (sum * ans[i]) % Mod;
//	REP(i, 1, n) printf("%d ", ans[i]);
//	REP(i, 1, n) printf("%d ", dis[i]);
	printf("%lld\n", sum);
    return 0;
}
