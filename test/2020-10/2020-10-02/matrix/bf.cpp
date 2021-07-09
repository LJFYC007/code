/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 10时08分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, m, l[maxn], r[maxn], f[1 << 25], g[1 << 25];

signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix1.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld%lld", &l[i], &r[i]);
    f[0] = 1;
    REP(i, 1, n) 
    {
        REP(j, 0, (1 << m) - 1)
        {
            if ( !f[j] ) continue ;
            REP(x, 1, l[i]) 
            {
                if ( (j >> x - 1) & 1 ) continue ;
                REP(y, r[i], m)
                {
                    if ( (j >> y - 1) & 1 ) continue ;
                    g[j | (1 << x - 1) | (1 << y - 1)] += f[j];
                }
            }
        }
        REP(j, 0, (1 << m) - 1) { f[j] = g[j]; g[j] = 0; }
    }
    int ans = 0;
    REP(i, 0, (1 << m) - 1) ans = (ans + f[i]) % Mod;
    printf("%lld\n", ans);
    return 0;
}
