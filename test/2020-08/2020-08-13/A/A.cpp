/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年08月13日 星期四 09时55分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define y1 crazyalicsbn
typedef long long LL;

const int maxn = 1e3 + 10;
const int maxm = 1e6 + 10;

int n, m, k, q, a[maxn][maxn], id[maxn][maxn], f[maxm], Max[maxm];
bool ans[maxm];
struct node { int x, y, id; node(int a = 0, int b = 0, int c = 0) { x = a; y = b; id = c; } } ;
vector<node> Q[maxn];
vector<pii> Edge[maxn];
char s[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline int Solve(int x1, int y1, int x2, int y2)
{
    if ( x1 < 1 || y1 < 1 ) return -1;
    return a[x2][y2] + a[x1 - 1][y1 - 1] - a[x1 - 1][y2] - a[x2][y1 - 1];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, n)
    {
        scanf("%s", s + 1);
        REP(j, 1, m) { a[i][j] = s[j] - '0'; id[i][j] = ++ k; } 
    }
    REP(i, 1, q) 
    { 
        int x1, y1, x2, y2, w; scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &w);
        Q[w].push_back(node(id[x1][y1], id[x2][y2], i));
    }
    
    REP(i, 1, n) REP(j, 1, m) a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    REP(i, 1, n) REP(j, 1, m)
    {
        int l = 1, r = min(n, m), pos = 0;
        while ( l <= r ) 
        {
            int Mid = (l + r) / 2;
            if ( Solve(i - Mid + 1, j - Mid, i, j) == 0 ) { l = Mid + 1; pos = Mid; }
            else r = Mid - 1;
        }
        Edge[pos].push_back(pii(id[i][j], id[i][j - 1]));
       
        l = 1; r = min(n, m); pos = 0;
        while ( l <= r ) 
        {
            int Mid = (l + r) / 2;
            if ( Solve(i - Mid, j - Mid + 1, i, j) == 0 ) { l = Mid + 1; pos = Mid; }
            else r = Mid - 1;
        }
        Edge[pos].push_back(pii(id[i][j], id[i - 1][j]));

        l = 1; r = min(n, m); pos = 0;
        while ( l <= r ) 
        {
            int Mid = (l + r) / 2;
            if ( Solve(i - Mid + 1, j - Mid + 1, i, j) == 0 ) { l = Mid + 1; pos = Mid; }
            else r = Mid - 1;
        }
        Max[id[i][j]] = pos;
    }

    REP(i, 1, k) f[i] = i;
    for ( int i = min(n, m); i >= 1; -- i ) 
    {
        for ( auto j : Edge[i] ) 
        {
            int fx = find(j.first), fy = find(j.second);
            if ( f[fx] != fy ) f[fx] = fy;
        }
        for ( auto j : Q[i] ) 
        {
            int fx = find(j.x), fy = find(j.y);
            if ( j.x == j.y ) ans[j.id] = (Max[j.x] >= i);
            else ans[j.id] = (fx == fy);
        }
    }
    REP(i, 1, q) if ( ans[i] ) puts("Yes"); else puts("No");
    return 0;
}
