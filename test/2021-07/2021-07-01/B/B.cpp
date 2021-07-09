/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月01日 星期四 11时06分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 100010;
const int INF = 1e8;
const int inf = 1e18;

int n, m, k, sum; double ans;
vector<pii> Edge[maxn];

namespace MCMF 
{
    int Begin[maxn], Next[maxn], To[maxn], From[maxn], e, W[maxn], F[maxn];
    int dis[maxn], a[maxn], pre[maxn];
    bool vis[maxn];

	inline void INIT() { e = 1; mem(Begin); } 

    inline void add(int u, int v, int w, int f) 
	{ 
		To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f; 
		To[++ e] = u; From[e] = v; Next[e] = Begin[v]; Begin[v] = e; W[e] = 0; F[e] = -f; 
	}

    inline bool BFS(int s, int t)
    {
		REP(i, 1, t) { dis[i] = -inf; vis[i] = 0; }
		dis[s] = 0; a[s] = INF; vis[s] = true;
        queue<int> Q; Q.push(s);
        while ( !Q.empty() )
        {
            int u = Q.front(); Q.pop();
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i];
                if ( dis[v] < dis[u] + F[i] && W[i] > 0 ) 
                {
                    dis[v] = dis[u] + F[i];
                    a[v] = min(a[u], W[i]);
                    pre[v] = i;
                    if ( !vis[v] ) { vis[v] = true; Q.push(v); }
                }
            }
            vis[u] = false;
        }
        if ( dis[t] == -inf ) return false;
        return true;
    }

    inline bool SPFA(int s, int t, int &flow, int &cost)
    {
        if ( !BFS(s, t) ) return false;
        flow += a[t]; cost += a[t] * dis[t];
        int u = t;
        while ( u != s ) 
        {
            W[pre[u]] -= a[t]; 
            W[pre[u] ^ 1] += a[t];
            u = From[pre[u]];
        }
        return true;
    }

    inline void Solve(int s, int t, int &flow, int &cost) 
    {
        flow = cost = 0;
        while ( SPFA(s, t, flow, cost) ) ;        
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &k); 
	REP(i, 1, n) { int x; scanf("%lld", &x); sum += x; } 
	REP(i, 1, m) 
	{ 
		int x, y, z; scanf("%lld%lld%lld", &x, &y, &z); 
		Edge[x].push_back(pii(y, z)); 
	}
	REP(i, 0, n - 1)
	{
		MCMF :: INIT();
		int s = n + n + 2, t = n + n + 3;
		REP(x, 1, n) 
		{ 
			MCMF :: add(s, x, 1, 0); 
			MCMF :: add(n + x, n + n + 1, 1, INF + n);
			REP(y, 1, n - 1) MCMF :: add(n + x, t, 1, y);
		}
		vector<int> p;
		REP(x, 1, n) for ( auto it : Edge[x] ) 
		{
			p.push_back(MCMF :: e + 1);
			MCMF :: add(x, it.first + n, 1, it.second);
		}
		MCMF :: add(n + n + 1, t, i, 0);

		int flow, cost; MCMF :: Solve(s, t, flow, cost);
		int ret = sum + cost - i * INF;	
		if ( ret >= 0 ) ans = max(ans, (k == 1 ? ret : ret * ret) * 1.0 / (n - i));
	}
	printf("%.9lf\n", ans);
    return 0;
}
