#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int T, n, m, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, id[maxn], cnt, p[maxn];

inline void add(int u, int v)
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;
	swap(u, v);
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;
}

inline void DFS(int u)
{
	if ( id[u] ) return ; id[u] = cnt; p[cnt] += a[u];
	for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i]);
}

int main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%d", &T);
	while ( T -- )
	{
		scanf("%d%d", &n, &m);
		REP(i, 1, 2 * n) scanf("%d", &a[i]);
		e = cnt = 0; mem(Begin); mem(id); mem(p);
		REP(i, 1, m)
		{
			int t, u, v; scanf("%d%d%d", &t, &u, &v);
			if ( t == 1 ) { add(u, v + n); add(v, u + n); }
			else { add(u, v); add(u + n, v + n); }
		}
		REP(i, 1, 2 * n) if ( !id[i] ) { ++ cnt; DFS(i); }
		REP(i, 1, n)
		{
			if ( id[i] == id[i + n] && (p[id[i]] & 1) ) { puts("NO"); goto Finish; }
			if ( id[i] != id[i + n] && p[id[i]] != p[id[i + n]] ) { puts("NO"); goto Finish; }
		}
		puts("YES");
		Finish : ;
	}
	return 0;
}
