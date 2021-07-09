/***************************************************************
	File name: cake.cpp
	Author: ljfcnyali
	Create time: 2019年11月12日 星期二 08时57分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;

int T, n, m, a[maxn], b[maxn], N, M, ans, num;

signed main()
{
    freopen("cake.in", "r", stdin);
    freopen("cake.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld%lld%lld", &n, &m, &N, &M);
        REP(i, 1, N) scanf("%lld", &a[i]);
        REP(i, 1, M) scanf("%lld", &b[i]);
        sort(a + 1, a + N + 1);
        sort(b + 1, b + M + 1);
        ans = 1; num = 0;
        bool flag = false;
        REP(i, 1, M) 
        {
            ++ ans;
            if ( abs(b[i]) >= m ) { ++ num; continue ; }
            if ( !flag ) flag = true;
            else ++ ans;
        }
        REP(i, 1, N)
            if ( abs(a[i]) >= m ) ans += M + 1;
            else ans += num + 2;
        printf("%lld\n", ans);
    }
    return 0;
}

