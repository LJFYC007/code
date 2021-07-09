/***************************************************************
	File name: u.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 08时31分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e3 + 10;

int n, q, c[maxn][maxn], ans, a[maxn], b[maxn];
struct node 
{ 
    int r, c, l, s; 
    node ( int x = 0, int y = 0, int z = 0, int w = 0 ) { r = x; c = y; l = z; s = w; }
} ;
vector<node> Q[maxn];

namespace Fucku
{
    const int Delta = 1e3;
    const int N = maxn - 10;

    inline int lowbit(int x) { return x & -x; }
    
    inline void Modify(int l, int r, int x, int val)
    {
        x += Delta;
        for ( int i = l; i <= N; i += lowbit(i) ) c[i][x] += val;
        for ( int i = r + 1; i <= N; i += lowbit(i) ) c[i][x] -= val;
    }

    inline int Query(int x, int y)
    {
        y += Delta; int ret = 0;
        for ( int i = x; i > 0; i -= lowbit(i) ) ret += c[i][y];
        return ret;
    }
}

signed main()
{
    freopen("u.in", "r", stdin);
    freopen("u.out", "w", stdout);
    scanf("%lld%lld", &n, &q);
    REP(i, 1, q) { int r, c, l, s; scanf("%lld%lld%lld%lld", &r, &c, &l, &s); Q[c].push_back(node(r, c, l, s)); }
    REP(i, 1, n)
    {
        mem(b);
        for ( auto it : Q[i] )
        {
            b[it.r] += it.s; if ( it.r + it.l <= n ) b[it.r + it.l] -= it.s;
            Fucku :: Modify(it.r, it.r + it.l - 1, it.r - it.c - 1, -it.s);
        }
        REP(j, 1, n) { b[j] += b[j - 1]; a[j] += b[j] + Fucku :: Query(j, j - i); }
        REP(j, 1, n) ans ^= a[j];
    }
    printf("%lld\n", ans);
    return 0;
}
