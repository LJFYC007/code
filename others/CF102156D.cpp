/***************************************************************
	File name: CF102156D.cpp
	Author: ljfcnyali
	Create time: 2020年11月25日 星期三 19时28分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 10010;
const int maxm = maxn * 60;
const int INF = 1e18;

int n, m, a[maxn], b[61][maxn], len[61], Begin[maxm], Next[maxm], To[maxm], e;
int c[61], id[61][maxn], dis[maxn], pre[maxn];
bool use[61];
queue<int> Q;

inline void Insert(int x)
{
    for ( int i = 60; i >= 0; -- i )
    {
        if ( !((x >> i) & 1) ) continue ;
        if ( !c[i] ) { c[i] = x; return ; }
        x ^= c[i];
    }
}

inline bool Check(int x)
{
    for ( int i = 60; i >= 0; -- i )
    {
        if ( !((x >> i) & 1) ) continue ;
        if ( !c[i] ) return true;
        x ^= c[i];
    }
    return false;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline vector<pii> Solve(vector<pii> p)
{
    e = 0; mem(Begin); mem(c); mem(use); mem(id); REP(i, 1, n) Insert(a[i]);
    for ( auto it : p ) { use[it.first] = true; Insert(b[it.first][it.second]); }
    int n1 = 0, n2 = 0, s = 1, t = 2;  
    for ( auto it : p ) id[it.first][it.second] = 2 + (++ n1);
    REP(i, 1, m) REP(j, 1, len[i])   
    {
        if ( id[i][j] ) continue ;
        ++ n2; id[i][j] = 2 + n1 + n2; 
        if ( Check(b[i][j]) ) add(s, id[i][j]);
        if ( !use[i] ) add(id[i][j], t); 
Next : ;
    }

    REP(o, 0, n1 - 1)
    {
        mem(c); mem(use); REP(i, 1, n) Insert(a[i]);
        for ( auto i : p ) if ( p[o] != i ) { Insert(b[i.first][i.second]); use[i.first] = true; }
        REP(i, 1, m) REP(j, 1, len[i]) 
        {
            if ( id[i][j] <= 2 + n1 ) continue ;
            if ( Check(b[i][j]) ) add(3 + o, id[i][j]);
            if ( !use[i] ) add(id[i][j], 3 + o);
        }
    }

    REP(i, 1, 2 + n1 + n2) dis[i] = INF;
    dis[s] = 1; Q.push(s);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( dis[v] > dis[u] + 1 ) { dis[v] = dis[u] + 1; pre[v] = u; Q.push(v); }
        }
    }
    int i = pre[t]; if ( dis[t] == INF ) return p;
    while ( i != s ) 
    {
        REP(x, 1, m) REP(y, 1, len[x]) if ( id[x][y] == i )
        {
            // cout << i << ", "; 
            if ( id[x][y] > n1 + 2 ) p.push_back(pii(x, y));
            else { for ( int it = 0; it < p.size(); ++ it ) if ( p[it] == pii(x, y) ) p.erase(p.begin() + it); }
            goto Finish ;
        }
Finish : ;
         i = pre[i];
    }
    // for ( auto it : p ) cout << it.first << " " << it.second << ";"; cout << endl;
    // fflush(stdout);
    return Solve(p);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n)
    {
        if ( !Check(a[i]) ) { puts("-1"); return 0; }
        Insert(a[i]);
    }
    scanf("%lld", &m); REP(i, 1, m) { scanf("%lld", &len[i]); REP(j, 1, len[i]) scanf("%lld", &b[i][j]); }
    vector<pii> a; a = Solve(a);
    if ( a.size() < m ) puts("-1");
    else { sort(a.begin(), a.end()); for ( auto it : a ) cout << b[it.first][it.second] << endl; }
    return 0;
}
