/***************************************************************
	File name: okfly.cpp
	Author: ljfcnyali
	Create time: 2020年09月06日 星期日 08时42分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 2e4 + 10;
const int INF = 1e9;

int T, n, m, s, CCC, t, Min, Begin[maxn], Next[maxn], To[maxn], W[maxn], e;
vector<pii> Edge[maxn], p;
bool use[maxn], vis[maxn], Vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline int DFS(int u)
{
    vis[u] = true; if ( u == t ) return 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( use[v] || vis[v] ) continue ;
        if ( DFS(v) ) { p.push_back(pii(v, W[i])); return 1; }
    }
    return 0;
}

inline int DFS1(int u)
{
    // cerr << u << endl;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( Vis[v] || v == CCC ) continue ; Vis[v] = true;
        if ( vis[v] ) { Min = min(Min, W[i]); return v; }
        int x = DFS1(v); 
        if ( x ) { Min = min(Min, W[i]); return x; }
    }
    return 0;
}

inline int Get()
{
    p.clear(); REP(i, 1, n) { Vis[i] = vis[i] = false; }
    DFS(s); p.push_back(pii(s, INF)); reverse(p.begin(), p.end()); 
    REP(i, 1, n) vis[i] = false; for ( auto i : p ) vis[i.first] = true;
    int now = 0, ret = INF; 
    while ( p[now].first != t ) 
    {
        CCC = p[now].first; Min = INF; int x = DFS1(p[now].first);
        cerr << p.size() << " " << now << " " << p[now].first << " " << x << endl; 
        if ( Min != INF )
        {
            int sum = INF;
            while ( p[now + 1].first != x ) 
            { 
                sum = min(sum, p[now + 1].second); 
                ++ now; 
            }
            sum = min(sum, p[now + 1].second);
            ret = min(ret, Min + sum);
        }
        else ret = min(ret, p[now + 1].second); 
        ++ now;
    }
    return ret;
}

inline void Solve(vector<int> a)
{
    /*
    if ( a.size() == 1 ) return ;
    p[1].clear(); p[2].clear(); s = a[0]; t = a[1]; 
    for ( auto i : a ) { use[i] = true; vis[i] = false; }

    Get();

    for ( auto i : a ) use[i] = false;
    */
}

signed main()
{
    freopen("okfly.in", "r", stdin);
    freopen("okfly.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        static vector<int> a; a.clear();
        e = 1; REP(i, 1, n) { Begin[i] = 0; Edge[i].clear(); a.push_back(i); }
        REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
        LL ans = 0;
        REP(i, 1, n) 
        {
            REP(j, i + 1, n) { s = i; t = j; ans += Get() ^ i ^ j; }
            cerr << i << endl;
        }
        printf("%lld\n", ans);
        return 0;
        // Solve(a);
    }
    return 0;
}
