/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月17日 星期五 15时46分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[maxn], n, r[maxn], num[maxn], cnt[maxn], ans;
bool vis[maxn];

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline bool Spfa()
{
	queue<int> Q; Q.push(0); dis[0] = 0;
	while ( !Q.empty() )
	{
		int u = Q.front(); Q.pop();
		cnt[u] ++;
		if ( cnt[u] > 24 ) { while ( !Q.empty() ) Q.pop(); return false; }
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
	while ( !Q.empty() ) Q.pop();
	return true;
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
		ans = 0x3f3f3f3f; mem(num);
		REP(i, 0, 23) scanf("%d", &r[i]); 
		scanf("%d", &n);
		REP(i, 1, n) { int x; scanf("%d", &x); num[x] ++; }
		REP(s23, 0, n)
		{
			REP(i, 0, 23) dis[i] = -0x3f3f3f3f;
			mem(Begin); e = 0; mem(vis); mem(cnt);
			REP(i, 0, 23) { add(i - 1, i, 0); add(i, i - 1, -num[i]); }
			REP(i, 0, 7) add(i + 16, i, r[i] - s23);
			REP(i, 8, 23) add(i - 8, i, r[i]);
			if ( Spfa() == true ) { printf("%d\n", s23); ans = 0; break ; }
		}
		if ( ans == 0x3f3f3f3f ) printf("No Solution\n");
	}
    return 0;
}
