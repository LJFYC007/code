/***************************************************************
	File name: CF103D.cpp
	Author: ljfcnyali
	Create time: 2019年09月11日 星期三 21时41分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 300010;

int n, m, f[maxn], a[maxn], ans[maxn];
struct node
{
    int t, k, id;
    bool operator < (const node &a) const { return k < a.k; }
} q[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    int N = sqrt(n);
    scanf("%lld", &m);
    REP(i, 1, m) { scanf("%lld%lld", &q[i].t, &q[i].k); q[i].id = i; }
    sort(q + 1, q + m + 1);
    REP(i, 1, m)
    {
        if ( q[i].k > N ) 
        {
            for ( int j = q[i].t; j <= n; j += q[i].k ) ans[q[i].id] += a[j];
            continue ;
        }
        if ( q[i].k != q[i - 1].k)
        {
            REP(j, 1, n) f[j] = f[j - q[i].k] + a[j];
        }
        int x = n;
        while ( x % q[i].k != q[i].t % q[i].k ) -- x;
        // if ( q[i].k == 2 ) printf("%lld %lld\n", x, q[i].t - q[i].k);
        ans[q[i].id] = f[x] - f[q[i].t - q[i].k];
    }
    REP(i, 1, m) printf("%lld\n", ans[i]);
    return 0;
}
