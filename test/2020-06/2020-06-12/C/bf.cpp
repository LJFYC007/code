/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月12日 星期五 10时43分43秒
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
const int INF = 1e18;

int n, k, d[maxn], a[maxn], ans = 1, c[maxn];
int D[maxn], A[maxn], F[maxn], p[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 2, n) scanf("%lld", &d[i]); 
    REP(i, 1, n) scanf("%lld", &a[i]); 
    REP(i, 1, n) 
    {
        int num = 0, o = k, R = n;
        REP(j, i, n) c[j] = a[j];
        REP(j, i, n)
        {
            num += c[j] - d[j + 1];
            if ( num < 0 ) { c[j] += -num; o += num; num = 0; }
            if ( o < 0 ) { R = j; break ; }
            p[j + 1] = o;
        }
        REP(j, 1, n) 
        {
            D[j] = D[j - 1] + d[j]; 
            A[j] = A[j - 1] + c[j];
        }

        int Max = -INF;
        REP(j, i + 1, R)
        {
            Max = max(Max, A[j - 1] - D[j - 1]);            
            int x = A[j] - D[j] + p[j] - c[j] + a[j];
            if ( x >= Max ) ans = max(ans, j - i + 1);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
