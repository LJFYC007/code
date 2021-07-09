#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss
const int maxn = 10010;

int n, s, t, Begin[maxn], To[maxn], Next[maxn], W[maxn], e, dis[maxn];
priority_queue< pair<int, int > > Q;
bool vis[maxn];

inline void add(int u, int v, int w)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
	W[e] = w;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &s, &t);
	REP(i, 1, n)
	{
		int k, x; scanf("%d", &k);
		REP(j, 1, k)
		{
			scanf("%d", &x);
			if ( j == 1 ) add(i, x, 0);
			else add(i, x, 1);
		}
	}
	REP(i, 1, n) dis[i] = 0x3f3f3f3f;
	Q.push( pair<int, int> (0, s) );
	dis[s] = 0;
	while ( !Q.empty() )
	{
		int u = Q.top().second; Q.pop();
		if ( vis[u] == true ) continue ;
		vis[u] = true;
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i];
			if ( dis[v] > dis[u] + W[i] ) 
			{
				dis[v] = dis[u] + W[i];
				Q.push ( pair<int, int> (-dis[v], v) );
			}
		}
	}
	printf("%d\n", dis[t] == 0x3f3f3f3f ? -1 : dis[t]);
	return 0;
}

