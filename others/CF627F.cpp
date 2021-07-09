/***************************************************************
	File name: CF627F.cpp
	Author: ljfcnyali
	Create time: 2021年01月13日 星期三 08时56分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, ans, x1, x2;
int a[maxn], b[maxn], x, y, dis[maxn], anc[maxn], t, len;
bool use[maxn];
vector<vector<int> > f;
vector<int> A, B;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] + 1; anc[v] = u; DFS(v, u);
    }
}

inline vector<int> Get(int x)
{
    vector<int> p; 
    while ( !use[x] && a[x] != b[x] ) { p.push_back(x); x = anc[x]; }
    return p;
}

inline int LCA(int x, int y)
{
    if ( dis[x] < dis[y] ) swap(x, y);
    while ( dis[x] > dis[y] ) x = anc[x];
    if ( x == y ) return x;
    while ( anc[x] != anc[y] ) { x = anc[x]; y = anc[y]; }
    return anc[x];
}

inline int Dis(int x, int y) { return dis[x] + dis[y] - 2 * dis[LCA(x, y)]; }

inline void DFS2(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS2(v, u);
    }
    vector<int> p = Get(u);
    if ( p.size() ) 
    {
        f.push_back(p); for ( auto it : p ) use[it] = true;
        if ( f.size() > 2 ) { puts("-1"); exit(0); }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); 
    REP(i, 1, n) { scanf("%lld", &a[i]); if ( !a[i] ) x = i; }
    REP(i, 1, n) { scanf("%lld", &b[i]); if ( !b[i] ) y = i; }
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    dis[y] = 1; DFS(y, 0);
    int u = x; while ( u != y ) { a[u] = a[anc[u]]; u = anc[u]; } a[y] = 0;
    DFS2(y, 0);
    if ( f.size() == 0 ) { printf("0 %lld\n", dis[x] - dis[y]); return 0; } 
    if ( f.size() == 1 ) 
    {
        vector<int> p = f[0]; t = anc[p.back()]; 
        x1 = p.front(); x2 = t; len = dis[x1] - dis[t] + 1;
        for ( auto it : p ) { A.push_back(a[it]); B.push_back(b[it]); }
    }
    if ( f.size() == 2 ) 
    {
        vector<int> p = f[0]; t = anc[p.back()]; len = dis[p.front()] - dis[t];
        x1 = p.front();
        for ( auto it : p ) { A.push_back(a[it]); B.push_back(b[it]); }
        p = f[1]; if ( anc[p.back()] != t ) { puts("-1"); return 0; } len += dis[p.front()] - dis[t] + 1;
        x2 = p.front();
        for ( int i = p.size() - 1; i >= 0; -- i ) { A.push_back(a[p[i]]); B.push_back(b[p[i]]); }
    }

    int ans = Dis(x, t) + Dis(t, y);
    int pos = -1; for ( int i = 0; i < B.size(); ++ i ) if ( B[i] == A.front() ) pos = i;
    if ( pos == -1 ) { puts("-1"); return 0; }
    for ( int i = 0; i < A.size(); ++ i ) if ( A[i] != B[(i + pos) % B.size()] ) { puts("-1"); return 0; } 
    int sum1 = pos * len, sum2 = (len - pos - 1) * len;
    if ( f.size() == 2 ) 
    {
        vector<int> p, q = f[0];
        while ( x ) { p.push_back(x); x = anc[x]; }
        while ( !p.empty() && p.back() != t ) p.pop_back(); 
        if ( !p.empty() && p.back() == t ) p.pop_back();
        vector<int> g = p; // reverse(q.begin(), q.end());
        if ( p.empty() ) goto Next ;

        while ( !p.empty() && !q.empty() && p.back() == q.back() ) { sum1 -= 2; p.pop_back(); q.pop_back(); }
        p = g; q = f[1]; // reverse(q.begin(), q.end());
        while ( !p.empty() && !q.empty() && p.back() == q.back() ) { sum2 -= 2; p.pop_back(); q.pop_back(); }
    }
Next : ;
    ans += min(sum1, sum2);
    if ( x1 > x2 ) swap(x1, x2);
    printf("%lld %lld %lld\n", x1, x2, ans);
    return 0;
}
