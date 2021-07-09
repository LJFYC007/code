/***************************************************************
	File name: P1901.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 21时17分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int sum[maxn], a[maxn], tot, n, h[maxn], v[maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n)
    {
        scanf("%d%d", &h[i], &v[i]);
        while ( tot && h[a[tot]] < h[i] ) sum[i] += v[a[tot --]];
        sum[a[tot]] += v[i];
        a[++ tot] = i;
    }
    REP(i, 1, n) ans = max(ans, sum[i]);
    printf("%d\n", ans);
    return 0;
}
