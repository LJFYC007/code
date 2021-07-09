/***************************************************************
	File name: LibreOJ_6500.cpp
	Author: ljfcnyali
	Create time: 2020年11月09日 星期一 20时44分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, k, m, ans, a[maxn], b[maxn], A[maxn], pre[maxn], s[maxn], val[maxn];
int f[maxn], s0[maxn], s1[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &k, &m);
    REP(i, 1, n) scanf("%1d", &a[i]);
    REP(i, 0, k - 1) val[i] = rand();
    REP(i, 1, n) 
    {
        A[i] = a[i] ^ a[i - 1];
        pre[i] = (i >= k ? pre[i - k] : 0) + A[i];
        s[i] = s[i - 1] ^ (A[i] ? val[i % k] : 0);

        f[i] = f[i - 1];
        if ( i >= k ) { s0[i] = s0[i - k]; s1[i] = s1[i - k]; } 
        if ( A[i] == 0 ) continue ;
        if ( pre[i] & 1 ) 
        {
            f[i] -= s0[i] - s1[i];
            s1[i] += (i - 1) / k + 1;
            f[i] += s1[i] - s0[i];
        }
        else 
        {
            f[i] -= s1[i] - s0[i];
            s0[i] += (i - 1) / k + 1;
            f[i] += s0[i] - s1[i];
        }
    }
    while ( m -- ) 
    {
        int l, r; scanf("%d%d", &l, &r);
        int x = s[r] ^ s[l] ^ (a[l] ? val[l % k] : 0);
        if ( x && x ^ val[(r + 1) % k] ) { puts("-1"); continue ; }

        ans = f[r] - f[l];
        if ( x ) 
        {
            if ( pre[r - k + 1] & 1 ) { ans -= s1[r - k + 1] - s0[r - k + 1]; ans += s0[r - k + 1] - s1[r - k + 1] + (r / k) + 1; }
            else { ans -= s0[r - k + 1] - s1[r - k + 1]; ans += s1[r - k + 1] - s0[r - k + 1] + (r / k) + 1; }
        }
        if ( a[l] ) 
        {
            ans -= (l - 1) / k + 1;
            if ( pre[l] & 1 ) ans += 2 * (s1[l] - s0[l]); else ans += 2 * (s0[l] - s1[l]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
