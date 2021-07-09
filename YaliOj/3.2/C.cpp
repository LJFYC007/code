/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月16日 星期四 08时56分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int a[maxn], b[maxn], l[maxn], n, p, k;
int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int ans = 0x3f3f3f3f, dis[maxn];
bool vis[maxn];

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

inline bool check(int x)
{
	e = 0; mem(Begin); mem(vis);
	REP(i, 1, p)
		if ( l[i] > x ) { add(a[i], b[i], 1); add(b[i], a[i], 1); }
		else { add(a[i], b[i], 0); add(b[i], a[i], 0); }
	queue<int> Q; Q.push(1); 
	memset ( dis, 0x3f, sizeof ( dis ) );
	dis[1] = 0;
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
//	printf("%d ", x);
//	REP(i ,1, n) printf("%d ", dis[i]); puts("");
	if ( dis[n] <= k )  return true;
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &p, &k);
	int L = 0, R = 0;
	REP(i, 1, p) { scanf("%d%d%d", &a[i], &b[i], &l[i]); R = max(R, l[i]); }
	while ( L <= R )
	{
		int Mid = (L + R) / 2;
		if ( check(Mid) ) { if ( dis[n] == k ) ans = min(ans, Mid); R = Mid - 1; }
		else L = Mid + 1;
	}
	if ( check(0) ) ans = 0;
	printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}
