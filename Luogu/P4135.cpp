/***************************************************************
	File name: P4135.cpp
	Author: ljfcnyali
	Create time: 2019年09月25日 星期三 11时31分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 510;
const int maxm = 100010;

int n, m, q, block, a[maxm], f[maxn][maxn], g[maxn][maxm], sum[maxm], ans;

inline void Solve1(int l, int r)
{
    ans = 0;
    REP(i, l, r)
    {
        ++ sum[a[i]];
        if ( sum[a[i]] % 2 == 0 ) ++ ans;
        else if ( sum[a[i]] > 2 ) -- ans;
    }
    REP(i, l, r) sum[a[i]] = 0;
}

inline void Solve2(int l, int r)
{
    int L = ((l - 1) / block + 1) * block + 1;
    int R = ((r - 1) / block) * block;
    ans = f[(L - 1) / block + 1][(R - 1) / block + 1];
    REP(i, l, L - 1) sum[i] = g[(R - 1) / block + 1][a[i]] - g[(L - 1) / block][a[i]];
    REP(i, R + 1, r) sum[i] = g[(R - 1) / block + 1][a[i]] - g[(L - 1) / block][a[i]];
    REP(i, l, L - 1)
    {   
        ++ sum[a[i]];
        if ( sum[a[i]] % 2 == 0 ) ++ ans;
        else if ( sum[a[i]] > 2 ) -- ans;
    }
    REP(i, R + 1, r)
    {   
        ++ sum[a[i]];
        if ( sum[a[i]] % 2 == 0 ) ++ ans;
        else if ( sum[a[i]] > 2 ) -- ans;
    }
    REP(i, l, L + 1) sum[a[i]] = 0; REP(i, R + 1, r) sum[a[i]] = 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q); block = sqrt(n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n)
    {
        ++ sum[a[i]];
        if ( i % block == 0 ) REP(j, 1, m) g[i / block][j] = sum[j];
    }
    if ( n % block != 0 ) REP(i, 1, m) g[(n - 1) / block + 1][i] = sum[i];
    for (int s = 1; s <= n; s += block ) 
    {
        mem(sum); ans = 0;
        REP(i, s, n)
        {
            ++ sum[a[i]];
            if ( sum[a[i]] % 2 == 0 ) ++ ans;
            else if ( sum[a[i]] > 2 ) -- ans;
            if ( i % block == 0 ) f[s / block + 1][i / block] = ans;
        }
        if ( n % block != 0 ) f[s / block + 1][(n - 1) / block + 1] = ans;
    }
    mem(sum);
    while ( q -- )
    {
        int l, r; scanf("%d%d", &l, &r);
        l = (l + ans) % n + 1; r = (r + ans) % n + 1;
        if ( l > r ) swap(l, r); if ( l == 0 ) l = 1;
        int L = (l - 1) / block + 1, R = (r - 1) / block + 1;
        if ( L == R || L + 1 == R ) Solve1(l, r);
        else Solve2(l, r);
        printf("%d\n", ans);
    }
    return 0;
}
