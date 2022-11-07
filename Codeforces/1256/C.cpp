/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 21时03分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, m, d, a[maxn], ans[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &d);
    int sum = 0;
    REP(i, 1, n) { scanf("%d", &a[i]); sum += a[i]; }
    int now = 0, t = 1;
    while ( now <= n ) 
    {
        int x = now + d;
        if ( n - x + 1 <= sum ) 
        {
            now = n;
            for ( int k = m; k >= t; -- k ) REP(i, 1, a[k]) ans[now --] = k;
            break ; 
        }
        if ( t > m ) { puts("NO"); return 0; }
        REP(j, x, x + a[t] - 1) ans[j] = t;
        now = x + a[t] - 1;
        sum -= a[t];
        ++ t;
    }
    puts("YES"); REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
