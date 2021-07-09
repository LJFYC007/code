/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月18日 星期六 08时37分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 20000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
long long dis[maxn], n, m, vis[maxn], cnt[maxn];
bool flag = false;

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline void Spfa()
{
	queue<int> Q; Q.push(0);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		vis[u] = 0; 
		if ( cnt[u] == n - 1 ) { printf("-1\n"); exit(0); }
		cnt[u] ++;
		for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i];
			if ( dis[v] < dis[u] + W[i] ) 
			{
				dis[v] = dis[u] + W[i];
				if ( !vis[v] ) 
				{
					vis[v] = 1;
					Q.push(v);
				}
			}
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
//	freopen("input.txt", "r", stdin);
    freopen("candy5.in", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, m)
	{
		int x, a, b; scanf("%d%d%d", &x, &a, &b);
		if ( x == 1 ) { add(a, b, 0); add(b, a, 0); }
		if ( x == 2 ) add(a, b, 1);
		if ( x == 3 ) add(b, a, 0);
		if ( x == 4 ) add(b, a, 1);
		if ( x == 5 ) add(a, b, 0);
		if ( (x == 2 || x == 4) && a == b ) { printf("-1\n"); return 0; }
	}
	for ( int i = n; i >= 1; -- i ) add(0, i, 1);
	Spfa();
	long long Min = 0x3f3f3f3f3f3f, ans = 0;
	REP(i, 1, n) { ans += dis[i]; Min = min(Min, dis[i]); }
	printf("%lld\n", ans);
    return 0;
}
