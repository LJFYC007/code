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
const int INF = 1e18;

int f[maxn], T, n, k, head, tail;
char s[maxn];
pii Q[maxn];

signed main()
{
    freopen("light.in", "r", stdin);
    freopen("light.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- )
    {
        scanf("%lld%lld", &n, &k);
        scanf("%s", s + 1);
        head = tail = 1; Q[head] = pii(0, INF);
        REP(i, 1, n)
        {
            f[i] = f[i - 1] + i;
            while ( head <= tail && Q[head].first < i - k ) ++ head;
            if ( s[i] == '1' )
            {
                int val = (i >= k + 1 ? f[i - k - 1] : 0);
                REP(j, 1, min(10ll, k)) if ( i - k - 1 + j >= 0 ) val = min(val, f[i - k - 1 + j]);
                val += i;
                while ( head <= tail && Q[tail].second >= val ) -- tail;
                Q[++ tail] = pii(i, val);
            }
            if ( head <= tail ) f[i] = min(f[i], Q[head].second);
        }
        printf("%lld\n", f[n]);
    }
    return 0;
}
