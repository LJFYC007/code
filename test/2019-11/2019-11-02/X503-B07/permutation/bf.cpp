/***************************************************************
	File name: permutation.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 08时45分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3010;

int T, n, k, a[maxn], ans;

inline int C(int n, int m)
{
    int ret = 1;
    REP(i, m + 1, n) ret = ret * i;
    REP(i, 1, n - m) ret = ret / i;
    return ret;
}

signed main()
{
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    REP(i, 1, 17) REP(j, 1, i) printf("%lld %lld %lld\n", i, j, C(i, j));
    return 0;
    scanf("%lld", &T); 
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &k); ans = 0;
        REP(i, 1, n) a[i] = i;
        do
        {
            int ret = 0;
            REP(i, 1, n) if ( a[i - 1] > a[i] || a[i + 1] > a[i] ) ++ ret;
            if ( ret >= k ) ++ ans;
        } while ( next_permutation(a + 1, a + n + 1) );
        printf("%lld %lld %lld\n", n, k, ans);
    }
    return 0;
}
