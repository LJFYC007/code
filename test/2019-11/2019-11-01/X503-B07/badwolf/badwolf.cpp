/***************************************************************
	File name: badwolf.cpp
	Author: ljfcnyali
	Create time: 2019年11月01日 星期五 09时59分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first 
#define y second
#define int unsigned long long

const int maxn = 20;
const int maxm = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, m, a[maxn][maxn], e[maxn][maxn], tot;
set<pii> f[maxm], ans;
map<int, int> Map;

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline void Modify(set<pii> &g, set<pii> &t, int x, int y, bool opt)
{
    if ( t.begin() -> first == -1 ) t.clear();
    for ( auto i : t )
    {
        int cnt = i.x + (opt ? e[x][y] : 0); if ( cnt > m ) continue ;
        auto it = g.lower_bound(pii(cnt, 0));
        if ( it != g.end() && it -> x == cnt ) 
        {
            int l = (it -> y + i.y * (opt ? a[x][y] : 1)) % Mod;
            g.erase(it); g.insert(pii(cnt, l));
        }
        else g.insert(pii(cnt, i.y * (opt ? a[x][y] : 1) % Mod));
    }
}

inline set<pii> DFS(int x, int y, int ret, int sum, bool flag1, bool flag2);

inline set<pii> Get(int x, int y, int ret, int sum, bool flag1, bool flag2, bool opt)
{
    if ( y < m ) return DFS(x, y + 1, ret, sum + opt, flag1 | (opt ? x == 1 : 0), flag2 | (opt ? y == 1 : 0));
    else return DFS(x + 1, 1, ret, sum + opt, flag1 | (opt ? x == 1 : 0), flag2 | (opt ? y == 1 : 0));
}

int cloc;

inline set<pii> DFS(int x, int y, int ret, int sum, bool flag1, bool flag2)
{
    ++ cloc; if ( cloc > 20 ) exit(0);
    int s = ((ret * n * n + x * n + y) * n + sum) * 4 + 2 * flag1 + flag2;
    set<pii> g, t; g.clear();
    printf("%llu %llu %llu %llu %llu %llu\n", x, y, ret, sum, flag1, flag2);
    if ( Map.count(s) ) 
    { 
        for ( auto i : f[Map[s]] ) if ( i.x + e[x][y] <= m ) g.insert(pii(i.x + e[x][y], i.y * a[x][y] % Mod));
        return g; 
    }
    if ( x == n + 1 || sum > n ) 
    {
        if ( !flag1 || !flag2 || sum != n ) g.insert(pii(-1, -1)); 
        else g.insert(pii(0, 0));
        return g;
    }

    int num = ret, h[maxn], p[maxn]; bool use[maxn]; mem(use); 
    REP(i, 1, n) { h[i] = num % 6; num /= 6; use[h[i]] = true; }
    int left = h[y - 1], up = h[y];
    
    if ( left == up && left ) 
    {
        t = Get(x, y, ret, sum, flag1, flag2, true);
        Modify(g, t, x, y, true);
        REP(i, 1, n) p[i] = h[i]; p[y] = 0;
        num = 0; for ( int i = n; i >= 1; -- i ) num = num * 6 + p[i]; 
        t = Get(x, y, num, sum, flag1, flag2, false);
        Modify(g, t, x, y, false);
    }

    if ( left == up ) 
    { 
        t = Get(x, y, ret, sum, flag1, flag2, false); 
        Modify(g, t, x, y, false);
        REP(i, 1, n) p[i] = h[i]; REP(i, 1, 6) if ( !use[i] ) { p[y] = i; break ; } 
        num = 0; for ( int i = n; i >= 1; -- i ) num = num * 6 + p[i]; 
        t = Get(x, y, num, sum, flag1, flag2, true);
        Modify(g, t, x, y, true);
    }

    if ( left && !up )
    {
        t = Get(x, y, ret, sum, flag1, flag2, false); 
        Modify(g, t, x, y, false);
        REP(i, 1, n) p[i] = h[i]; p[y] = p[y - 1];
        num = 0; for ( int i = n; i >= 1; -- i ) num = num * 6 + p[i]; 
        t = Get(x, y, num, sum, flag1, flag2, true);
        Modify(g, t, x, y, true);
    }

    if ( !left && up ) 
    {
        t = Get(x, y, ret, sum, flag1, flag2, true);
        Modify(g, t, x, y, true);
        REP(i, 1, n) p[i] = h[i]; p[y] = 0;
        num = 0; for ( int i = n; i >= 1; -- i ) num = num * 6 + p[i];
        t = Get(x, y, num, sum, flag1, flag2, false);
        Modify(g, t, x, y, false);
    }

    if ( left && up && left != up ) 
    {
        REP(i, 1, n) p[i] = h[i]; p[y] = 0;
        num = 0; for ( int i = n; i >= 1; -- i ) num = num * 6 + p[i];
        t = Get(x, y, num, sum, flag1, flag2, false);
        Modify(g, t, x, y, false);
        REP(i, 1, n) { p[i] = h[i]; if ( p[i] == h[y - 1] ) p[i] = h[y]; }
        num = 0; for ( int i = n; i >= 1; -- i ) num = num * 6 + p[i];
        t = Get(x, y, num, sum, flag1, flag2, true);
        Modify(g, t, x, y, true);
    }
    Map[s] = ++ tot; f[tot] = g;
    return g;
}

signed main()
{
    freopen("badwolf.in", "r", stdin);
    freopen("badwolf.out", "w", stdout);
    scanf("%llu%llu", &n, &m);
    REP(i, 1, n) REP(j, 1, n) { read(a[i][j]); read(e[i][j]); }
    ans = DFS(1, 1, 0, 0, 0, 0);
    REP(i, 0, m)
    {
        if ( ans.begin() -> first == i ) { printf("%llu ", ans.begin() -> second); ans.erase(ans.begin()); }
        else printf("0 ");
    }
    puts("");
    return 0;
}
