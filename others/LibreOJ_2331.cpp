/***************************************************************
	File name: LibreOJ_2331.cpp
	Author: ljfcnyali
	Create time: 2020年07月20日 星期一 09时21分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long 
typedef long long LL;

const int maxn = 1010;

int T, n, m, A, tot, ans, len[maxn], lim[maxn], f[maxn][maxn];
struct node { int l, r, m; } a[maxn];
vector<int> p;
map<int, int> Map;
bool vis[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        mem(vis); mem(lim); p.clear(); Map.clear(); 
        tot = 0; p.push_back(1); ans = 1;
        scanf("%lld%lld%lld", &n, &m, &A);
        REP(i, 1, m) 
        { 
            scanf("%lld%lld%lld", &a[i].l, &a[i].r, &a[i].m); ++ a[i].r; 
            p.push_back(a[i].l); p.push_back(a[i].r);
        }
        sort(p.begin(), p.end());
        REP(i, 0, p.size() - 1) 
        {
            if ( i == 0 || p[i] != p[i - 1] ) Map[p[i]] = ++ tot;
            len[tot] = p[i + 1] - p[i];
        }
        REP(i, 1, m) { a[i].l = Map[a[i].l]; a[i].r = Map[a[i].r]; }
        sort(a + 1, a + m + 1, [](node x, node y) { return x.m < y.m; });
        for ( int l = 1, r; l <= m; l = r + 1 )
        {
            r = l; while ( a[r + 1].m == a[l].m ) ++ r;
            p.clear();
            REP(i, l, r) REP(j, a[i].l, a[i].r - 1) if ( !vis[j] ) { vis[j] = true; p.push_back(j); }
            for ( auto i : p ) REP(j, l, r) if ( a[j].l <= i && i < a[j].r ) lim[i] = max(lim[i], a[j].l);
            f[p[0]][p[0]] = 
            for ( int i = 1; i < p.size(); ++ i ) 
            {
            }
        }
    }
    return 0;
}
