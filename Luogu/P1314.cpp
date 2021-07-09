/***************************************************************
	File name: P1314.cpp
	Author: ljfcnyali
	Create time: 2019年06月09日 星期日 16时52分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

LL sumv[maxn], sumw[maxn], n, m, S;
LL v[maxn], w[maxn], ans, L[maxn], R[maxn];

inline LL check(LL W)
{
    REP(i, 1, n)
    {
        if ( w[i] >= W ) sumw[i] = sumw[i - 1] + 1;
        else sumw[i] = sumw[i - 1];
        if ( w[i] >= W ) sumv[i] = sumv[i - 1] + v[i];
        else sumv[i] = sumv[i - 1];
    }
    LL sum = 0;
    REP(i, 1, m)
    {
        LL x = sumw[R[i]] - sumw[L[i] - 1];
        LL y = sumv[R[i]] - sumv[L[i] - 1];
        sum += x * y;
    }
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &S);
    ans = S;
    LL l = 0, r = 0;
    REP(i, 1, n) { scanf("%lld%lld", &w[i], &v[i]); r = max(r, w[i]); }
    REP(i, 1, m) scanf("%lld%lld", &L[i], &R[i]);
//    int cnt = 0;
    while ( l <= r ) 
    {
//        cerr << l << " " << r << endl;
//        ++ cnt; if ( cnt > 10 ) return 0;
        LL Mid = l + r >> 1;
        LL Y = check(Mid);
        ans = min(ans, abs(S - Y));
        if ( Y == S ) { printf("0\n"); return 0; }
        if ( Y < S ) r = Mid - 1;
        else l = Mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
