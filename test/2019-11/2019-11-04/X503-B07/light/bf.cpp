/***************************************************************
	File name: light.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 09时40分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5000010;

int f[maxn], T, n, k, head, tail;
char s[maxn];

signed main()
{
    freopen("light.in", "r", stdin);
    freopen("light1.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- )
    {
        scanf("%lld%lld", &n, &k);
        scanf("%s", s + 1);
        REP(i, 1, n)
        {
            f[i] = f[i - 1] + i;
            REP(j, max(0ll, i - k), i) if ( s[j] == '1' ) f[i] = min(f[i], (j >= k + 1 ? f[j - k - 1] : 0) + j);
        }
        printf("%lld\n", f[n]);
    }
    return 0;
}
