/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月16日 星期四 12时14分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int a[maxn], b[maxn], l[maxn], n, m, s, dis1[maxn], dis2[maxn];
bool vis[maxn];

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void BFS1()
{
	mem(vis); memset ( dis1, 0x3f, sizeof ( dis1 ) );
	dis1[s] = 0;
	queue<int> Q; Q.push(s);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		vis[u] = false;
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( dis1[v] > dis1[u] + W[i] ) 
			{
				dis1[v] = dis1[u] + W[i];
				if ( !vis[v] ) 
				{
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}
}

inline void BFS2()
{
	mem(vis); memset ( dis2, 0x3f, sizeof ( dis2 ) );
	dis2[s] = 0;
	queue<int> Q; Q.push(s);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		vis[u] = false;
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( dis2[v] > dis2[u] + W[i] ) 
			{
				dis2[v] = dis2[u] + W[i];
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
	scanf("%d%d%d", &n, &m, &s);
	REP(i, 1, m) 
	{
		scanf("%d%d%d", &a[i], &b[i], &l[i]);
		add(a[i], b[i], l[i]);
	}
	BFS1();
	mem(Begin); e = 0;
	REP(i, 1, m) add(b[i], a[i], l[i]);
	BFS2();
	int ans = 0;
	REP(i, 1, n) { dis1[i] += dis2[i]; ans = max(ans, dis1[i]); }
	printf("%d\n", ans);
    return 0;
}
