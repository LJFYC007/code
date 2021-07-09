/***************************************************************
	File name: and.cpp
	Author: ljfcnyali
	Create time: 2020年07月08日 星期三 10时52分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;
const int w = 1 << 8;

int n, m, g[w], len[w][w];
int *a[w][w], *f1[w][w], *f2[w][w];
struct node { int op, x, l, r, val; } Q[maxn];

inline int Find(int x, int y, int z) { return lower_bound(a[x][y] + 1, a[x][y] + len[x][y] + 1, z) - a[x][y]; }

inline int lowbit(int x) { return x & -x; }

inline void add(int x, int y, int pos, int val1, int val2)
{
    int n = len[x][y];
    for ( int i = pos; i <= n; i += lowbit(i) ) 
    {
        f1[x][y][i] = f1[x][y][i] + val1 >= Mod ? f1[x][y][i] + val1 - Mod : f1[x][y][i] + val1;
        f2[x][y][i] = f2[x][y][i] + val2 >= Mod ? f2[x][y][i] + val2 - Mod : f2[x][y][i] + val2;
    }
}

inline int get(int x, int y, int pos, int a)
{
    return 0;
    int ret1 = 0, ret2 = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) 
    {
        ret1 = ret1 + f1[x][y][i] >= Mod ? ret1 + f1[x][y][i] - Mod : ret1 + f1[x][y][i];
        ret2 = ret2 + f2[x][y][i] >= Mod ? ret2 + f2[x][y][i] - Mod : ret2 + f2[x][y][i];
    }
    return ((LL)a * ret1 - ret2 + Mod) % Mod;
}

inline void Modify(int x, int y, int a, int b, int val)
{
    int l = Find(x, y, a), r = Find(x, y, b);
    add(x, y, l, val, (LL)val * a % Mod);
    add(x, y, r, Mod - val, (LL)(Mod - val) * b % Mod);
}

inline int Query(int x, int y, int a) { return get(x, y, Find(x, y, a), a + 1); }

inline int count(int x)
{
    int sum = 1;
    REP(i, 0, 7) if ( (x >> i) & 1 ) sum <<= 1;
    return sum;
}

signed main()
{
    freopen("and.in", "r", stdin);
    freopen("and.out", "w", stdout);
    scanf("%d%d", &n, &m); -- n;
    REP(i, 0, w - 1) g[i] = count(i);
    REP(i, 1, m)
    {
        scanf("%d%d%d%d", &Q[i].op, &Q[i].x, &Q[i].l, &Q[i].r);
        Q[i].x ^= n;
        if ( Q[i].op == 0 ) 
        {
            scanf("%d", &Q[i].val);
            REP(j, 0, w - 1) len[Q[i].x >> 8][j] += 2;
        }
        else REP(j, 0, w - 1) len[j][Q[i].x & w - 1] += 2;
    }

    REP(i, 0, w - 1) REP(j, 0, w - 1) { a[i][j] = new int[len[i][j] + 1]; len[i][j] = 0; }
    REP(i, 1, m)
        if ( Q[i].op == 0 ) 
            REP(j, 0, w - 1)
            {
                a[Q[i].x >> 8][j][++ len[Q[i].x >> 8][j]] = Q[i].r + 1;
                a[Q[i].x >> 8][j][++ len[Q[i].x >> 8][j]] = Q[i].l;
            }
        else
            REP(j, 0, w - 1)
            {
                a[j][Q[i].x & w - 1][++ len[j][Q[i].x & w - 1]] = Q[i].r;
                a[j][Q[i].x & w - 1][++ len[j][Q[i].x & w - 1]] = Q[i].l - 1;
            }

    REP(i, 0, w - 1) REP(j, 0, w - 1)
    {
        if ( !len[i][j] ) continue ;
        sort(a[i][j] + 1, a[i][j] + len[i][j] + 1);
        int tot = unique(a[i][j] + 1, a[i][j] + len[i][j] + 1) - a[i][j] - 1;
        len[i][j] = tot;
        f1[i][j] = new int[len[i][j] + 1]; f2[i][j] = new int[len[i][j] + 1];
    }

    REP(i, 1, m) if ( Q[i].op == 0 ) 
        REP(j, 0, w - 1)
            Modify(Q[i].x >> 8, j, Q[i].l, Q[i].r + 1, (LL)Q[i].val * g[Q[i].x & j] % Mod);
    else
    {
        int ans = 0;
        REP(j, 0, w - 1)
            ans = (ans + (Query(j, Q[i].x & w - 1, Q[i].r) - Query(j, Q[i].x & w - 1, Q[i].l - 1) + Mod) * (LL)g[(Q[i].x >> 8) & j]) % Mod;
        printf("%d\n", ans);
    }
    return 0;
}
