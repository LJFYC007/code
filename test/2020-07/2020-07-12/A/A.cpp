/***************************************************************
    File name: A.cpp
    Author: ljfcnyali
    Create time: 2020年07月12日 星期日 08时42分20秒
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
 
const int maxn = 2e5 + 10;
 
int n, m, type, ans, sum; 
bool vis[maxn];
pii f[maxn];
struct node { int x; pii t; node(int a = 0, pii b = pii(0, 0)) { x = a; t = b; } } ;
vector<node> p;
deque<pii> Q, Q1;
vector<pii> g;
 
inline int Find(int x) 
{ 
    if ( x == f[x].x ) return x;
    if ( !vis[x] ) { vis[x] = true; p.push_back(node(x, f[x])); }
    return f[x].x = Find(f[x].x);
}

inline void ReBuild()
{
    REP(i, 1, m) f[i] = pii(i, 1); g.clear();
    int Max = 200; sum = 0;
    while ( !Q.empty() && Max ) { -- Max; Q1.push_back(Q.front()); g.push_back(Q.front()); Q.pop_front(); }
    for ( auto it : Q ) 
    {
        int fx = Find(it.first), fy = Find(it.second);
        if ( fx == fy && f[fx].y ) { f[fx].y = 0; ++ sum; continue ; } 
        f[fy].x = fx;
        if ( f[fx].y != f[fy].y ) { f[fx].y = 0; ++ sum; continue ; }
        if ( f[fx].y == 1 ) { ++ sum; continue; }
    }
    for ( int i = (int)(g.size()) - 1; i >= 0; -- i ) Q.push_front(g[i]);
}

inline int Solve()
{
    for ( auto i : p ) vis[i.x] = false;
    p.clear(); int ret = 0;
    for ( auto it : Q1 ) 
    {
        int fx = Find(it.first), fy = Find(it.second);
        if ( !vis[fx] ) { vis[fx] = true; p.push_back(node(fx, f[fx])); }
        if ( !vis[fy] ) { vis[fy] = true; p.push_back(node(fy, f[fy])); }
        if ( fx == fy && f[fx].y ) { f[fx].y = 0; ++ ret; continue ; } 
        f[fy].x = fx; 
        if ( f[fx].y != f[fy].y ) { f[fx].y = 0; ++ ret; continue ; }
        if ( f[fx].y == 1 ) { ++ ret; continue; }
    }
    for ( auto i : p ) f[i.x] = i.t; 
    return ret;
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &type);
    ReBuild();
    REP(i, 1, m)
    {
        int op; scanf("%d", &op);
        if ( type == 1 ) op = (op + ans) % 2;
        if ( op == 0 ) 
        {
            if ( Q1.empty() ) ReBuild();
            Q.pop_front(); Q1.pop_front();
        }
        else
        {
            int a, b; scanf("%d%d", &a, &b);
            if ( type == 1 ) { a = (a + ans) % n + 1; b = (b + ans) % n + 1; }
            Q.push_back(pii(a, b));

            int fx = Find(a), fy = Find(b);
            if ( fx == fy && f[fx].y ) { f[fx].y = 0; ++ sum; } 
            else
            {
                f[fy].x = fx; 
                if ( f[fx].y != f[fy].y ) { f[fx].y = 0; ++ sum; }
                else if ( f[fx].y == 1 ) ++ sum;
            }
        }
        ans = sum + Solve();
        printf("%d\n", ans);
    }
    return 0;
}
