/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月28日 星期六 09时37分31秒
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

int n, m, k, D, T, a[maxn];

signed main()
{
    freopen("array.in", "r", stdin);
    freopen("array1.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld%lld%lld", &n, &m, &k, &D);
        REP(i, 1, m) scanf("%lld", &a[i]);
        sort(a + 1, a + m + 1);
        int sum = 0, ans = 0; REP(i, 1, m) sum += a[i];
        REP(i, 0, n)
        {
            if ( sum * i > D ) break ; 
            int ret = (m + k) * i, x = D - i * sum; 
            // if ( i == 3 ) cout << x << " " << ret << endl;
            REP(j, 1, m)
            {
                int y = min(n - i, x / a[j]);
                // if ( i == 3 ) cout << y << " ";
                ret += y; x -= a[j] * y;
            }
            // if ( ret == 1159 ) cerr << i << endl;
            // if ( i == 3 ) cout << endl << ret << endl;
            ans = max(ans, ret);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
