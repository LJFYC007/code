/***************************************************************
	File name: filter.cpp
	Author: ljfcnyali
	Create time: 2020年11月30日 星期一 10时20分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 1e18;
const int Delta = 1e6;
const int Mod = 998244353;

int n, m, k, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dis[maxn], lst, pre[maxn];
bool vis[maxn];
priority_queue<pii, vector<pii>, greater<pii> > Q;
vector<pii> p;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Solve(int x)
{
    int l = lst, r = 0;
    REP(i, lst, n + 1) if ( a[i] != x ) { r = i - 1; lst = i; break ; }
    p.clear(); REP(i, l, r) p.push_back(pii(dis[i], i)); 
    sort(p.begin(), p.end());
    for ( int i = 1; i < p.size(); ++ i )
        if ( p[i].first > p[i - 1].first + Delta ) 
        {
            int x = p[i].first - p[i - 1].first - Delta;
            for ( int j = i; j < p.size(); ++ j ) 
                p[j].first -= x;
        }
    for ( auto it : p ) dis[it.second] = it.first - p[0].first;
    REP(i, l, r) { vis[i] = false; Q.push(pii(dis[i], i)); }

    // REP(i, l, r) cout << dis[i] << " "; cout << endl;

    while ( !Q.empty() ) 
    {
        int u = Q.top().second; Q.pop();
        if ( vis[u] ) continue ; vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( W[i] == 0 && dis[v] > dis[u] + 1 ) { dis[v] = dis[u] + 1; pre[v] = u; Q.push(pii(dis[v], v)); }
            if ( W[i] == 1 && dis[v] > dis[u] * 2 ) { dis[v] = dis[u] * 2; pre[v] = u; }
        }
    }
}

inline void Get(int x)
{
    if ( !pre[x] ) return ;
    if ( dis[pre[x]] == INF ) Get(pre[x]);
    int val = dis[pre[x]]; if ( val == INF ) return ;
    if ( a[x] == a[pre[x]] ) dis[x] = (val + 1) % Mod;
    else dis[x] = val * 2 % Mod;
}

signed main()
{
    freopen("filter.in", "r", stdin);
    freopen("filter.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k); lst = 1;
    REP(i, 1, k - 1)
    {
        int x; scanf("%lld", &x);
        REP(j, lst, x) a[j] = i;
        lst = x + 1;
    }
    REP(i, lst, n) a[i] = k;
    REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); add(u, v, a[u] < a[v]); }
    REP(i, 2, n) dis[i] = INF; 

    lst = 1; REP(i, 1, k) Solve(i);
    REP(i, 2, n) dis[i] = INF;
    REP(i, 2, n) if ( dis[i] == INF ) Get(i);
    // REP(i, 2, n) cout << pre[i] << " "; cout << endl;
    REP(i, 1, n) printf("%lld\n", dis[i] == INF ? -1 : dis[i] % Mod);
    return 0;
}
