/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年07月27日 星期一 09时45分05秒
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

const int maxn = 1511;
const int INF = 0x3f3f3f3f;

int n, m, k, l, p[11], ans = INF, f[maxn][20010];
bool vis[maxn][20010];
pii a[maxn];
struct node 
{ 
    int x, st;
    node(int a = 0, int b = 0) { x = a; st = b; }
    bool operator < (const node &a) const { return f[x][st] > f[a.x][a.st]; }
};
struct Node 
{
    int x, st; char pos;
    Node(int a = 0, int b = 0, char c = 0) { x = a; st = b; pos = c; }
} g[maxn][20010];
priority_queue<node> Q;

inline int Get(pii x, pii y) { return max(abs(x.x - y.x), abs(x.y - y.y)); }

inline void Modify(Node u, node x, int t)
{
    if ( f[x.x][x.st] > t ) 
    {
        f[x.x][x.st] = t; g[x.x][x.st] = u;
        if ( !vis[x.x][x.st] ) { vis[x.x][x.st] = true; Q.push(x); }
    }
}

inline vector<int> Find(node x)
{
    if ( f[x.x][x.st] == 0 ) 
    {
        vector<int> p; p.clear();
        REP(i, 1, k) p.push_back(i);
        return p;
    }
    Node u = g[x.x][x.st];
    vector<int> p = Find(node(u.x, u.st));
    if ( u.x == x.x ) return p;
    if ( u.pos == 0 ) 
    {
        int pos = p.front(); p.erase(p.begin()); p.push_back(pos);
        printf("%d %d\n", pos, f[x.x][x.st]);
    }
    else 
    {
        int pos = p.size() - u.pos, T = p[pos]; p.erase(p.begin() + pos);
        pos = T; p.push_back(pos);
        printf("%d %d\n", pos, f[x.x][x.st]);
    }
    // for ( auto i : p ) printf("%d ", i); puts("");
    // puts("");
    return p;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &k, &l);
    p[0] = 1; REP(i, 1, 10) p[i] = p[i - 1] * 3;
    int b = max(n, m) - 1, x = 1; l += b;
    for ( int i = b; i >= 1; -- i ) { a[i] = pii(x, x); -- x; }
    REP(i, b + 1, l) scanf("%d%d", &a[i].x, &a[i].y);
    int val = 0; REP(j, b - k + 1, b) val += 2 * p[j - 1];
    memset(f, 0x3f, sizeof(f)); f[b][val] = 0; Q.push(node(b, val));      
    node las;
    while ( !Q.empty() ) 
    {
        node v, u = Q.top(); Q.pop();
        if ( f[u.x][u.st] > ans ) continue ;
        if ( u.x == l ) { ans = min(ans, f[u.x][u.st]); las = u; break ; }
        v = node(u.x, u.st / 3); Modify(Node(u.x, u.st, 0), v, f[u.x][u.st] + 1);

        int pos = u.x + 1, num = 0;
        for ( int i = b; i >= 1; -- i ) 
        {
            if ( (u.st / p[i - 1]) % 3 >= 1 ) -- pos;
            if ( (u.st / p[i - 1]) % 3 != 2 ) continue ;
            ++ num; int t = Get(a[u.x + 1], a[pos]);
            if ( t > b - i ) continue ;
            int x = (u.st - p[i - 1]) / 3 + 2 * p[b - 1];
            v = node(u.x + 1, x); Modify(Node(u.x, u.st, num), v, f[u.x][u.st] + 1);
        }
        if ( num < k && f[u.x][u.st] >= b ) 
        {
            v = node(u.x + 1, u.st / 3 + 2 * p[b - 1]);
            Modify(Node(u.x, u.st, 0), v, f[u.x][u.st] + 1);
        }
    }
    printf("%d\n", ans);
    Find(las);
    return 0;
}
