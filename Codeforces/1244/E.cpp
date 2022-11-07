/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年10月13日 星期日 17时29分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 100010;
const int INF = 1000000000;

int n, k, a[maxn], ans, sum[maxn];

inline int calc1(int x)
{
    int s = a[x] * x - sum[x];
    return s;
}

inline int calc2(int x)
{
    int s = sum[n] - sum[x - 1] - a[x] * (n - x + 1);
    return s;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d%I64d", &n, &k);
    REP(i, 1, n) scanf("%I64d", &a[i]);
    sort(a + 1, a + n + 1);
    REP(i, 1, n) sum[i] = sum[i - 1] + a[i];
    ans = a[n] - a[1];
    int L = 1, R = n;
    while ( a[L] == a[L + 1] ) ++ L;
    while ( a[R] == a[R - 1] ) -- R;
    int sum1 = calc1(L), sum2 = calc2(R);
    int num = 0;
    while ( k && L < R ) 
    {
        if ( L < (n - R + 1) ) 
        {
            int x = a[L + 1] - a[L];
            if ( k >= x * L ) { k -= x * L; ++ L; }
            else { a[L] += k / L; break ; }
        }
        else 
        {
            int x = a[R] - a[R - 1];
            if ( k >= x * (n - R + 1) ) { k -= x * (n - R + 1); -- R; }
            else { a[R] -= k / (n - R + 1); break ; }
        }
        continue ;
        ++ num; if ( num > n ) break ; 
        if ( sum1 <= sum2 ) 
        {
            ans = min(ans, a[R] - a[L]); k -= sum1;
            ++ L; int now = L; 
            while ( a[L] == a[now] && L <= R ) ++ L;
            -- L;
            sum1 = calc1(L) - sum1;
        }
        else
        {
            ans = min(ans, a[R] - a[L]); k -= sum2;
            -- R; int now = R; 
            while ( a[R] == a[now] && R >= L ) -- R;
            ++ R;
            sum2 = calc2(R) - sum2;
        }
    }
    printf("%I64d\n", a[R] - a[L]);
    return 0;
}
