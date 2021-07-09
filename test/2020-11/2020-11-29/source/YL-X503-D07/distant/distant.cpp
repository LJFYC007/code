/***************************************************************
	File name: distant.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月29日 星期日 09时55分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define x first
#define y second
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;
const int maxm = 410;
const LL INF = 1e18;

int n, m, q, ans[maxn];
LL f[maxm][maxm];
vector<pii> Edge[maxn][2];
struct node 
{
    int x, y; LL dis;
    node ( int a = 0, int b = 0, LL c = 0 ) { x = a; y = b; dis = c; }
    bool operator < (const node &a) const { return dis > a.dis; }
} ;
priority_queue<node> Q;

signed main()
{
    freopen("distant.in", "r", stdin);
    freopen("distant.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, m) 
    { 
        int u, v, w, t; scanf("%d%d%d%d", &u, &v, &w, &t); 
        if ( t == 1 ) Edge[v][0].push_back(pii(u, w));
        else Edge[u][1].push_back(pii(v, w)); 
    }

    REP(i, 1, n) REP(j, 1, n) f[i][j] = INF;
    REP(i, 1, n) { f[i][i] = 0; Q.push(node(i, i, 0)); }
    while ( !Q.empty() ) 
    {
        node t = Q.top(); Q.pop();
        int x = t.x, y = t.y; if ( f[x][y] < t.dis ) continue ;
        REP(k, 1, n) 
        {
            if ( f[x][k] > f[x][y] + f[y][k] ) { f[x][k] = f[x][y] + f[y][k]; Q.push(node(x, k, f[x][k])); }
            if ( f[k][y] > f[k][x] + f[x][y] ) { f[k][y] = f[k][x] + f[x][y]; Q.push(node(k, y, f[k][y])); }
        }
        for ( auto a : Edge[x][0] ) for ( auto b : Edge[y][1] )
            if ( f[a.x][b.x] > f[x][y] + a.y + b.y )
            {
                f[a.x][b.x] = f[x][y] + a.y + b.y;
                Q.push(node(a.x, b.x, f[a.x][b.x]));
            }
    }

    REP(i, 1, q) { int s, t; scanf("%d%d", &s, &t); printf("%lld\n", f[s][t] == INF ? -1 : f[s][t] % Mod); }
    return 0;
}
