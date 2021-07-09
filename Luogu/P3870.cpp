/***************************************************************
    File name: P3870.cpp
    Author: ljfcnyali
    Create time: 2019年06月08日 星期六 09时56分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int a[maxn], p[maxn], f[maxn], n, m, block, sum[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    REP(i, 1, n) p[i] = (i - 1) / block + 1;
    REP(i, 1, m)
    {
        int opt, l, r; scanf("%d%d%d", &opt, &l, &r);
        if ( opt == 0 ) 
        {
            if ( p[l] == p[r] ) REP(j, l, r) a[j] = 1 - a[j];
            else
            {
                REP(j, l, block * p[l]) a[j] = 1 - a[j];
                REP(j, block * (p[r] - 1) + 1, r) a[j] = 1 - a[j];
            }
            REP(j, p[l] + 1, p[r] - 1) f[j] = 1 - f[j];
            sum[p[l]] = sum[p[r]] = 0;
            if ( p[l] == p[r] ) REP(j, l, r) sum[p[l]] += a[j];
            else
            {
                REP(j, block * (p[l] - 1) + 1, block * p[l]) sum[p[l]] += a[j];
                REP(j, block * (p[r] - 1) + 1, block * p[r]) sum[p[r]] += a[j];
            }
        }
        else
        {
            int ans = 0;
            if ( p[l] == p[r] ) 
            {
                REP(j, l, r) if ( f[p[l]] ) ans += 1 - a[j]; else ans += a[j];
                printf("%d\n", ans);
                continue ;
            }
            REP(j, l, block * p[l]) if ( f[p[l]] ) ans += 1 - a[j]; else ans += a[j];
            REP(j, block * (p[r] - 1) + 1, r) if ( f[p[r]] ) ans += 1 - a[j]; else ans += a[j];
            REP(j, p[l] + 1, p[r] - 1) if ( f[j] ) ans += block - sum[j]; else ans += sum[j];
            printf("%d\n", ans);
        }
    }
    return 0;
}
