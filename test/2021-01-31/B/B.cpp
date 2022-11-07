/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年01月31日 星期日 10时18分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define int long long
#define x first
#define y second
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int maxm = 1e6 + 10;
const int Mod = 998244353;

int T, n, m, Begin[maxn], Next[maxm], To[maxm], e, ans, deg[maxn], id[maxn], cnt[maxn];
vector<int> Edge[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[u]; }

inline int calc(int x) { return (x * (x - 1) / 2) % Mod; }

inline bool cmp(int a, int b) { return deg[a] > deg[b] || (deg[a] == deg[b] && a < b); }

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld%lld", &n, &m); ans = m * (n - 2 + m - 1) % Mod;
		e = 0; REP(i, 1, n) { Begin[i] = deg[i] = 0; Edge[i].clear(); id[i] = i; }
		REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v);	add(u, v); add(v, u); }
		REP(i, 1, n) ans = (ans + calc(deg[i])) % Mod;
		sort(id + 1, id + n + 1, cmp);
		REP(u, 1, n) for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i]; if ( id[u] < id[v] ) continue ;
			Edge[u].push_back(v);
		}
		REP(u, 1, n)
		{
			for ( int i = Begin[u]; i; i = Next[i] )
			{
				int v = To[i]; vis[v] = true;
				for ( auto w : Edge[v] ) if ( id[w] < id[u] ) { ans = (ans + cnt[w]) % Mod; ++ cnt[w]; }
			}
			for ( auto v : Edge[u] )
				for ( auto w : Edge[v] ) if ( id[w] < id[u] && vis[w] )
					ans = (ans + 3) % Mod;
			for ( int i = Begin[u]; i; i = Next[i] )
			{
				int v = To[i]; vis[v] = false;
				for ( auto w : Edge[v] ) if ( id[w] < id[u] ) cnt[w] = 0;
			}
		}
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
