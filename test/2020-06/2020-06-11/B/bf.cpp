/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月11日 星期四 08时32分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], m, k[maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
    scanf("%d", &m); REP(i, 1, m) scanf("%d", &k[i]);
    sort(a + 1, a + n + 1);
    sort(k + 1, k + m + 1);
    for ( int i = m; i >= 1; -- i )
    {
        for ( int j = n; j >= n - k[i] + 1; -- j ) { ans += a[j]; -- a[j]; }
        sort(a + 1, a + n + 1);
    }
    printf("%d\n", ans);
    return 0;
}
