/***************************************************************
	File name: hhcs.cpp
	Author: ljfcnyali
	Create time: 2020年05月21日 星期四 17时13分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define y1 hhakioi_hhcs_cslbn
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, l[maxn], r[maxn], ans, p[maxn];

signed main()
{
    freopen("hhcs.in", "r", stdin);
    freopen("hhcs.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld%lld", &l[i], &r[i]);
    REP(i, 0, (1 << n) - 1)
    {
        int sum = 1, num = 0;
        REP(j, 0, n - 1) 
            if ( (i >> j) & 1 ) 
            {
                p[j] = l[j + 1] - 1;
                ++ num;
            }
            else p[j] = r[j + 1];
        sort(p, p + n);
        REP(j, 0, n - 1) sum = sum * max(0ll, p[j] - j + 1) % Mod;
        ans = (ans + sum * (num & 1 ? -1 : 1)) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
