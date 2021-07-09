/***************************************************************
	File name: factory.cpp
	Author: ljfcnyali
	Create time: 2019年09月25日 星期三 09时57分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 510;

int n, p, tot1, tot2, f[maxn][maxn], ans;
struct node
{
    int s, t;
    bool operator < (const node &a) const { return s < a.s || (s == a.s && t < a.t); }
} a[maxn], b[maxn], c[maxn];

inline int cmp(node a, node b) { return a.t - a.s > b.t - b.s; }

inline int cmp2(node a, node b) { return a.s == b.s ? a.t > b.t : a.s < b.s; }

int main()
{
    freopen("factory.in", "r", stdin);
    freopen("factory.out", "w", stdout);
    scanf("%d%d", &n, &p);
    REP(i, 1, n) scanf("%d%d", &c[i].s, &c[i].t);
    sort(c + 1, c + n + 1, cmp2);
    REP(i, 1, n)
    {
        REP(j, i + 1, n)
            if ( c[i].s <= c[j].s && c[j].t <= c[i].t )
            {
                b[++ tot2] = c[i]; goto Next;
            }
        a[++ tot1] = c[i];
Next : ;
    }
    sort(a + 1, a + tot1 + 1);
    sort(b + 1, b + tot2 + 1, cmp);
    memset(f, -0x3f, sizeof(f)); f[0][0] = 0;
    REP(j, 1, p)
        REP(i, 1, tot1)
            REP(k, 0, i - 1)
                if ( a[k + 1].t > a[i].s && f[k][j - 1] != -0x3f3f3f3f ) 
                    f[i][j] = max(f[i][j], f[k][j - 1] + a[k + 1].t - a[i].s);
    REP(x, 0, p)
    {
        int sum = f[tot1][x], y = p - x;
        // cerr << x << " " << sum << endl;
        if ( y > tot2 ) continue ;
        REP(i, 1, y) sum += b[i].t - b[i].s;
        // cerr << sum << endl;
        ans = max(ans, sum);
    }
    printf("%d\n", ans);
    return 0;
}
