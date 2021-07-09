/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年11月06日 星期三 18时28分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 200010;
const int N = (1 << 17) - 1;

int n, h[maxn], m, block, f[maxn], a[maxn], b[maxn], p[maxn], num, tot, ans[maxn];

signed main()
{
    freopen("monster.in", "r", stdin);
    freopen("monster.out", "w", stdout);
    scanf("%lld", &n); num = n;
    REP(i, 0, n - 1) scanf("%lld", &h[i]);
    scanf("%lld", &m);
    block = sqrt(m);
    for ( int o = 1; o <= m; o += block ) 
    {
        int L = o, R = min(o + block - 1, m);
        // printf("%lld %lld\n", L, R);
        mem(p);
        REP(i, L, R) { scanf("%lld%lld", &a[i], &b[i]); a[i] &= N; p[a[i]] += b[i]; }
        REP(j, 0, 17) for ( int i = N; i >= 0; -- i ) if ( i & (1 << j) ) p[i & ~(1 << j)] += p[i];
        tot = 0;
        REP(i, 0, n - 1) 
        { 
            if ( h[i] > 0 && h[i] <= p[i] ) f[++ tot] = i;
            else h[i] -= p[i];
        }
        REP(i, 1, tot) 
        {
            bool flag = false;
            REP(j, L, R) 
            { 
                h[f[i]] -= ((a[j] & f[i]) == f[i]) ? b[j] : 0; 
                if ( h[f[i]] <= 0 && !flag ) { ++ ans[j]; flag = true; }
            }
        }
        REP(j, L, R) { num -= ans[j]; printf("%lld\n", num); }
    }
    return 0;
}
