/***************************************************************
	File name: CF1220D.cpp
	Author: ljfcnyali
	Create time: 2019年09月19日 星期四 19时16分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int a[maxn], n, sum[maxn], ans, k;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i]); ++ sum[a[i]]; }
    REP(i, 1, n) 
        if ( sum[a[i]] + sum[a[i] * 3] > ans ) 
        {
            ans = sum[a[i]] + sum[a[i] * 3];
            k = a[i];
        }
    printf("%d\n", n - ans);
    REP(i, 1, n) if ( a[i] != k && a[i] != k * 3 ) printf("%d ", a[i]);
    puts("");
    return 0;
}
