/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年08月10日 星期一 11时09分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define x first
#define y second
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int INF = 1e6;

int n, m, num, R, d, ans, match[maxn];
vector<int> Edge[maxn];
pii a[maxn], op;
struct node { pii x; int id; } b[maxn];
bool vis[maxn], use[maxn];

int operator * (pii a, pii b) { return a.x * b.y - a.y * b.x; }
bool operator < (node a, node b) 
{
    if ( a.x * op != 0 && b.x * op != 0 && (a.x * op > 0) != (b.x * op > 0) ) return op * a.x > 0;
    return a.x * b.x > 0;
}

inline int sqr(int x) { return x * x; }

inline int Dis(int i, int j) { return sqr(a[i].x - a[j].x) + sqr(a[i].y - a[j].y); }

inline int DFS(int u)
{
    if ( use[u] ) return 0; use[u] = true;
    for ( auto v : Edge[u] ) if ( !match[v] || DFS(match[v]) )
    {
        match[u] = v; match[v] = u; 
        return 1;
    }
    return 0;
}

signed main()
{
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &R, &d);
    REP(i, 1, n) scanf("%lld%lld", &a[i].x, &a[i].y);
    REP(i, 1, n) if ( Dis(i, 1) <= R * R ) vis[i] = true; 
    REP(i, 1, n)
    {
        if ( vis[i] ) continue ;
        op = pii(a[i].x - a[1].x, a[i].y - a[1].y);
        m = 0; 
        REP(j, 1, n) if ( vis[j] && Dis(i, j) <= d * d ) { b[++ m].x = pii(a[j].x - a[i].x, a[j].y - a[i].y); b[m].id = j; }
        sort(b + 1, b + m + 1);
        REP(j, 1, m) Edge[i].push_back(b[j].id); 
    }

    REP(i, 1, n)
    {
        if ( vis[i] ) continue ;
        mem(use); if ( DFS(i) ) ++ ans;
    }
    printf("%lld\n", ans * 2);
    mem(use);
    REP(i, 1, ans)
    {
        int pos = 0;
        REP(j, 1, n) 
        {
            if ( vis[j] || !match[j] ) continue ;
            while ( !Edge[j].empty() && use[*Edge[j].begin()] ) Edge[j].erase(Edge[j].begin());
            if ( !Edge[j].empty() && *Edge[j].begin() == match[j] ) { pos = j; break ; }
        }
        printf("%lld %lld\n", pos, match[pos]); use[match[pos]] = true;
    }
    return 0;
}
