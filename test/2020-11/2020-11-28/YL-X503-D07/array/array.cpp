/***************************************************************
	File name: array.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月28日 星期六 08时25分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int T, n, m, k, D, a[maxn], ans;

signed main()
{
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
    scanf("%lld", &T);
    REP(o, 1, T)
    // while ( T -- ) 
    {
        scanf("%lld%lld%lld%lld", &n, &m, &k, &D);
        REP(i, 1, m) scanf("%lld", &a[i]);
        
        /*
        if ( o == 2440 ) 
        {
            cout << n << " " << m << " " << k << " " << D << endl;
            REP(i, 1, m) cout << a[i] << " "; cout << endl;
        }
        continue ;
        */

        sort(a + 1, a + m + 1); ans = 0;

        // REP(i, 1, m) cout << a[i] << " "; cout << endl;
        int sum = 0, val = 0;
        REP(i, 1, m) val += a[i]; a[m + 1] = D + 1;
        REP(i, 0, m)
        {
            if ( sum > D ) break ; 
            int ret, x, y = 0;
            ret = n * i; x = D - sum; 
            if ( val > 0 ) y = min(n, x / val);
            ret += (m - i + k) * y; x -= y * val;
            // if ( i == 0 ) cerr << y << " " << ret << endl;
            ret += min(n - y, x / a[i + 1]); 
            ans = max(ans, ret);

            ret = n * i; x = D - sum;
            y = min(n, x / a[i + 1]);
            ret += y; x -= y * a[i + 1];
            if ( val - a[i + 1] > 0 ) ret += (m - i - 1 + k) * min(n, x / (val - a[i + 1]));
            ans = max(ans, ret);

            if ( val > 0 && val > a[i + 1] ) 
            {
                int num = min(n, 1 + x / (val - a[i + 1]));
                ret = n * i; x = D - sum;
                x -= num * val;
                // int num = min(n, x / val + 1);
                // if ( i == 0 ) cout << num << endl;
                if ( x >= 0 ) 
                {
                    ret += num * (m - i + k); 
                    ret += min(n - num, x / a[i + 1]);
                    ans = max(ans, ret);
                }
            }

            val -= a[i + 1];
            sum += a[i + 1] * n;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
