/***************************************************************
	File name: puzzle.cpp
	Author: ljfcnyali
	Create time: 2019年09月08日 星期日 09时00分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 1000010;

int a[maxn], test, n, sum1, sum2, ans, sum[maxn], num1[maxn], num2[maxn];

inline char read()
{
    char c = getchar();
    while ( c == ' ' || c == '\n' || c == '\r' ) c = getchar();
    return c;
}

signed main()
{
    freopen("puzzle.in", "r", stdin);
    freopen("puzzle.out", "w", stdout);
    scanf("%lld%lld", &test, &n);
    REP(i, 1, n) 
    {
        a[i] = read() - '0';
        if ( a[i] ) ++ sum1; else ++ sum2;
        if ( sum1 >= 3 ) ans += sum[sum1 - 2];
        if ( a[i] ) sum[sum1] = sum[sum1 - 2] + sum2 + 1, sum2 = 0;
    }
    sum1 = 0;
    REP(i, 1, n)
    {
        if ( a[i] ) num1[i] = sum1, sum1 = 0;
        else ++ sum1;
    }
    sum2 = 0;
    for ( int i = n; i >= 1; -- i ) if ( a[i] ) num2[i] = sum2, sum2 = 0; else ++ sum2;
    REP(i, 1, n) if ( a[i] ) ans += num1[i] * num2[i];
    printf("%lld\n", ans);
    return 0;
}
