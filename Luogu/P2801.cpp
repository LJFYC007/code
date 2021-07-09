/***************************************************************
	File name: P2801.cpp
	Author: ljfcnyali
	Create time: 2019年06月16日 星期日 16时00分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2000010;

LL a[maxn], p[maxn], f[1010][1010], block, n, m, num, sum[1010];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    block = sqrt(n); num = n - block * block;
    REP(i, 0, n + block) a[i] = -0x3f3f3f3f;
    REP(i, 1, n) 
    { 
        scanf("%lld", &a[i]); 
        p[i] = (i - 1) / block + 1; 
        f[p[i]][i - (p[i] - 1) * block] = a[i];
    }
    REP(i, 1, block) sort(f[i] + 1, f[i] + block + 1);
    sort(f[block + 1] + 1, f[block + 1] + block + 1);
    REP(i, 1, m)
    {
        getchar(); 
        getchar(); char c = getchar();
        LL l, r, w; scanf("%lld%lld%lld", &l, &r, &w);
        if ( c == 'A' ) 
        {
            LL ans = 0;
            if ( p[l] == p[r] ) 
            {
                REP(j, l, r) if ( a[j] + sum[p[l]] >= w ) ++ ans;
                printf("%lld\n", ans); continue ;
            }
            REP(j, l, p[l] * block) if ( a[j] + sum[p[l]] >= w ) ++ ans;
            REP(j, (p[r] - 1) * block + 1, r) if ( a[j] + sum[p[r]] >= w ) ++ ans;
            REP(j, p[l] + 1, p[r] - 1)
            {
                LL L = 1, R = block, s = block + 1;
                while ( L <= R ) 
                {
                    LL Mid = L + R >> 1;
                    if ( f[j][Mid] + sum[j] >= w ) { R = Mid - 1; s = Mid; }
                    else L = Mid + 1;
                }
                ans += block - s + 1;
            }
            printf("%lld\n", ans);
        }
        else
        {
            if ( p[l] == p[r] ) 
            {
                REP(j, l, r) a[j] += w;
                LL x = (p[l] - 1) * block;
                REP(j, 1, block) f[p[l]][j] = a[x + j];
                sort(f[p[l]] + 1, f[p[l]] + block + 1);
                continue ;
            }
            REP(j, l, p[l] * block) a[j] += w;
            REP(j, (p[r] - 1) * block + 1, r) a[j] += w;
            LL x = (p[l] - 1) * block;
            REP(j, 1, block) f[p[l]][j] = a[x + j];
            x = (p[r] - 1) * block;
            REP(j, 1, block) f[p[r]][j] = a[x + j];
            sort(f[p[l]] + 1, f[p[l]] + block + 1);
            sort(f[p[r]] + 1, f[p[r]] + block + 1);
            REP(j, p[l] + 1, p[r] - 1) sum[j] += w;
        }
    }
    return 0;
}
