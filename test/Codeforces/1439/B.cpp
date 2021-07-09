/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, T, k, Begin[maxn], Next[maxn], To[maxn], e, deg[maxn];
priority_queue<pii, vector<pii>, greater<pii> > Q;
vector<int> p;
unordered_map<int, bool> Map[maxn];
bool vis[maxn], use[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[u]; }

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	cin >> T;
	while ( T -- )
	{
		cin >> n >> m >> k;
		REP(i, 1, n) { Map[i].clear(); Begin[i] = deg[i] = vis[i] = use[i] = 0; } e = 0;
		REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); Map[u][v] = Map[v][u] = true; }
        while ( !Q.empty() ) Q.pop();
        REP(i, 1, n) Q.push(pii(deg[i], i));
        int ans = n;
		while ( !Q.empty() )
		{
			int u = Q.top().second; Q.pop(); 
            if ( vis[u] ) continue ; 
            if ( deg[u] >= k )
            {
                printf("1 %d\n", ans);
                REP(i, 1, n) if ( !vis[i] ) printf("%d ", i); puts("");
                goto Finish ;
            }
            -- ans; vis[u] = true;
            if ( k * (k - 1) / 2 <= m && deg[u] == k - 1 ) 
            {
                p.clear(); use[u] = true;
                int sum = 0;
                for ( int i = Begin[u]; i; i = Next[i] ) 
                {
                    int v = To[i]; if ( vis[v] ) continue ;
                    use[v] = true; p.push_back(v); -- deg[v]; Q.push(pii(deg[v], v));
                }
                bool flag = true; 
                for ( auto it : p )
                {
                    int num = 0; 
                    for ( auto x : p ) num += Map[it][x];
                    if ( num != k - 2 ) { flag = false; break ; }
                }
                if ( flag ) 
                {
                    printf("2\n");
                    REP(i, 1, n) if ( use[i] ) printf("%d ", i); puts("");
                    goto Finish;
                }
                for ( auto it : p ) Map[it][u] = false;
                use[u] = false; for ( auto it : p ) use[it] = false;
                continue ;
            }
			for ( int i = Begin[u]; i; i = Next[i] )
			{
				int v = To[i]; -- deg[v]; Map[v][u] = false;
				if ( !vis[v] ) Q.push(pii(deg[v], v));
			}
		}
        puts("-1");
Finish : ;
    }
    return 0;
}
